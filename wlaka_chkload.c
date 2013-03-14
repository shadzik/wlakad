/* Check load average for wlakad purpose
 * Author: Bartosz 'shadzik' Swiatek (shadzik@gmail.com)
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/wait.h>

#include "wlaka.h"

int check_load(void) {
        FILE *f;
        int value, pid;
	struct stat statinfo;
        f = fopen(LOAD, "r");
        if (!f)  
                return -1;
        else
                fscanf(f, "%d", &value);
        fclose(f);
	if ((value >= maxload) && (stat(APACHELOCK,&statinfo)==0)) {
		pid=fork();
		if(pid==0) {
			logtxt("Load was too big, killed apache.");
			execl("/etc/rc.d/init.d/httpd", "httpd", "stop", (char *)NULL);
		}
		else
			waitpid(pid, NULL, 0);
	}
	if ((value <= minload) && (stat(APACHELOCK,&statinfo)!=0)) {
		pid=fork();
		if(pid==0) {
			logtxt("Load acceptable. Started apache.");
			execl("/etc/rc.d/init.d/httpd", "httpd", "start", (char *)NULL);
		}
		else
			waitpid(pid, NULL, 0);
	}
return 0;
}

