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

int                        main(int argc, char **argv)
{
    int                     sock;
    char                    *ip;
    int                     port;
    struct sockaddr_in      serverAddr;
    struct sockaddr_in      serverClient;
    pthread_t               tid;
    int                     fd;
    int                     option;

    if (argc != 2)
    {
        printf("Usage: %s <port>\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    ip = "127.0.0.1";
    port = atoi(argv[1]);

    // socket settings
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0)
    {
        printf("[-]Error socket.\n");
        exit(1);
    }
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(port);
    serverAddr.sin_addr.s_addr = inet_addr(ip);
    // signals
    signal(SIGPIPE, SIG_IGN);
    option = 1;

    if (setsockopt(sock, SOL_SOCKET, (SO_REUSEPORT | SO_REUSEADDR), (char*)&option, sizeof(option)) > 0)
    {
        printf("[-]Error setsokopt.\n");
        exit(1);
    }

    // binding
    if (bind(sock, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) < 0)
    {
        printf("[-]Error bidind.\n");
        exit(1);
    }
    // listen
    if (listen(sock, 3) < 0)
    {
        printf("[-]Error listening.\n");
        exit(1);
    }
    printf("=== WELCOME TO TCHADINGO CHATROOM ==\n");
    return (0);
}
