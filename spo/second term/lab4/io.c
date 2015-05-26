#include "io.h"
#include <errno.h>

void print_err(const char* err);

void print(const char* str)
{
	if( write(STDOUT_FILENO, str, strlen(str)) < 0 )
		sys_error("write");
}

void print_err(const char* err)
{
	if( write(STDERR_FILENO, err, strlen(err)) < 0 ) 
		sys_error("write");
}

void print_diff(char* path1, char* path2, int chr, int line)
{
	char chr_tmp[12]={0x0};
	sprintf(chr_tmp,"%d", chr);
	char line_tmp[12]={0x0};
	sprintf(line_tmp,"%d", line);
	
	print(path1);
	print(" ");
	print(path2);
	print(" differ: char ");
	print(chr_tmp);
	print(", line ");
	print(line_tmp);
	print("\n");
}

void print_lflag(size_t count, int n1, int n2) 
{
	char count_tmp[12]={0x0};
	sprintf(count_tmp,"%d", count);
	char n1_tmp[4]={0x0};
	sprintf(n1_tmp,"%d", n1);
	char n2_tmp[4]={0x0};
	sprintf(n2_tmp,"%d", n2);
	
	print(count_tmp);
	print("\t");
	print(n1_tmp);
	print("\t");
	print(n2_tmp);
	print("\n");
}

void print_eof(char* path)
{
	print("bcmp: EOF on ");
	print(path);
	print("\n");
}

void error(const char* err)
{
	print_err("bcmp: ");
	print_err(err);
	print("\n");
	_exit(1);
}

void sys_error(const char* err)
{
	char errno_tmp[4]={0x0};
	sprintf(errno_tmp,"%d", errno);
	
	print_err("bcmp: ");
	print_err(errno_tmp);
	print_err(" ");
	perror(err);
	
	_exit(1);
}
