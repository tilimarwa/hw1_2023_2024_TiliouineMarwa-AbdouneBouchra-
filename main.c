#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include "initMatrix.h"
#include "displayMatrix.h"
#include "multiThreadedProgramExample.h"

	int n;  	// Matrix size
	int **A;	// Matrix elements
	int **B;	// Matrix elements
	int **C;	// Matrix elements
	int sharedSum;


int main(int argc, char **argv) {

	if (argc < 3){
		printf("Usage: ./mmm <mode> [num threads] <size>\n");
		printf("<mode>: S (sequential); P (parallel)\n");
		printf("[num threads]: # of threads to run, 1 by default\n");
		printf("<size>: Matrix size\n");
		return 1;
	}

	char* mode = argv[1];
	
	if ((!strcmp(mode, "S")) || (!strcmp(mode, "s")))
		printf("Sequential execution\n");
	else if ((!strcmp(mode, "P")) || (!strcmp(mode, "p")))
		printf("Parallel execution\n");
		else {
		 printf("Invalid execution mode\n");
		 exit(0);
		}
	int numThreads; // Number of threads
	int i, j;

	if ((!strcmp(mode, "S")) || (!strcmp(mode, "s"))) {
		printf("Mode: Sequential\n");
		numThreads = 1;
		n = atoi (argv[2]);
	}
		
	if ((!strcmp(mode, "P")) || (!strcmp(mode, "p"))){
		printf("Mode: Parallel\n");
		numThreads = atoi (argv[2]);
		n = atoi (argv[3]);
	}

	if (n <= 1){
		printf("Warning: Matrix size must be > 2\n");
		exit (1);
	}

	if (numThreads < 1){
		printf("Warning: Num threads must be >= 1.\n");
		exit (1);
	}
	printf("# of threads: %d\n", numThreads);
	printf("Matrix size: %d\n", n);

	A = (int **)malloc(n * sizeof(int *));
	for (i = 0; i < n; i++)
		A[i] = (int *)malloc(n * sizeof(int));

	generateRandomMatrix(A, n, 0, 99);
	printMatrix(A, n);
	printf("\n");
		B = (int **)malloc(n * sizeof(int *));
	for (i = 0; i < n; i++)
		B[i] = (int *)malloc(n * sizeof(int));

	generateRandomMatrix(B, n, 0, 99);
	printMatrix(B, n);
		C = (int **)malloc(n * sizeof(int *));
	for (i = 0; i < n; i++)
		C[i] = (int *)malloc(n * sizeof(int));

	generateRandomMatrix(C, n, 0, 0);

	launchThreads(numThreads);

    printMatrix(C, n);
	// Freeing up memory space for matrix A.
	for (i = 0; i < n; ++i) {
		free(A[i]);
	}
	free(A);

	return 0;
}
