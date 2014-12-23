#include <stdio.h>
#include "tools.h"

void showError(char text[])
{
	fprintf(stderr, "Error: %s\n", text);
	exit(1);
}

void add_error(int err)
{
	if (err == 1)
		showError("Wrong source index.");
	if (err == 2)
		showError("Wrong direction index.");
}

void usage()
{
	printf("Usage: nbgrep [OPTION] ... PATTERN < [FILE]\n");
	printf(" ^Q \t exit\n");
	printf("Options:\n");
	printf(" -i \t ignores upper/lower case\n");
	printf(" -n \t print line number (first line is 1)\n");
	printf(" -h \t display this help and exit\n");
	printf(" -t \t print an execution time of the program\n");
	printf(" -v \t select non-matching lines\n");
	printf(" -c \t only print a count of matching lines\n");
	printf(" -s \t use implementation on a set data type\n");	
	printf("Regexp synopsis:\n");
	printf(" () \t defines a marked subexpression\n");
	printf(" . \t matches any single character\n");
	printf(" ^ \t matches the starting position within the string\n");
	printf(" $ \t matches the ending position within the string\n");
	printf(" * \t matches the preceding element zero or more times\n");
	printf(" + \t matches the preceding element one or more times\n");
	printf(" ? \t matches the preceding element zero or one time\n");
	printf(" (A|B) \t matches either the expression before or the expression after the operator\n");
	exit(1);
}