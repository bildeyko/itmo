#include <unistd.h>
#include <sys/shm.h>
#include "1_1.h"

#define SHM_KEY 6660
#define SHM_MODE 0666

int 
main(int argc, char  *argv[])
{
	int shmid;
	srv_info_t *info;
	
	if ( (shmid = shmget(SHM_KEY, sizeof(srv_info_t), SHM_MODE)) < 0 ) {
		perror("shmget");
		exit(1);
	}
	
	if ( (info = (srv_info_t *) shmat(shmid, NULL, 0)) == (void *) -1) {
		// зачем тут void?
		perror("shmat");
		exit(1);
	}
	while(1)
	{
		printf("pid: %d uid: %d gid: %d\n", info->pid, info->uid, info->gid);
		printf("     secs: %d avg: %.3f %.3f %.3f\n", 
				info->secs, info->loadavg1, info->loadavg5, info->loadavg15);
		sleep(1);
	}
	
	return 0;
}
