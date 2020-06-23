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
    int                 new_sock;
    int                 ret;
    struct sockaddr_in  serverAddr;
    struct sockaddr_in  newAddr;
    char                buff[1024];
    pid_t               child;
    socklen_t           addr_size;

    child = 0;
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0)
    {
        printf("[-]Error connection./n");
        exit(1);
    }
    printf("[+]Server socket is created./n");


    memset(&serverAddr, '\0', sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(PORT);
    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");

    ret = bind(sock, (struct sockaddr *)&serverAddr, sizeof(serverAddr));
    if (ret < 0)
    {
        printf("[-]Error in biding./n");
        exit(1);
    }
    printf("[+]Binding to port %d.\n", PORT);

    if (listen(sock, 3) == 0)
    {
        printf("Listening...\n");
    }
    else
    {
        printf("[-]Error in binding part2./n");
    }

    while (1)
    {
        new_sock = accept(sock, (struct sockaddr *)&newAddr, &addr_size);
        if (new_sock < 0)
        {
            exit(1);
        }
        printf("[+]Connection accepted from %s:%d\n", inet_ntoa(newAddr.sin_addr), ntohs(newAddr.sin_port));

        if ((child == fork()) == 0)
        {
            close(sock);
        }
        while (1)
        {
            recv(new_sock, buff, 1024, 0);
            if (strcmp(buff, ":exit") ==0)
            {
                printf("[-]Disconected from %s:%d\n", inet_ntoa(newAddr.sin_addr), ntohs(newAddr.sin_port));
                break;
            }
            else
            {
                printf("Client: %s\n", buff);
                send(new_sock, buff, strlen(buff), 0);
                bzero(buff, sizeof(buff));
            }
        }
    }
    close(new_sock);

    return (0);
}
