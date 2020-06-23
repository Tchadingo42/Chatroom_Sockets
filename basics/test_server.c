#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <netdb.h>
#define PORT 30000
#define SOCKET_ERROR -1

typedef struct  s_user
{            
    char        nom[30];
    int         age;
}                t_user;

int                     main(void)
{
    struct sockaddr_in  addrServer;
    int                 sock;
    int                 client_sock;

    sock = socket(AF_INET, SOCK_STREAM, 0);

    addrServer.sin_addr.s_addr = inet_addr("127.0.0.1");
    addrServer.sin_family = AF_INET;
    addrServer.sin_port = htons(PORT);

    bind(sock, (const struct sockaddr *) &addrServer, sizeof(addrServer));
    printf("bind :%d\n", sock);

    listen(sock, 5);
    printf("listen\n"); 

    struct sockaddr_in addrClient;
    socklen_t csize = sizeof(addrClient);
    client_sock = accept(sock, (struct sockaddr *)&addrClient, &csize);
    printf("accept\n");

    printf("client : %d\n", sock);
    t_user      user;

    user.age = 22;

    send(client_sock, &user, sizeof(user), 0);
    close(client_sock);
    close(sock);
    printf("close\n");
    return (0);
}
