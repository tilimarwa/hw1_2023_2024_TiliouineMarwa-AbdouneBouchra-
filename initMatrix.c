/*
 * init-matrix.c
 *
 *  Created on: 5 janv. 2021
 *      Author: laloukil
 */

#include <time.h>
#include <stdlib.h>

#include "initMatrix.h"

void generateRandomMatrix (int **matrix, int dim, int minValue, int maxValue) {
	srand(time(0));
	int i, j;
	for (i = 0; i < dim; ++i) {
		for (j = 0; j < dim; ++j) {
			matrix[i][j] = (rand() % (maxValue - minValue + 1)) + minValue;
		}
	}

}
