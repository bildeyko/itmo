#include <stdio.h>
#include "tools.h"
#include "constants.h"

void showError(char text[])
{
	fprintf(stderr, "Error: %s\n", text);
}

void usage()
{
	printf("-= SuperBench =-\n");
	printf("About:\n");
	printf(" This benchmark flips your image using pure C, assembler and MMX.\n");
	printf(" The benchmark returns the time of each test in clock ticks and seconds.\n");
	printf("Usage:\n");
	printf(" /? - help\n");
	printf(" -p<string> - path to BMP file\n");
	printf(" -r<number> - number of repetitions of image transformation. Default: %d\n", DEF_REPS);
	exit(1);
}