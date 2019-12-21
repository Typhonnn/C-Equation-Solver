#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "allEquations.c"
#include "Solver.c"

#define EQ_SIZE 80
#define MAX_EQUATIONS 3

void printAllEquations(AllEquations *allEq) {
	int i, j;
	for (i = 0; i < allEq->count; i++) {
		for (j = 0; j < allEq->count; j++) {
			printf("%.3f ", allEq->eqArr[i]->A[j]);
		}
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

void calDetrmin(Solver *solver) {


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
	calDetrmin(solver);
	return 0;
}
