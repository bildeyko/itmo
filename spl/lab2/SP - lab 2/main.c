#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#include "bmpStruct.h"
#include "workWithFile.h"
#include "flipFunctions.h"
#include "tools.h"
#include "constants.h"

/*
TODO:
1. Add command in mmx code which cleared FPU (  I don't remember name of this command) +
2. Write flip function in C without mempcy.Make the transfer of 4 bytes +-
3. Try to use REP command in asm function
4. Read about optimization in C
*/

typedef void(*flipFunc_pointer_t)(unsigned char * imageArray, imageInfoStruct imageInfo);

int doFlip(char *label, char *suffix, int reps, unsigned char * imageArr, imageInfoStruct imageIn, bmpFileStruct sourceFile, char *path,
	flipFunc_pointer_t flipFunc)
{
	clock_t time;
	clock_t allTime;
	int i;

	printf("\n");
	printf("%s\n", label);
	printf(" Process:\n");
	allTime = 0;
	for (i = 0; i<reps; i++) {
		time = clock();
		(*flipFunc)(imageArr, imageIn);
		time = clock() - time;
		allTime += time;
		printf("\r  %d%%", ((i + 1) * 100 / reps));
	}
	printf("\n");
	fprintf(stderr, " Time:\n  %d clock ticks (%f seconds)\n", allTime, ((float)allTime) / CLOCKS_PER_SEC);
	safeImageFile(path, suffix, &sourceFile, &imageArr);
}

int main(int argc, char** argv) 
{
	int i;
	imageInfoStruct imageInfo;
	bmpFileStruct sourceFile;
	unsigned char *imageArray;
	char path[BUFFER_SIZE];
	char *label;
	int reps;
	clock_t time;
	clock_t allTime;	
	flipFunc_pointer_t func;

	reps = DEF_REPS;
	strcpy(path, "");
	printf("\n");


	/*
	The parser of string with parameters.
	*/
	for (i=1; i<argc; i++) 
	{
		if(argv[i][0] == '-') 
		{
			switch (argv[i][1])
			{
			case 'p':
				strncpy(path, &argv[i][2], BUFFER_SIZE);
				path[BUFFER_SIZE - 1] = '\0';
				break;
			case 'r':
				reps = strtol(&argv[i][2], NULL, 0);
				if (reps == 0)
					showError("Wrong the number of repetitions.");
				break;
			default:
				printf("Wrong argument: %s\n", argv[i]);
				usage();
			}
		}
		if(argv[i][0] == '/') 
		{
			switch (argv[i][1])
			{
				case '?':
					usage();
					break;
				default:
					printf("Wrong argument: %s\n", argv[i]);
					usage();
			}
		}
	}

	if (strlen(path) == 0)
		usage();

	printf("Path to BMP file: %s\n", path);
	printf("Reps: %d\n",reps);

	imageInfo = loadImageFile(path, &sourceFile, &imageArray);

	printf("Resolution: %dx%d\n", imageInfo.width, imageInfo.height);
	
	func = &flipImageC;
	label = "Test 1 - using pure C";
	doFlip(label, "_1_c_", reps, imageArray, imageInfo, sourceFile, path, func);

	func = &flipImageC_memcpy;
	label = "Test 2 - using C with memcpy function";
	doFlip(label, "_2_c_memcpy_", reps, imageArray, imageInfo, sourceFile, path, func);

	func = &flipImageAsm;
	label = "Test 3 - using pure Asm";
	doFlip(label, "_3_asm_", reps, imageArray, imageInfo, sourceFile, path, func);

	func = &flipImageMMX;
	label = "Test 4 - using asm with MMX";
	doFlip(label, "_4_mmx_", reps, imageArray, imageInfo, sourceFile, path, func);

	free(imageArray);
	return 0;
}