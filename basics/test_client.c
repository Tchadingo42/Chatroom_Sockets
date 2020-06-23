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
    t_user              user;
    struct sockaddr_in  addrClient;
    int                 sock;

    sock = socket(AF_INET, SOCK_STREAM, 0);

    addrClient.sin_addr.s_addr = inet_addr("127.0.0.1");
    addrClient.sin_family = AF_INET;
    addrClient.sin_port = htons(PORT);

    connect(sock, (const struct sockaddr *)&addrClient, sizeof(addrClient));
    printf("Connecter\n");

    recv(sock, &user, sizeof(t_user), 0);
    printf("data->[%d]\n", user.age);
    close(sock);

    return (0);
}
