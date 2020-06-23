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

int             client(void)
{
    // creation socket sock
    SOCKET      sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == INVALID_SOCKET)
    {
        perror("socket()");
        exit(errno);
    }
    // connexion au server
    struct hostent  *hostinfo = NULL;
    SOCKADDR_IN sin = { 0 }; // init la structure avec des 0
    const char      *hostname = "www.chbelan.fr";

    hostinfo = gethostbyname(hostname); // recuperation des infos de l'hote auquel on veut se connecter
    if (hostinfo == NULL)
    {
        fprintf(stderr, "Unknow host %s.\n", hostname);
        exit(EXIT_FAILURE);
    }
    sin.sin_addr = *(IN_ADDR *) hostinfo->h_addr; // l'addresse se trouve dans le champs h_addr de la structure hostinfo
    sin.sin_port = htons(PORT);
    sin.sin_family = AF_INET;

    if (connect(sock,(SOCKADDR *) &sin, sizeof(SOCKADDR)) == SOCKET_ERROR)
    {
        perror("connect()");
        exit(EXIT_FAILURE);
    }
    //SOCKET      socket;
    char        buff[1024];
    // envoie de donner pour communiquer avec le serveur
    if (send(sock, buff, strlen(buff), 0) < 0)
    {
        perror("send()");
        exit(EXIT_FAILURE);
    }
    // reception des donnees
    int     n = 0;
    if ((n = recv(sock, buff, sizeof(buff - 1), 0)) < 0)
    {
        perror("recv()");
        exit(EXIT_FAILURE);
    }
    buff[n] = '\0';
    // ferme le socket
    closesocket(sock);
    return (0);
}
