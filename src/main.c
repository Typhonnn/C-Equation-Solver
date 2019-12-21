#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "allEquations.c"
#include "Solver.c"

#define EQ_SIZE 80
#define MAX_EQUATIONS 3

void printVector(float *vec, int size) {
	int i;
	printf("Vector B = \n");
	for (i = 0; i < size; ++i) {
		printf("\t%.3f\n", vec[i]);
	}
}

void printMatrix(float **matrix, int size) {
	int i, j;
	printf("Matrix A = \n");
	for (i = 0; i < size; i++) {
		for (j = 0; j < size; j++) {
			printf("\t%.3f ", matrix[i][j]);
		}
		printf("\n");
	}
}

void* setEquation(AllEquations *allEq, char *eqStr) {
	char eqCpy[EQ_SIZE];
	char *delimiters = " *+=";
	float num;
	int i = 0;
	char var[MAX_EQUATIONS];
	Equation *tempEq = malloc(sizeof(Equation));
	if (tempEq == NULL) {
		printf("ERROR! COULD NOT MALLOC tempEq!");
		return NULL;
	}
	tempEq->count = allEq->count;
	tempEq->A = malloc(allEq->count * sizeof(float));
	if (tempEq->A == NULL) {
		printf("FAILED TO MALLOC tempEq->A!\n");
		return NULL;
	}
	strcpy(eqCpy, eqStr);
	char *splitEq = strtok(eqCpy, delimiters);
	while (splitEq != NULL) {
		sscanf(splitEq, "%f", &num);
		splitEq = strtok(NULL, delimiters);
		if (splitEq != NULL) {
			sscanf(splitEq, "%c", &var[i]);
			(tempEq->A[var[i] - 'x']) = num;
			splitEq = strtok(NULL, delimiters);
			i++;
		}
	}
	tempEq->B = num;
	return tempEq;
}

void setAllEquations(AllEquations *allEq) {
	int i = 0;
	char eqStr[EQ_SIZE];
	for (i = 0; i < (allEq->count); ++i) {
		printf("Enter equation %d: ", i + 1);
		scanf("%s", eqStr);
		allEq->eqArr[i] = setEquation(allEq, eqStr);
		memset(eqStr, 0, EQ_SIZE);
	}
}

void setSolverMatrix(Solver *solver, AllEquations *allEq) {
	int i;
	for (i = 0; i < solver->count; ++i) {
		solver->A_Mat[i] = allEq->eqArr[i]->A;
		solver->B_Vec[i] = allEq->eqArr[i]->B;
	}
}

void setSolver(Solver *solver, AllEquations *allEq) {
	solver->count = allEq->count;
	solver->A_Mat = malloc(solver->count * sizeof(float*));
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

float calDetrmin(float **A_Mat, int size) {
	float x, y, z;
	if (size == 1) {
		return A_Mat[0][0];
	}
	if (size == 2) {
		return A_Mat[0][0] * A_Mat[1][1] - A_Mat[0][1] * A_Mat[1][0];
	}
	if (size == 3) {
		x = A_Mat[1][1] * A_Mat[2][2] - A_Mat[2][1] * A_Mat[1][2];
		y = A_Mat[1][0] * A_Mat[2][2] - A_Mat[2][0] * A_Mat[1][2];
		z = A_Mat[1][0] * A_Mat[2][1] - A_Mat[2][0] * A_Mat[1][1];
		return A_Mat[0][0] * x - A_Mat[0][1] * y + A_Mat[0][2] * z;
	}
	return 0;
}

float* calVecSol(Solver *solver) {
	float x, y, z;
	float *X_Vec = malloc(solver->count * sizeof(float));
	if (X_Vec == NULL) {
		printf("ERROR! COULD NOT MALLOC X_Vec!");
		return 0;
	}
	if (solver->count == 1) {
		*X_Vec = *solver->B_Vec / solver->Detrmin;
	}
	if (solver->count == 2) {

	}
	if (solver->count == 3) {

	}
	return X_Vec;
}

int main() {
	AllEquations *allEq = malloc(sizeof(AllEquations));
	if (allEq == NULL) {
		printf("ERROR! COULD NOT MALLOC AllEquations!");
		return 0;
	}
	printf("Number of equations: ");
	scanf("%d", &(allEq->count));
	allEq->eqArr = malloc(allEq->count * sizeof(Equation*));
	if ((allEq->eqArr) == NULL) {
		printf("ERROR! COULD NOT MALLOC eqArr!");
		return 0;
	}
	setAllEquations(allEq);
	Solver *solver = malloc(sizeof(Solver));
	if (solver == NULL) {
		printf("ERROR! COULD NOT MALLOC SOLVER!");
		return 0;
	}
	setSolver(solver, allEq);
	printMatrix(solver->A_Mat, solver->count);
	solver->Detrmin = calDetrmin(solver->A_Mat, solver->count);
	if (solver->Detrmin == 0) {
		printf("Matrix A determinant = %.3f\n", solver->Detrmin);
	}
	printVector(solver->B_Vec, solver->count);
	if (solver->Detrmin == 0) {
		printf("There is no single solution for that system of equations.\n");
	} else {
		solver->X_Vec = calVecSol(solver);
	}
	return 0;
}
