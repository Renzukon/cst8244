#include <stdio.h>
#include <stdlib.h>
#include <process.h>
#include <string.h>
#include <errno.h>
#include <sys/neutrino.h>

#include "calc_message.h"

int main(int argc, char* argv[]) {
    //int     rcvid;
    int     chid;
    //char    message [50];

    chid = ChannelCreate (0);
    if (chid == -1)
    {
    	perror("failed to create the channel.");
    	exit (EXIT_FAILURE);
    }
    printf("The server is running as PID %d\n", getpid());
    while (1) {

    }
    ChannelDestroy(chid);
	return EXIT_SUCCESS;
}
