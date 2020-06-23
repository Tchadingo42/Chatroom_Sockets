#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <errno.h>
#include <sys/socket.h>
#include <strings.h>
#include <string.h>
#define  MAX_CLIENTS 4
#define  BUFF_SIZE 2048

int                 main(int argc, char **argv)
{
    char            *ip;
    int             port;

    if (argc != 2)
    {
        printf("Usage: %s <port>\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    ip = "127.0.0.1";
    port = atoi(argv[1]);



    return (0);
}
