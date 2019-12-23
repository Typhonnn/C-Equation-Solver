#pragma once
#include "allEquations.h"

typedef struct {
	int count;
	float **A_Mat;
	float *B_Vec;
	float Detrmin;
	float *X_Vec;
} Solver;

void printMatrix(float **mat, int size);

void printSolVec(float *vec, int size);

void printVector(float *vec, int size);

void setSolverMatrix(Solver *solver, AllEquations *allEq);

void setSolver(Solver *solver, AllEquations *allEq);

