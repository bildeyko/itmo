#include <stdio.h>
#include "tools.h"

void showError(char text[])
{
	fprintf(stderr, "Error: %s\n", text);
}