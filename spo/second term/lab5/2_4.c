#include <pthread.h>
#include <semaphore.h>
#include <ctype.h>

char arr[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 
					'h', 'i', 'k', 'l', 'm', 'n', 'o', 
					'p', 'q', 'r', 's', 't', 'v', 'x', 'y', 'z'};
sem_t sem1;
sem_t sem2;
sem_t sem3;
sem_t sem4;

void reflect (void *ptr);
void invert (void *ptr);

int 
main(int argc, char  *argv[])
{
	pthread_t tid1, tid2;
	int i;
	
	if(pthread_create(&tid2, NULL, invert, NULL) < 0) {
		perror("pthread_create");
		exit(1);
	}
	
	if(pthread_create(&tid1, NULL, reflect, NULL) < 0) {
		perror("pthread_create");
		exit(1);
	}
	
	
	  if (sem_init(&sem1, 0, 0) < 0){
		perror("sem_init error");
		return 1;
	  }
		
	  if (sem_init(&sem2, 0,0) < 0){
		perror("sem_init error");
		return 1;
	  }

	  if (sem_init(&sem3, 0, 0) < 0){
		perror("sem_init error");
		return 1;
	  }
		
	  if (sem_init(&sem4, 0,0) < 0){
		perror("sem_init error");
		return 1;
	  }
	  
	  while(1) {
		sem_post(&sem1);
		sem_wait(&sem2);

		for(i=0; i<sizeof(arr); i++)
			printf("%c ",arr[i]);
		printf("\n");
		
		sleep(1);
		
		sem_post(&sem3);
		sem_wait(&sem4);
		
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
		sem_wait(&sem1);
		chr = &arr[0];
		for(i=0; i<sizeof(arr); i++) {
			buf = *chr;
			if (isalpha(buf))
			  *chr = ( islower(buf) ? toupper(buf) : tolower(buf) );
			chr ++;
		}		
		sem_post(&sem2);
	}
}

void reflect (void *ptr) {
	char buf;
	int i;
	while(1) {
		sem_wait(&sem3);
		for(i=0; i<sizeof(arr)/2; i++) {
			buf = arr[i];
			arr[i] = arr[sizeof(arr)-1-i];
			arr[sizeof(arr)-1-i] = buf;
		}
		sem_post(&sem4);
	}
}
