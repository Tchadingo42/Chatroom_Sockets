#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#define h_addr h_addr_list[0] /* for backward compatibility */
#include <unistd.h> /* close */
#include <netdb.h> /* gethostbyname */
#define INVALID_SOCKET -1
#define PORT 4242
#define SOCKET_ERROR -1
#define closesocket(s) close(s)
typedef int SOCKET;
typedef struct sockaddr_in SOCKADDR_IN;
typedef struct sockaddr SOCKADDR;
typedef struct in_addr IN_ADDR;
int             client(void);
int             server(void);

int             main(void)
{
    client();
    server();
}

int            server(void)
{
    // creation socket
    SOCKET      sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == SOCKET_ERROR)
    {
        perror("socket()");
        exit(errno);
    }
    // creation interface sur laquelle notre socket va ecouter pour la lier au socket
    SOCKADDR_IN sin = { 0 };
    // on rempli  la structure  SOCKADDR pour l'addresse on utilise htonl donc le server ecoute sur PORT
    sin.sin_addr.s_addr = htonl(INADDR_ANY); //nous somme un serveret acceptons n'importe quel addresse
    sin.sin_family = AF_INET;
    sin.sin_port = htons(PORT);

    if (bind(sock, (SOCKADDR *) &sin, sizeof(sin)) == SOCKET_ERROR)
    {
        perror("blind()");
        exit(EXIT_FAILURE);
    }
    // ecouter et accepter les connexions limiter a deux entrer
    if (listen(sock, 2) == SOCKET_ERROR)
    {
        perror("listen()");
        exit(EXIT_FAILURE);
    }
    SOCKADDR_IN    csin = { 0 };
    SOCKET          csock;
    int             sinsize = sizeof csin;
    csock = accept(sock, (SOCKADDR *) &csin, &sinsize);

    if (csock == INVALID_SOCKET)
    {
            perror("accept()");
            exit(EXIT_FAILURE);
    }
    closesocket(sock);
    closesocket(csock);
    return (0);
}

