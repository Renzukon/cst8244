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

sig_atomic_t usr1Happened;
sem_t *sem;

void* childThread(void *arg){
	int semvalue = 0;
	printf("Child thread %d created\n", pthread_self());
	while(1) {
		sem_wait(sem);
		sem_getvalue(sem, &semvalue);
		printf("Child thread %d unblocked\n", pthread_self());
		sleep(5);
	}
	pthread_exit(NULL);
}

void sigusr1_handler(int sig)
{
	usr1Happened = 1;
}

int main(void) {
    int err;
    int nThreads = 0;
	pthread_attr_t attr;
    struct sigaction sa;
    usr1Happened = 0;
	sa.sa_handler = sigusr1_handler;
	sa.sa_flags = 0; // or SA_RESTART
	sigemptyset(&sa.sa_mask);
	sem = sem_open(SNAME,O_CREAT,S_IWOTH,0);
	if (sigaction(SIGUSR1, &sa, NULL) == -1) {
		perror("sigaction");
		exit(1);
	}

	printf("Enter the number of threads to create:\n");
	scanf("%d", &nThreads);
	for(int i = 0; i < nThreads; i++){
		pthread_attr_init(&attr);
		err = pthread_create(NULL, &attr, &childThread, NULL);
		if(err != 0){
			printf("Can't create thread");
		}
		pthread_attr_destroy(&attr);
	}

    while (!usr1Happened) {
        sleep(5);
    }

	printf("Process has been killed");
	sem_destroy(sem);
	return 0;
}
