#include <fcntl.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include  <signal.h>
#include "1_1.h"

void INThandler(int);

srv_info_t *shm;

int 
main(int argc, char  *argv[])
{
	char fname[] = ".mmaptmp";
	int file;
	time_t start;
	double load[3] = {0};
	
	if (signal(SIGINT, INThandler) < 0)
		perror("Cannot handle SIGINT");
	
	if (signal(SIGQUIT, INThandler) < 0)
		perror("Cannot handle SIGQUIT");

	if (signal(SIGTERM, INThandler) < 0)
		perror("Cannot handle SIGTERM");
	
	if ((file = open(fname,O_RDWR | O_CREAT | O_TRUNC,
	S_IRWXU | S_IRWXG | S_IRWXO)) < 0) {
		perror("open");
		exit(1);
	}
	
	if (ftruncate(file, sizeof(srv_info_t)) < 0) {
		perror("ftruncate");
		exit(1);
	}
	
	if ( (shm = (srv_info_t *) mmap(0, sizeof(srv_info_t), 
			PROT_READ | PROT_WRITE, MAP_SHARED, file, 0)) == MAP_FAILED) {
		perror("mmap");
		exit(1);
	}
	
	if(close(file) < 0 ) {
		perror("close");
		exit(1);
	}
	
	start = time(NULL);
	getloadavg(load, 3);
	
	shm->pid = getpid();
	shm->uid = getuid();
	shm->gid = getgid();
	shm->secs = 0;	
	shm->loadavg1 = load[0];
	shm->loadavg5 = load[1];
	shm->loadavg15 = load[2];
	
	printf("pid: %d uid: %d gid: %d\n", shm->pid, shm->uid, shm->gid);
		printf("     avg: %.3f %.3f %.3f\n", shm->loadavg1, shm->loadavg5, shm->loadavg15);
	
	while(1) {
		sleep(1);
		shm->secs = time(NULL) - start;
	}
	
	return 0;
}

void  
INThandler(int sig)
{
	if(munmap((void *)shm, sizeof(srv_info_t)) < 0) {
		perror("munmap");
		exit(1);
	}	
    exit(0);
}
