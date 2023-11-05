/*
 * multiThreadedProgramExample.c
 *
 *  Created on: 11 janv. 2021
 *      Author: laloukil
 */

#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

extern int **A; // Matrix elements
extern int **B; // Matrix elements
extern int **C; // Matrix elements
extern int n;   // Matrix dimension
int nt;   // Numberof threads

void threadFunction(void *args);

void launchThreads(int N)
{
    nt = N;
    printf("Launching %d threads\n", N);
    // allocate space for storing N threads
    pthread_t *threads = (pthread_t *)malloc(sizeof(pthread_t) * N);

    // spawn off N threads, each calling threadFunction(i)
    long th;
    int rc;
    clock_t begin, end;
    double elapsedTime;
    begin = clock();
    for (th = 0; th < N; th++)
    {
        rc = pthread_create(&threads[th], NULL, (void *)threadFunction, (void *)th);
        if (rc)
        {
            printf("Failed to create thread; error code: %d\n", rc);
            exit(-1);
        }
    }

    // Joining the N threads
    for (th = 0; th < N; th++)
        pthread_join(threads[th], NULL);
    end = clock();
    elapsedTime = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("Total time taken by CPU: %f\n", elapsedTime);
}

void threadFunction(void *args)
{
    long tId = (long)args;

    int taille = ceil(((double)n / (double)nt));

    int debut = tId * taille;
    int fin = debut + taille - 1;

    for (int i = debut; i <= fin; ++i)
    {
        if (i >= n)
        {
            break;
        }
        for (int j = 0; j < n; ++j)
        {
            for (int k = 0; k < n; ++k)
            {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }

    pthread_exit(0);
}