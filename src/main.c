#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "allEquations.c"

#define EQ_SIZE 80
#define MAX_EQUATIONS 3

void printEquation(Equation *tempEq) {
	int i;
	for (i = 0; i < tempEq->count; i++) {
		printf("Hi %.3f ", *(tempEq->A + i));
	}
}

void* setEquation(AllEquations *allEq, char *eqStr) {
	char eqCpy[EQ_SIZE];
	char *delimiters = " *+=";
	float num;
	int i = 0;
	char var[MAX_EQUATIONS];
	Equation *tempEq = malloc(sizeof(Equation));
	tempEq->count = allEq->count;
	tempEq->A = malloc(allEq->count * sizeof(float));
	if (tempEq->A == NULL || tempEq == NULL) {
		printf("FAILED TO MALLOC EQUATION!\n");
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
	printEquation(tempEq);
	return tempEq;
}

void setAllEquations(AllEquations *allEq) {
	int i = 0;
	char eqStr[EQ_SIZE];
	for (i = 0; i < (allEq->count); ++i) {
		printf("Enter equation %d: ", i + 1);
		scanf("%s", eqStr);
		*((allEq->eqArr) + i) = setEquation(allEq, eqStr);
		if (((allEq->eqArr) + i) == NULL) {
			return;
		}
		memset(eqStr, 0, EQ_SIZE);
	}
}

int main() {
	AllEquations *allEq = malloc(sizeof(AllEquations));
	if (allEq == NULL) {
		return 0;
	}
	printf("Number of equations: ");
	scanf("%d", &(allEq->count));
	allEq->eqArr = malloc(allEq->count * sizeof(Equation*));
	if ((allEq->eqArr) == NULL) {
		return 0;
	}
	setAllEquations(allEq);
	return 0;
}
