#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <string.h>
#include <time.h>
#include <limits.h>

typedef struct client
{
	int sockfd;
	struct sockaddr_storage client_info;
	int client_size;
}client;

void initServer(int *sockfd, char *port, struct addrinfo *server_info, struct addrinfo **server_pointer, int backlog)
{
	if (!getaddrinfo(NULL,port,server_info,server_pointer)) {
		struct addrinfo *traverse=*server_pointer;
		while (traverse) {
			if ((*sockfd=socket(traverse->ai_family, traverse->ai_socktype, traverse->ai_protocol)) != -1) {
				if (bind(*sockfd, traverse->ai_addr, traverse->ai_addrlen) != -1) {
					if (listen(*sockfd,backlog) != -1) {
						printf ("Server Listening at Port %s\n", port);
						break;
					}
				}
			}
			traverse=traverse->ai_next;
		}
	}
}

void initWorker(int *sockfd, char *port, struct addrinfo *client_info, struct addrinfo **client_pointer, char *ip_address)
{
	if (!getaddrinfo(ip_address,port,client_info,client_pointer)) {
		struct addrinfo *traverse=*client_pointer;
		while (traverse) {
			if ((*sockfd=socket(traverse->ai_family, traverse->ai_socktype, traverse->ai_protocol)) != -1) {
				if (connect(*sockfd,traverse->ai_addr,traverse->ai_addrlen) != -1) {
					printf ("Connection Established\n");
					break;
				}
			}
			traverse=traverse->ai_next;
		}
	}
}
