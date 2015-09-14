#include <stdio.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <dirent.h>

#define BUFFER_SIZE 1024

void doaction(int sock);

void 
error(const char* err)
{
	perror(err);
	exit(1);
}

int 
main(int argc, char  *argv[])
{
	int sockfd, newsockfd, port, pid, clilen;
	struct sockaddr_in server, client;
	int reuse = 1;
	
	if(argc != 2) {
		printf("usage: server port\n");
		exit(1);
	}
	
	if ( (sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
		error("socket");
	
	bzero((char *) &server, sizeof(server));
	port = atoi(argv[1]);
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = INADDR_ANY;
	server.sin_port = htons(port);
	
	if (bind (sockfd, (struct sockadd *) &server, sizeof(server)) < 0)
		error("bind");
	if (setsockopt (sockfd, SOL_SOCKET, SO_REUSEADDR, &reuse,
		sizeof(reuse)) < 0)
		error("setsockopt");
		
	listen(sockfd, 5);
	clilen = sizeof(client);
	while (1) {
		newsockfd = accept(sockfd, 
					(struct sockadd *) &client, &clilen);
		if (newsockfd < 0)
			error("accept");
			pid = fork();
			if (pid < 0 )
				error("fork");
			if (pid == 0) {
				close(sockfd);
				doaction(newsockfd);
				exit(0);
			}
			else close(newsockfd);
	}
	
	return 0;
}

void
doaction(int sock)
{
	ssize_t n;
	char buffer[BUFFER_SIZE] = {0};
	DIR *dir;
    struct dirent *dp;
	int telnet = 0;
	char * pch;
	
	while ( (n = read(sock, buffer, BUFFER_SIZE)) > 0)
	{		
		pch=strchr(buffer,'\r');
		if (pch != NULL)
		{
			telnet = 1;
			buffer[n-2] = 0;
		}
		
		if ((dir = opendir (buffer)) == NULL) {
			char str1[] = "\tCan't open the ";
			write(sock , str1 , strlen(str1));
			write(sock , buffer , strlen(buffer));
			write(sock , "\n" , 1);
			if (telnet == 0)
				write(sock , "/" , 1);
			bzero(&buffer, BUFFER_SIZE);
			continue;
		}
		
		while ((dp = readdir(dir)) != NULL) {
			write(sock , "\t" , 1);
			write(sock , dp->d_name , strlen(dp->d_name));
			write(sock , "\n" , 1);
		}
		if (telnet == 0)
			write(sock , "/" , 1);
		
		bzero(&buffer, BUFFER_SIZE);
		
		if (closedir(dir) < 0)
			error("closedir");
	}
	if (n == 0) {
		printf("Client disconnected\n");
	} else if (n < 0) {
		error("recv");
	}
}
