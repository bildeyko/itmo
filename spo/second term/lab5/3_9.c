#include <unistd.h>
#include  <signal.h>
#include "1_1.h"

void handler(int);

srv_info_t shm;

int 
main(int argc, char  *argv[])
{
	time_t start;
	double load[3] = {0};
		
	struct sigaction sa;
	sa.sa_handler = &handler;
	
	if (sigaction(SIGINT, &sa, NULL) < 0)
		perror("Cannot handle SIGINT");

	if (sigaction(SIGHUP, &sa, NULL) < 0)
		perror("Cannot handle SIGHUP");

	if (sigaction(SIGUSR1, &sa, NULL) < 0)
		perror("Cannot handle SIGUSR1");

	if (sigaction(SIGUSR2, &sa, NULL) < 0)
		perror("Cannot handle SIGUSR2");

	if (sigaction(SIGTERM, &sa, NULL) < 0)
		perror("Cannot handle SIGTERM");
	
	start = time(NULL);
	getloadavg(load, 3);
	
	shm.pid = getpid();
	shm.uid = getuid();
	shm.gid = getgid();
	shm.secs = start;	
	shm.loadavg1 = load[0];
	shm.loadavg5 = load[1];
	shm.loadavg15 = load[2];
	
	
	printf("pid: %d uid: %d gid: %d\n", shm.pid, shm.uid, shm.gid);
		printf("     avg: %.3f %.3f %.3f\n", shm.loadavg1, shm.loadavg5, shm.loadavg15);
	while(1) {
		sleep(1);
		shm.secs = time(NULL) - start;
	}
	
	return 0;
}

void  
handler(int sig)
{
	if(sig == 1) 
		printf("pid: %d\n", shm.pid);
	if(sig == 2) 
		printf("uid: %d\n", shm.uid);
	if(sig == 15) 
		printf("gid: %d\n", shm.gid);
	if(sig == 16) 
		printf("time: %d sec\n", shm.secs);
	if(sig == 17) 
		printf("avg: %.3f %.3f %.3f\n", shm.loadavg1, shm.loadavg5, shm.loadavg15);
}
