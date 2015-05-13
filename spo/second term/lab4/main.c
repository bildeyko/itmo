#include <stdio.h>
#include <errno.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stddef.h>
#include "io.h"

#define BUFFSIZE 4096

static int lflag;
static int sflag;

int compare(char* argv[], int flds1, int flds2);
int dec_to_oct(int num);
void usage();

int main(int argc, char  *argv[])
{
	off_t offset1, offset2, currpos;
	int res, flds1=STDIN_FILENO, flds2=STDIN_FILENO;
	
	while((res = getopt(argc,argv,"ls")) != -1) {
		switch (res) {
		case 'l':
			lflag = 1;
			break;
		case 's':
			sflag = 1;
			break;
		case '?':
		default:
			usage();
		}
	}	
	argc -= optind;
	argv += optind;	
	
	if(argc < 2)
		usage();
	
	if(lflag && sflag)
		error("the -l and -s options may not be specified together");
	
	if(!strcmp(argv[0], "-") && !strcmp(argv[1], "-") )
		usage();
	if(strcmp(argv[0], "-"))
		if ((flds1 = open(argv[0], O_RDONLY)) < 0)
			if(!sflag) sys_error("open");
	if(strcmp(argv[1], "-"))
		if ((flds2 = open(argv[1], O_RDONLY)) < 0)
			if(!sflag) sys_error("open");
		
	if(argc>2){
		offset1 = atoi(argv[2]);
		if ( (currpos = lseek(flds1, offset1, SEEK_SET)) < 0 )
			if(!sflag) sys_error("lseek");
		if(argc>3){
			offset2 = atoi(argv[3]);
			if ( (currpos = lseek(flds2, offset2, SEEK_SET)) < 0 )
				if(!sflag) sys_error("lseek");
		}
	}
	
	_exit(compare(argv, flds1, flds2));
}

int compare(char* argv[], int flds1, int flds2)
{
	int n1, n2, i;
	size_t c_count, l_count;
	unsigned char buf1[BUFFSIZE], buf2[BUFFSIZE];
	c_count = 1;
	l_count = 1;
	
	while ( (n1 = read(flds1, buf1, BUFFSIZE)) > 0 &&
				(n2 = read(flds2, buf2, BUFFSIZE)) > 0) {					
		for(i=0; i<( (n1<n2) ? n1 : n2 ); i++) {
			if(buf1[i] != buf2[i]) {
				if(!lflag) {
					if(!sflag) print_diff(argv[0], argv[1], c_count, l_count);
					goto Exit;
				} else 
					print_lflag(c_count,  dec_to_oct(buf1[i]), dec_to_oct(buf2[i]));
			}
			if(buf1[i] == '\n')
				l_count ++;
			c_count ++;
		}
		
		if (n1 < n2) {
			if(!sflag) print_eof(argv[0]);
			break;
		} else if (n1 > n2) {
			if(!sflag) print_eof(argv[1]);
			break;
		}
	}
	
	if(n1<0 || n2<0)
		if(!sflag) sys_error("read");
	
Exit:
	close(flds1);
	close(flds2);
	return 0;
}

int dec_to_oct(int num) 
{
	int rem, i=1, octal=0;
    while (num!=0)
    {
        rem=num%8;
        num/=8;
        octal+=rem*i;
        i*=10;
    }
    return octal;
}

void usage()
{
	if(!sflag)
		print("usage: cmp [-l | -s] file1 file2 [skip1] [skip2]\n");
	_exit(1);
}
