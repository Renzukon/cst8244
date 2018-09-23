#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>


sig_atomic_t usr1Happened;

void sigusr1_handler(int sig)
{
	usr1Happened = 1;
}

int main(void) {
    struct sigaction sa;
    int numChildren = 0;
    int counter = 0;
    usr1Happened = 0;
	sa.sa_handler = sigusr1_handler;
	sa.sa_flags = 0; // or SA_RESTART
	sigemptyset(&sa.sa_mask);

	if (sigaction(SIGUSR1, &sa, NULL) == -1) {
		perror("sigaction");
		exit(1);
	}

	printf("Enter the number of children:\n");
	scanf("%d", &numChildren);
	printf("PID = %d : Parent running\n", getpid());
	pid_t pid;
	for(int i = 0; i < numChildren; i++){
	int rv;


	    switch(pid = fork()) {
	    case -1:
	        perror("fork");  /* something went wrong */
	        exit(1);         /* parent exits */

	    case 0:
	    		while (!usr1Happened) {
	    			printf("PID = %d : Child running\n", getpid());
	    			sleep(5);
	    		}
	    		printf("PID = %d : Child received USR1\n",getpid());
	    		printf("PID = %d : Child Exiting.\n",getpid());
	    		exit(rv);

	    default:
    		counter++;
	        if(counter == numChildren){
		        while ((pid = wait(&rv)) > 0);
		        printf("PID = %d: Children finished, parent exiting.\n", getpid());
	        }
	    }
	}

	return 0;
}
