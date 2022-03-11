#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <signal.h>
#include <netdb.h>

void error(char *msg) {
    
    fprintf(stderr, "%s: %s\n", msg, strerror(errno));
    exit(1);
}

int open_socket(char *host, char *port) {

    struct addrinfo *res;
    struct addrinfo hints;
    memset (&hints, 0, sizeof(hints));
    hints.ai_family = PF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    if (getaddrinfo(host, port, &hints, &res) == -1)
      error("Can`t resolve the address");
    int d_sock = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
    if (d_sock == -1)
      error("Can`t open socket");
    int c = connect(d_sock, res->ai_addr, res->ai_addrlen);
    freeaddrinfo(res);
    if (c == -1)
      error("Can`t connect to socket");
    return d_sock;
}

void open_socket_ip(char *host, char *port) {

    int s = socket(PF_INET, SOCK_STREAM, 0);

    struct sockaddr_in si;
    memset(&si, 0, sizeof(si));
    si.sin_family = PF_INET;
    si.sin_addr.s_addr = inet_addr("85.242.180.83");
    si.sin_port = htons(30000);
    connect(s, (struct sockaddr *) &si, sizeof(si));

}

int say(int socket, char *s) {
    
    int result = send(socket, s, strlen(s), 0);
    if (result == -1)
        fprintf(stderr, "%s: %s\n", "Error talking to the client", strerror(errno));
    return result;
}

int main(int argc, char *argv[]) {

    int d_sock;

    d_sock = open_socket("85.242.180.83", "30000");
    char buf[255];

    sprintf(buf, "GET /wiki/%s http/1.1\r\n", argv[1]);
    say(d_sock, buf);

    say(d_sock, "HOST: en.wikipedia.org\r\n\r\n");
    char rec[256];
    int byteRcvd = recv(d_sock, rec, 255, 0);
    while (byteRcvd) {
        if (byteRcvd == -1)
          error("Can`t read from server");
        
        rec[byteRcvd] = '\0';
        printf("%s", rec);
        byteRcvd = recv(d_sock, rec, 255, 0);
    }

    close(d_sock);
    return 0;

}