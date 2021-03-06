/* chkpid functionality for wlakad
 * Author: Bartosz 'shadzik' Swiatek (shadzik@gmail.com) 
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>

#include "wlaka.h"

int chkpid() {
	int pid = getpid()+1;
	int old_pid = 0;
	struct stat statinfo;
	FILE *f;
	if (stat(PIDFILE,&statinfo)==0) {
		f = fopen(PIDFILE,"r");
		fscanf(f ,"%d", &old_pid);
		printf("It seems that another wlakad instance is already running.\n");
		printf("Kill PID %d or if that pid doesn't exist remove %s manually.\n", old_pid, PIDFILE);
		fclose(f);
		exit(1);
	}
	else {
		f = fopen(PIDFILE, "w");
		fprintf(f, "%d", pid);
		fclose(f);
	}
return 0;
}
