#include <fcntl.h>
#include <sys/mman.h>
#include "1_1.h"

int 
main(int argc, char  *argv[])
{
	char fname[] = ".mmaptmp";
	srv_info_t *info;
	int file;
	
	if ((file = open(fname, O_RDONLY)) < 0) {
		perror("open");
		exit(1);
	}
	
	if ( (info = (srv_info_t *) mmap(0, sizeof(srv_info_t), 
			PROT_READ, MAP_SHARED, file, 0)) == MAP_FAILED) {
		perror("mmap");
		exit(1);
	}
	
	while(1)
	{
		printf("pid: %d uid: %d gid: %d\n", info->pid, info->uid, info->gid);
		printf("     secs: %d avg: %.3f %.3f %.3f\n", info->secs, info->loadavg1, info->loadavg5, info->loadavg15);
		sleep(1);
	}
	
	return 0;
}
