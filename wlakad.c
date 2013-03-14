/* WLAKAd - Watch Load And Kill Apache daemon
 * Author: Bartosz 'shadzik' Swiatek (shadzik@gmail.com)
 *
 * This is a little daemon I wrote for my friend to avoid apache doing an overload
 * on his entire machine. It watches the load average and kills apache if load grows
 * too much. Than, after load sinks to a capable result, it starts apache back again to 
 * provide web service to users.
 *
 * Version: 0.2 (dated to: 20070501)
 * License: GPLv2
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <signal.h>
#include <sys/wait.h>
#include <unistd.h>

#include "wlaka.h"

static char _verid[] = {"wlakad.c 0.2 (01/05/2007)"};

void usun();

int main(int argc, char *argv[]) {
	int ch, cycle_time, pid;
	strcpy(progname, argv[0]);
	/* replace some defines if passed options */
	strcpy(logfile, LOGFILE);
	extern char *optarg;

	maxload = MAXLOAD;
	minload = MINLOAD;
	cycle_time = CYCLE;

	while ((ch = getopt(argc, argv, OPTSTRING)) != -1) {
		switch(ch) {
			case 'v':
				/* -v just prints version and exits */
				printf("%s\n", _verid);
				exit(0);
			case 'l':
				/* -l sets maxload (default 50) */
				if (sscanf(optarg, "%d", &maxload) != 1) {
					fprintf(stderr, "%s: unreadable maxload argument\n", progname);
					exit(1);
				}
				break;
			case 'm':
				/* -m sets minload (defult 10) */
				if (sscanf(optarg, "%d", &minload) != 1) {
					fprintf(stderr, "%s: unreadable minload argument\n", progname);
					exit(1);
				}
				break;
			case 'c':
				/* -c sets cycle time (default 5 minutes) */
				if (sscanf(optarg, "%d", &cycle_time) != 1) {
					fprintf(stderr, "%s: unreadable cycle time argument\n", progname);
					exit(1);
				}
				break;
			case 'f':
				/* -f sets alternative logfile (default /var/log/wlaka) */
				if (sscanf(optarg, "%s", logfile) != 1) {
					fprintf(stderr, "%s: unreadable logfile argument\n", progname);
					exit(1);
				}
				break;
			default:
				fprintf(stderr, "Usage: %s %s\n", argv[0], USAGE);
				exit(1);
		}
	}

	/* Check if wlakad isn't already running and write pidfile
	 */
	chkpid();

	/* On exiting loop of option parsing optind indexes the next
	 * argv[] argument to the function.
	 *
	if( signal( SIGINT, SIG_IGN ) != SIG_IGN )
		signal( SIGINT, SIG_IGN );
	if( signal( SIGKILL, SIG_IGN ) != SIG_IGN )
		signal( SIGKILL, SIG_IGN );
	*/

	logtxt("WLAKA Daemon started successfully in the backround.");
	/* Fork child process, sends daemon to the background loop */
	pid = fork();
	if (pid==0) {
		//fclose(stdin);
		fclose(stdout);
		while(1) {
			check_load();
			sleep(cycle_time);
		}
	}
	else {
		/*
		if( signal( SIGINT, SIG_DFL ) != SIG_DFL )
			signal( SIGINT, SIG_DFL );
		if( signal( SIGKILL, SIG_DFL ) != SIG_DFL )
			signal( SIGKILL, SIG_DFL);
		*/
		//waitpid(-1, NULL, 0);
		exit(0);
	}
} /* end main() */

void usun() {
	remove(PIDFILE);
}
