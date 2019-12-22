#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "allEquations.c"
#include "Solver.c"

#define EQ_SIZE 80
#define MAX_EQUATIONS 3

void cpyMat(float **dest, float **src, int size) {
	int i, j;
	for (i = 0; i < size; ++i) {
		for (j = 0; j < size; ++j) {
			dest[i][j] = src[i][j];
		}
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
		memset(eqStr, '\0', EQ_SIZE);
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

float calDetrmin(float **Mat, int size) {
	float x, y, z;
	if (size == 1) {
		return Mat[0][0];
	}
	if (size == 2) {
		return Mat[0][0] * Mat[1][1] - Mat[0][1] * Mat[1][0];
	}
	if (size == 3) {
		x = Mat[1][1] * Mat[2][2] - Mat[2][1] * Mat[1][2];
		y = Mat[1][0] * Mat[2][2] - Mat[2][0] * Mat[1][2];
		z = Mat[1][0] * Mat[2][1] - Mat[2][0] * Mat[1][1];
		return Mat[0][0] * x - Mat[0][1] * y + Mat[0][2] * z;
	}
	return 0;
}

void* calVecSol(Solver *solver) {
	int i;
	float x, y, z;
	float *X_Vec = malloc(solver->count * sizeof(float));
	if (X_Vec == NULL) {
		printf("ERROR! COULD NOT MALLOC X_Vec!");
		return 0;
	}
	float **matCpy = malloc(solver->count * sizeof(float*));
	for (i = 0; i < solver->count; ++i) {
		matCpy[i] = malloc(solver->count * sizeof(float));
	}
	if (matCpy == NULL) {
		printf("ERROR! COULD NOT MALLOC matCpy!");
		return NULL;
	}
	if (solver->count == 1) {
		X_Vec[0] = solver->B_Vec[0] / solver->Detrmin;
	}
	if (solver->count == 2) {
		cpyMat(matCpy, solver->A_Mat, solver->count);
		matCpy[0][0] = solver->B_Vec[0];
		matCpy[1][0] = solver->B_Vec[1];
		x = calDetrmin(matCpy, solver->count) / solver->Detrmin;
		cpyMat(matCpy, solver->A_Mat, solver->count);
		matCpy[0][1] = solver->B_Vec[0];
		matCpy[1][1] = solver->B_Vec[1];
		y = calDetrmin(matCpy, solver->count) / solver->Detrmin;
		X_Vec[0] = x;
		X_Vec[1] = y;
	}
	if (solver->count == 3) {
		cpyMat(matCpy, solver->A_Mat, solver->count);
		matCpy[0][0] = solver->B_Vec[0];
		matCpy[1][0] = solver->B_Vec[1];
		matCpy[2][0] = solver->B_Vec[2];
		x = calDetrmin(matCpy, solver->count) / solver->Detrmin;
		cpyMat(matCpy, solver->A_Mat, solver->count);
		matCpy[0][1] = solver->B_Vec[0];
		matCpy[1][1] = solver->B_Vec[1];
		matCpy[2][1] = solver->B_Vec[2];
		y = calDetrmin(matCpy, solver->count) / solver->Detrmin;
		cpyMat(matCpy, solver->A_Mat, solver->count);
		matCpy[0][2] = solver->B_Vec[0];
		matCpy[1][2] = solver->B_Vec[1];
		matCpy[2][2] = solver->B_Vec[2];
		z = calDetrmin(matCpy, solver->count) / solver->Detrmin;
		X_Vec[0] = x;
		X_Vec[1] = y;
		X_Vec[2] = z;
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
	printf("\nMatrix A determinant = %.3f\n", solver->Detrmin);
	printVector(solver->B_Vec, solver->count);
	if (solver->Detrmin == 0) {
		printf("There is no single solution for that system of equations.\n");
	} else {
		solver->X_Vec = calVecSol(solver);
		printSolVec(solver->X_Vec, solver->count);
	}
	return 0;
}
