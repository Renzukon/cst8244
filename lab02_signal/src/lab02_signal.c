#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <signal.h>

sig_atomic_t usr1Happened;

void sigusr1_handler(int sig)
{
	usr1Happened = 1;
}

int main(void) {
    struct sigaction sa;
    usr1Happened = 0;
	sa.sa_handler = sigusr1_handler;
	sa.sa_flags = 0; // or SA_RESTART
	sigemptyset(&sa.sa_mask);


	if (sigaction(SIGUSR1, &sa, NULL) == -1) {
		perror("sigaction");
		exit(1);
	}

    while (!usr1Happened) {
        printf("PID = %d : Running…\n", getpid());
        sleep(5);
    }
	printf("PID = %d : Received USR1\n",getpid());
	printf("PID = %d : Exiting.\n",getpid());
	return 0;
}
