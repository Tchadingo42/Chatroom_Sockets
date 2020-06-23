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
#include <pthread.h>
#include "my.h"
#define PORT 30000
#define SOCKET_ERROR -1

int                     main(void)
{
    t_user              user;
    struct sockaddr_in  addrClient;
    int                 sock;
    char                chaine[42];

    sock = socket(AF_INET, SOCK_STREAM, 0);

    addrClient.sin_addr.s_addr = inet_addr("127.0.0.1");
    addrClient.sin_family = AF_INET;
    addrClient.sin_port = htons(PORT);

    connect(sock, (const struct sockaddr *)&addrClient, sizeof(addrClient));
    printf("Connecter\n");
    
    recv(sock, chaine, 42, 0);
    printf("%s\n", chaine);
    scanf("%d %d %d", &user.x, &user.y, &user.z);
    send(sock, &user, sizeof(user), 0);

    close(sock);
    return (0);
}
