// Title:			              querier.c
// Creator:			            John Coleman
// Creation Date:		        02.05.2024
// Modification Date:      	02.27.2024
// Desscription:             
// A basic DNS client that queries a hostname, 
// and prints the IP's to stanard out.
//
// Progress:			Work in progress.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>

#define IPBUF 256

int main(int argc, char *argv[])
{
	struct addrinfo ipinfo;
	struct addrinfo *result, *vector;
	int sfd, aret;
	size_t len;
	ssize_t nread;
	char ip[IPBUF];

	if(argc<2 || argc>2)
	{
		fprintf(stdout, "Usage: %s host\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	/* Obtain address(es) matching host/port */
	memset(&ipinfo, 0, sizeof(struct addrinfo));
	ipinfo.ai_family = AF_UNSPEC;
	ipinfo.ai_socktype = SOCK_DGRAM;
	ipinfo.ai_flags = 0;
	ipinfo.ai_protocol = 0;

	aret = getaddrinfo(argv[1], NULL, &ipinfo, &result);
	if(aret!=0)
	{
		fprintf(stdout, "getaddrinfo: %s\n", gai_strerror(aret));
		exit(EXIT_FAILURE);
	}

	for(vector=result; vector!=NULL; vector=vector->ai_next)
	{
		getnameinfo(vector->ai_addr, vector->ai_addrlen, ip, sizeof(ip), NULL, 0, NI_NUMERICHOST);
		fprintf(stdout, "%s\n", ip);
	}

	return 0;
}
