#include <pthread.h>
#include <ctype.h>
#include <sys/sem.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include  <signal.h>

char arr[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 
					'h', 'i', 'k', 'l', 'm', 'n', 'o', 
					'p', 'q', 'r', 's', 't', 'v', 'x', 'y', 'z'};
int semid;

static struct sembuf main_unlock = {0, 1, 0};
static struct sembuf inv_unlock = {1, 1, 0};
static struct sembuf ref_unlock = {2, 1, 0};

static struct sembuf main_lock = {0, -1, 0};
static struct sembuf inv_lock = {1, -1, 0};
static struct sembuf ref_lock = {2, -1, 0};

void reflect (void *ptr);
void invert (void *ptr);
void INThandler(int);

int 
main(int argc, char  *argv[])
{
	pthread_t tid1, tid2;
	int i;
	
	key_t key = 6969600;
	
	signal(SIGINT, INThandler);
	signal(SIGQUIT, INThandler);
	signal(SIGTERM, INThandler);
	
	if(pthread_create(&tid2, NULL, invert, NULL) < 0) {
		perror("pthread_create");
		exit(1);
	}
	
	if(pthread_create(&tid1, NULL, reflect, NULL) < 0) {
		perror("pthread_create");
		exit(1);
	}
	
	if ((semid = semget(key, 3, 0644 | IPC_CREAT)) < 0) {
		perror("semget");
		exit(1);
	}
	
	while(1) {
		semop(semid, &inv_unlock, 1);
		semop(semid, &main_lock, 1);

		for(i=0; i<sizeof(arr); i++)
			printf("%c ",arr[i]);
		printf("\n");
		
		sleep(1);
		
		semop(semid, &ref_unlock, 1);
		semop(semid, &main_lock, 1);
		
		for(i=0; i<sizeof(arr); i++)
			printf("%c ",arr[i]);
		printf("\n");
		
		sleep(1);
	  }
	
	return 0;
}

void 
invert (void *ptr) {
	char * chr;
	int buf;
	int i;
	
	while(1) {
		semop(semid, &inv_lock, 1);
		chr = &arr[0];
		for(i=0; i<sizeof(arr); i++) {
			buf = *chr;
			if (isalpha(buf))
			  *chr = ( islower(buf) ? toupper(buf) : tolower(buf) );
			chr ++;
		}		
		semop(semid, &main_unlock, 1);
	}
}

void 
reflect (void *ptr) {
	char buf;
	int i;
	while(1) {
		semop(semid, &ref_lock, 1);
		for(i=0; i<sizeof(arr)/2; i++) {
			buf = arr[i];
			arr[i] = arr[sizeof(arr)-1-i];
			arr[sizeof(arr)-1-i] = buf;
		}
		semop(semid, &main_unlock, 1);
	}
}

void  
INThandler(int sig)
{
	if(semctl(semid, 0, IPC_RMID) < 0) {
		perror("semctl");
		exit(1);
	}	
    exit(0);
}
