#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "allEquations.h"
#include "Solver.h"

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
	float dx, dy, dz;
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
		dx = calDetrmin(matCpy, solver->count);
		cpyMat(matCpy, solver->A_Mat, solver->count);
		matCpy[0][1] = solver->B_Vec[0];
		matCpy[1][1] = solver->B_Vec[1];
		dy = calDetrmin(matCpy, solver->count);
		X_Vec[0] = dx / solver->Detrmin;
		X_Vec[1] = dy / solver->Detrmin;
	}
	if (solver->count == 3) {
		cpyMat(matCpy, solver->A_Mat, solver->count);
		matCpy[0][0] = solver->B_Vec[0];
		matCpy[1][0] = solver->B_Vec[1];
		matCpy[2][0] = solver->B_Vec[2];
		dx = calDetrmin(matCpy, solver->count);
		cpyMat(matCpy, solver->A_Mat, solver->count);
		matCpy[0][1] = solver->B_Vec[0];
		matCpy[1][1] = solver->B_Vec[1];
		matCpy[2][1] = solver->B_Vec[2];
		dy = calDetrmin(matCpy, solver->count);
		cpyMat(matCpy, solver->A_Mat, solver->count);
		matCpy[0][2] = solver->B_Vec[0];
		matCpy[1][2] = solver->B_Vec[1];
		matCpy[2][2] = solver->B_Vec[2];
		dz = calDetrmin(matCpy, solver->count);
		X_Vec[0] = dx / solver->Detrmin;
		X_Vec[1] = dy / solver->Detrmin;
		X_Vec[2] = dz / solver->Detrmin;
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
	getchar();
	allEq->eqArr = malloc(allEq->count * sizeof(Equation*));
	if (allEq->eqArr == NULL) {
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
	printf("Press any key to continue...");
	char standby;
	scanf("%c", &standby);
	return 0;
}
