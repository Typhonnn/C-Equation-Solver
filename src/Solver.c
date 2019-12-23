#include <stdio.h>
#include <stdlib.h>
#include "Solver.h"

void printMatrix(float **mat, int size) {
	int i, j;
	printf("\nMatrix A = \n");
	for (i = 0; i < size; i++) {
		for (j = 0; j < size; j++) {
			printf("\t%.3f ", mat[i][j]);
		}
		printf("\n");
	}
}

void printSolVec(float *vec, int size) {
	int i;
	printf("\nVector X = \n");
	for (i = 0; i < size; ++i) {
		printf("\t%c = %.3f\n", 'x' + i, vec[i]);
	}
}

void printVector(float *vec, int size) {
	int i;
	printf("\nVector B = \n");
	for (i = 0; i < size; ++i) {
		printf("\t%.3f\n", vec[i]);
	}
}

void setSolverMatrix(Solver *solver, AllEquations *allEq) {
	int i, j;
	for (i = 0; i < solver->count; ++i) {
		for (j = 0; j < solver->count; ++j) {
			solver->A_Mat[i][j] = allEq->eqArr[i]->A[j];
		}
		solver->B_Vec[i] = allEq->eqArr[i]->B;
	}
}

void setSolver(Solver *solver, AllEquations *allEq) {
	int i;
	solver->count = allEq->count;
	solver->A_Mat = malloc(solver->count * sizeof(float*));
	for (i = 0; i < solver->count; ++i) {
		solver->A_Mat[i] = malloc(solver->count * sizeof(float));
	}
	if (solver->A_Mat == NULL) {
		printf("ERROR! COULD NOT MALLOC solver->A_Mat!");
		return;
	}
	solver->B_Vec = malloc(solver->count * sizeof(float*));
	if (solver->B_Vec == NULL) {
		printf("ERROR! COULD NOT MALLOC solver->B_Vec!");
		return;
	}
	setSolverMatrix(solver, allEq);
}
