/* Logger functionality for wlakad
 * Author: Bartosz 'shadzik' Swiatek (shadzik@gmail.com) 
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "wlaka.h"

int logtxt(char message[10000]) {
	time_t clock;
	clock=time(NULL);
	char *data = ctime(&clock);
	FILE *f;
	f = fopen(logfile,"a+");
	if (!f)
		return -1;
	else
		fprintf(f ,"%s wlakad.c: %s\n", data, message);
	fclose(f);
return 0;
}
