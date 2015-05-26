#ifndef IO_H
#define IO_H

#include <unistd.h>
#include <stddef.h>
#include <string.h>

void print(const char* str);
void error(const char* err);
void print_diff(char* path1, char* path2, int chr, int line);
void print_lflag(size_t count, int n1, int n2);
void print_eof(char* path);
void sys_error(const char* err);

#endif
