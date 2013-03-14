/* Definitions for wlaka.c and chkload.c
 * author: Bartosz 'shadzik' Swiatek (shadzik@gmail.com)
 */

#define LOGFILE "/var/log/wlakad"
#define USAGE   "[-v][-l maxload][-m minload][-c cycles][-f logfile]"
        
/* Default cycle time set to 5 minutes */
#define CYCLE   (5*60)
/* Default maxload set to 50 */  
#define MAXLOAD 50
/* Default minload set to 10 */  
#define MINLOAD 10
        
#define OPTSTRING       "vl:m:c:f:"

#define LOAD "/proc/loadavg"
#define APACHELOCK "/var/lock/subsys/httpd"
#define	PIDFILE	"/var/run/wlakad.pid"

int check_load();
int logtxt();
int chkpid();

char progname[100];
int maxload,minload;
char logfile[100];
