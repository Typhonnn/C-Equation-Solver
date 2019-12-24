#pragma once
#include "allEquations.h"

typedef struct {
	int count;
	float **A_Mat;
	float *B_Vec;
	float Detrmin;
	float *X_Vec;
} Solver;

//Generic function that takes a matrix and size and prints it.
void printMatrix(float **mat, int size);

//Takes a solution's array and prints it in a column.
void printSolVec(float *vec, int size);

//Takes an array and prints it in column.
void printVector(float *vec, int size);

//Takes an allocated struct Solver and setting it up with data from struct AllEquations.
void setSolverMatrix(Solver *solver, AllEquations *allEq);

//Takes an allocated struct Solver and allocating memory for pointers in it.
void setSolver(Solver *solver, AllEquations *allEq);

