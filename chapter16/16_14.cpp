#include "../include/apue.h"
#include <netdb.h>
#include <errno.h>
#include <sys/socket.h>

#define MAXADDRLEN 256
#define BUFLEN 128

extern int connect_retry(int, const struct sockaddr*, socklen_t);

//receive and print the data from remote machine
void print_uptime(int sockfd)
{
    int n;
    char buf[BUFLEN];

    while((n=recv(sockfd, buf, BUFLEN, 0)) > 0)
    {
        write(STDOUT_FILENO, buf, n);
    }

    if(n<0)
    {
        err_sys("recv error");
    }
}

int main(int argc, char* argv[])
{
    struct addrinfo *ailist, *aip;
    struct addrinfo hint;
    int sockfd, err;

    if(argc != 2)
    {
        err_quit("usage: ruptime hostname");
    }

    hint.ai_flags = 0; //customize behavior
    hint.ai_family = 0; //AF_UNSPEC:0 AF_INET:2 AF_INET6:23
    hint.ai_socktype = SOCK_STREAM; //SOCK_STREAM SOCK_DGRAM
    hint.ai_protocol = 0;
    hint.ai_addrlen = 0;
    hint.ai_canonname = NULL;
    hint.ai_next = NULL;

	//get the address info correspond to specified host-service, hind filled with
	//the type we wanted, ailist is stored with return result, result may be mulple
    if((err = getaddrinfo(argv[1], "ruptimed", &hint, &ailist)) != 0)
    {
        err_quit("getaddrinfo error: %s", gai_strerror(err));
    }

	// once we got some addresses, we the create a socket, and connect it with the first 
	// address we got, last we print the data received 
    for(aip=ailist; aip!=NULL; aip=aip->ai_next)
    {
        if((sockfd = socket(aip->ai_family, SOCK_STREAM, 0)) < 0)
        {
            err = errno;
        }
        if(connect_retry(sockfd, aip->ai_addr, aip->ai_addrlen) < 0)
        {
            err = errno;
        }
        else
        {
            print_uptime(sockfd);
            exit(0);
        }
    }

    fprintf(stderr, "can't connect to %s: %s\n", argv[1], strerror(err));
    exit(1);
}

