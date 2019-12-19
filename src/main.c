#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "allEquations.c"
#include "equation.c"

#define EQ_SIZE 80
#define MAX_EQUATIONS 3

void* setEquation(AllEquations *allEq, char *eqStr) {
	char eqCpy[EQ_SIZE];
	char *delimiters = " *+=";
	float *coe = (float*) malloc((allEq->count) * sizeof(float));
	Equation *tempEq = malloc(sizeof(Equation));
	if (coe == NULL || tempEq == NULL) {
		printf("FAILED TO MALLOC EQUATION!\n");
		return NULL;
	}
	float num;
	int i = 0;
	char var[MAX_EQUATIONS];
	strcpy(eqCpy, eqStr);
	char *splitEq = strtok(eqCpy, delimiters);
	while (splitEq != NULL) {
		sscanf(splitEq, "%f", &num);
		splitEq = strtok(NULL, delimiters);
		if (splitEq != NULL) {
			sscanf(splitEq, "%c", &var[i]);
			coe[var[i] - 'x'] = num;
			splitEq = strtok(NULL, delimiters);
		}
	}
	tempEq->count = allEq->count;
	tempEq->A = coe;
	tempEq->B = num;
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
	AllEquations *allEq;
	printf("Number of equations: ");
	scanf("%d", &(allEq->count));
	(allEq->eqArr) = malloc((allEq->count) * sizeof(Equation*));
	setAllEquations(allEq);
}
