#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "allEquations.h"
#include "Solver.h"

#define EQ_SIZE 80 //Max size for equation.
#define MAX_EQUATIONS 3 //Max number of equations.

//Free allocated memory in program.
void freeMem(Solver *solver, AllEquations *allEq) {
	int i, num;
	num = solver->count;
	for (i = 0; i < num; ++i) {
		free(allEq->eqArr[i]->A);
		free(allEq->eqArr[i]);
		free(solver->A_Mat[i]);
	}
	free(solver->X_Vec);
	free(solver->B_Vec);
	free(solver);
	free(allEq);
}

//Takes one matrix and copies it by value to another matrix.
void cpyMat(float **dest, float **src, int size) {
	int i, j;
	for (i = 0; i < size; ++i) {
		for (j = 0; j < size; ++j) {
			dest[i][j] = src[i][j];
		}
	}
}

//Takes a matrix and it's size and gives back it determinant.
float calDetrmin(float **Mat, int size) {
	float x, y, z; //Holds the solution for adjoint's determinant.
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

//Takes a fully defined struct Solver, and using Cramer's Rule to calculate
//the solutions for the matrix using a copy matrix to backup it's original values.
void* calVecSol(Solver *solver) {
	int i;
	float dx, dy, dz; //Holds the determinant with B vector switched in the variable's column.
	float *X_Vec = malloc(solver->count * sizeof(float)); //Allocate memory for Solver's solution vector.
	if (X_Vec == NULL) {
		printf("ERROR! COULD NOT MALLOC X_Vec!");
		return 0;
	}
	float **matCpy = malloc(solver->count * sizeof(float*)); //Allocate memory for copy matrix.
	if (matCpy == NULL) {
		printf("ERROR! COULD NOT MALLOC matCpy!");
		return NULL;
	}
	for (i = 0; i < solver->count; ++i) { //Setting up rows.
		matCpy[i] = malloc(solver->count * sizeof(float));
		if (matCpy[i] == NULL) {
			printf("ERROR! COULD NOT MALLOC matCpy!");
			return NULL;
		}
	}
	if (solver->count == 1) { //Placing solution in solution's vector for size 1.
		X_Vec[0] = solver->B_Vec[0] / solver->Detrmin;
	}
	if (solver->count == 2) { //Placing solution in solution's vector for size 2.
		cpyMat(matCpy, solver->A_Mat, solver->count); //Copy the matrix.
		matCpy[0][0] = solver->B_Vec[0]; //Switch row B with variable x column.
		matCpy[1][0] = solver->B_Vec[1];
		dx = calDetrmin(matCpy, solver->count); //Placing determinant of Matrix x switched into dx.
		cpyMat(matCpy, solver->A_Mat, solver->count); //Copy the matrix.
		matCpy[0][1] = solver->B_Vec[0]; //Switch row B with variable y column.
		matCpy[1][1] = solver->B_Vec[1];
		dy = calDetrmin(matCpy, solver->count); //Placing determinant of Matrix x switched into dy.
		X_Vec[0] = dx / solver->Detrmin; //Applying Cramer's Rule to calculate the solution of variables.
		X_Vec[1] = dy / solver->Detrmin;
	}
	if (solver->count == 3) { //Placing solution in solution's vector for size 3.
		cpyMat(matCpy, solver->A_Mat, solver->count); //Copy the matrix.
		matCpy[0][0] = solver->B_Vec[0]; //Switch row B with variable x column.
		matCpy[1][0] = solver->B_Vec[1];
		matCpy[2][0] = solver->B_Vec[2];
		dx = calDetrmin(matCpy, solver->count); //Placing determinant of Matrix x switched into dx.
		cpyMat(matCpy, solver->A_Mat, solver->count); //Copy the matrix.
		matCpy[0][1] = solver->B_Vec[0]; //Switch row B with variable y column.
		matCpy[1][1] = solver->B_Vec[1];
		matCpy[2][1] = solver->B_Vec[2];
		dy = calDetrmin(matCpy, solver->count); //Placing determinant of Matrix x switched into dy.
		cpyMat(matCpy, solver->A_Mat, solver->count); //Copy the matrix.
		matCpy[0][2] = solver->B_Vec[0]; //Switch row B with variable z column.
		matCpy[1][2] = solver->B_Vec[1];
		matCpy[2][2] = solver->B_Vec[2];
		dz = calDetrmin(matCpy, solver->count); //Placing determinant of Matrix x switched into dz.
		X_Vec[0] = dx / solver->Detrmin; //Applying Cramer's Rule to calculate the solution of variables.
		X_Vec[1] = dy / solver->Detrmin;
		X_Vec[2] = dz / solver->Detrmin;
	}
	for (i = 0; i < solver->count; ++i) {
		free(matCpy[i]);
	}
	free(matCpy);
	return X_Vec;
}

int main() {
	AllEquations *allEq = malloc(sizeof(AllEquations)); //Allocate memory for struct AllEquations.
	if (allEq == NULL) {
		printf("ERROR! COULD NOT MALLOC AllEquations!");
		return 0;
	}
	printf("Number of equations: ");
	scanf("%d", &(allEq->count)); //Placing user's choice for number of equations directly into allEq.
	getchar(); //flushing the \n.
	allEq->eqArr = malloc(allEq->count * sizeof(Equation*)); //Allocate memory for each equation inside allEq.
	if (allEq->eqArr == NULL) {
		printf("ERROR! COULD NOT MALLOC eqArr!");
		return 0;
	}
	setAllEquations(allEq);
	Solver *solver = malloc(sizeof(Solver)); //Allocate memory for struct Solver.
	if (solver == NULL) {
		printf("ERROR! COULD NOT MALLOC SOLVER!");
		return 0;
	}
	setSolver(solver, allEq); //Setting up the solver.
	printMatrix(solver->A_Mat, solver->count); //Printing the matrix with generic function.
	solver->Detrmin = calDetrmin(solver->A_Mat, solver->count); //Calculating the determinant of matrix with generix function.
	printf("\nMatrix A determinant = %.3f\n", solver->Detrmin); //Printing determinant.
	printVector(solver->B_Vec, solver->count); //Printing vector B.
	if (solver->Detrmin == 0) { //By Linear Algebra's rules if determinant is not zero THERE IS a single solution to the set of equations.
		printf("There is no single solution for that system of equations.\n");
	} else { //In case there is a single solution.
		solver->X_Vec = calVecSol(solver); //Calling function to calculate solution's vector.
		printSolVec(solver->X_Vec, solver->count); //Printing the solutions.
	}
	printf("Press any key to continue..."); //By request a holder to keep the program running.
	char standby;
	scanf("%c", &standby);
	freeMem(solver, allEq);
	return 0;
}
