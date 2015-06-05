#ifndef FILE_1_1_H
#define FILE_1_1_H

#include <sys/types.h> 
#include <time.h>

typedef struct srv_info {
	pid_t pid;
	uid_t uid;
	gid_t gid;
	time_t secs;
	double loadavg1;
	double loadavg5;
	double loadavg15;
} srv_info_t;

#endif
