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
#define PORT 30000
#define SOCKET_ERROR -1

typedef struct  s_user
{            
    int         age;
    int         x;
    int         y;
    int         z;
}                t_user;

void                    *function(void *args)
{
    int                 socket;
    char                chaine[] = "quels sont les positions du player";
    t_user              user;

    socket = *(int*)args;
    send(socket, chaine, strlen(chaine) + 1, 0);
    recv(socket, &user, sizeof(user), 0);
    printf("the values are x->%d y->%d z->%d\n", user.x, user.y, user.z);
    close(socket);
    free(args);
    pthread_exit(NULL);
}

int                     main(void)
{
    struct sockaddr_in  addrServer;
    int                 sock;
    int                 client_sock;
    pthread_t           thread_client;
    int                 i;
    int                 *args;

    sock = socket(AF_INET, SOCK_STREAM, 0);

    addrServer.sin_addr.s_addr = inet_addr("127.0.0.1");
    addrServer.sin_family = AF_INET;
    addrServer.sin_port = htons(PORT);

    bind(sock, (const struct sockaddr *) &addrServer, sizeof(addrServer));
    printf("bind :%d\n", sock);

    listen(sock, 5);
    printf("listen\n"); 

    pthread_t   tab[3];
    i = 0;
    while (i < 3)
    {
        struct sockaddr_in addrClient;
        socklen_t csize = sizeof(addrClient);
        client_sock = accept(sock, (struct sockaddr *)&addrClient, &csize);
        printf("accept\n");

        if (!(args = malloc(sizeof(int))))
            return (-1);
        *args = client_sock;
        pthread_create(&tab[i], NULL, function, args);
        i = i + 1;
    }
    i = 0;
    while (i < 3)
    {
        pthread_join(tab[i], NULL);
        i = i + 1;
    }
    close(client_sock);
    close(sock);
    printf("close\n");
    return (0);
}
