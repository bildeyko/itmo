#include <unistd.h>
#include <sys/shm.h>
#include  <signal.h>
#include "1_1.h"

#define SHM_KEY 6660
#define SHM_MODE 0666

void INThandler(int);

int shmid;
srv_info_t *shm;

int 
main(int argc, char  *argv[])
{
	time_t start;
	double load[3] = {0};
	
	if (signal(SIGINT, INThandler) < 0)
		perror("Cannot handle SIGINT");
	
	if (signal(SIGQUIT, INThandler) < 0)
		perror("Cannot handle SIGQUIT");

	if (signal(SIGTERM, INThandler) < 0)
		perror("Cannot handle SIGTERM");
	
	if ( (shmid = shmget(SHM_KEY, sizeof(srv_info_t), IPC_CREAT | SHM_MODE)) < 0 ) {
		perror("shmget");
		exit(1);
	}
	
	if ( (shm = (srv_info_t *) shmat(shmid, NULL, 0)) == (void *) -1) {
		perror("shmat");
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
	if(shmdt((void *) shm) < 0){
		perror("shmdt");
		exit(1);
	}
    if(shmctl(shmid, IPC_RMID, NULL) < 0) {
		perror("shmctl");
		exit(1);
	}
	
    exit(0);
}
