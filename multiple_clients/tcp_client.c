#include <strings.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#define PORT 30000

int                     main(void)
{
    int                 sock;
    int                 ret;
    char                buff[1024];
    struct sockaddr_in   serverAddr;

    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0)
    {
        printf("[-]Error in connection.\n");
        exit(1);
    }
    printf("[+]Client socket is created.\n");

    memset(&serverAddr, '\0', sizeof(serverAddr));

    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(PORT);
    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");

    ret = connect(sock, (struct sockaddr*)&serverAddr, sizeof(serverAddr));
    if (ret < 0)
    {
        printf("[-]Error in connection.\n");
        exit(1);
    }
    printf("[+]Connection to server./n");

    while (1)
    {
        printf("Client: \t");
        scanf("%s", &buff[0]);
        send(sock, buff, strlen(buff), 0);

        if (strcmp(buff, ":exit") == 0)
        {
            close(sock);
            printf("[-]Disconected from server.\n");
            exit(1);
        }
        if (recv(sock, buff, 1024, 0) < 0)
        {
            printf("[-]Error in reiceiving data.\n");
        }
        else
        {
            printf("Server: \t%s\n", buff);
        }
    }

    return (0);
}
