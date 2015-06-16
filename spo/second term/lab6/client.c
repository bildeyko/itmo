#include <stdlib.h>
#include <stdio.h>
#include <unistd.h> 
#include <sys/types.h> 
#include <sys/socket.h>
#include <arpa/inet.h>

#define BUFFER_SIZE 1024

void 
usage()
{
	printf("usage: client -h host -p port dir1 .... dirN\n");
	exit(1);
}

void 
error(const char* err)
{
	perror(err);
	exit(1);
}

int 
main(int argc, char  *argv[])
{
	int opt, index, n, sockfd;
	struct sockaddr_in server;
	char *host = NULL;
	char * pch;
	int port = -1;
	char buffer[BUFFER_SIZE] = {0};
	
	while((opt = getopt(argc,argv,"h:p:")) != -1) {
		switch (opt) {
			case 'h':
				host = optarg;
				break;
			case 'p':
				port = atoi(optarg);
				break;
			default:
				usage();			
		}
	}
	if (argc < 1)
		usage();
	
	if (host == NULL || port == -1)
		usage();	

	bzero((char *) &server, sizeof(server));
	
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = inet_addr(host);;
	server.sin_port = htons(port);
	
	if ( (sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
		error("socket");
	
	if (connect(sockfd, (struct sockadd *) &server, sizeof(server)) < 0)
		error("connect");
	
	printf("host: %s port: %d - connected\n", host, port);
	
	for (index = optind; index < argc; index++) {
		printf("%s\n", argv[index]);
		
		if (write(sockfd , argv[index] , strlen(argv[index])) < 0)
			error("write");
		
		while (1) {
			bzero(&buffer, BUFFER_SIZE);
			if ( (n = read(sockfd, buffer, BUFFER_SIZE)) > 0)
			{
				pch=strchr(buffer,'/');
				if (pch != NULL)
				{
					*pch = '\0';
					printf("%s", buffer);
					bzero(&buffer, BUFFER_SIZE);
					break;
				} else
					printf("%s", buffer);				
			}
			if (n == 0) {
				printf("Disconnection\n");
				break;
			} else if (n < 0) {
				error("recv");
			}
		}
	}
		
	return 0;
}
