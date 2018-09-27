#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <pthread.h>
#include <semaphore.h>
#include <fcntl.h>

#define SNAME "/mySem"
sem_t *sem;
int main(void) {
	int newSem;
	sem = sem_open(SNAME,0);

	printf("Thread-Waker PIDD = %d \n", getpid());
	while(newSem != 0){
		printf("How many threads do you want to wake up (enter 0 to exit)?\n");
		scanf("%d", &newSem);
		for(int j = 0; j < newSem; j++) {
			sem_post(sem);
			//printf("hello\n");
		}
		sleep(1);
	}
	printf("bye!\n");
	sem_destroy(sem);
	return EXIT_SUCCESS;
}
