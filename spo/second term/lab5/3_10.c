#include <stdio.h>
#include <unistd.h>
#include <sys/types.h> 

#define UTIL "/usr/bin/wc"

void print_err(const char* err);

int 
main(int argc, char  *argv[])
{
	FILE *fp;
	int fd[2];
	pid_t pid;
	char ch;
	size_t count;
	
	if (argc != 2) {
		printf("usage: 3_10 file\n");
		exit(1);
	}

	if ( (fp = fopen(argv[1], "r")) == NULL) 
		print_err("cannot open the file");
	if (pipe(fd) < 0)
		print_err("pipe");
	
	if ( (pid = fork()) < 0)
		print_err("fork");
	else if (pid > 0) { /* parent process */
		close(fd[0]);
		
		count = 0;
		while (1)
		{
			ch = fgetc(fp);
			if(ferror(fp))
				print_err("fgetc");
			if(ch == EOF)
				break;
			if( (++count)%2 == 0) 
				if(write(fd[1], &ch, 1) != 1)
					print_err("write");
		}
		
		close(fd[1]);
		if (waitpid(pid, NULL, 0) < 0)
			print_err("waitpid");
		
		exit(0);		
	} else {  /* child process */
		close(fd[1]);
		if(dup2(fd[0], STDIN_FILENO) != STDIN_FILENO)
			print_err("dup2");
			
		close(fd[0]);
		
		if (execl(UTIL, UTIL, (char *)0) < 0)
			print_err("execl");
	}
	exit(0);
}

void 
print_err(const char* err)
{
	perror(err);
	exit(1);
}
