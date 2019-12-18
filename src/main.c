#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "equation.c"

#define EQ_SIZE 80
#define MAX_EQUATIONS 3

struct Equation* setEquation(int eqNum, char **eqs, int numOfEq) {
	struct Equation *tempEq = (struct Equation*)malloc(sizeof(Equation));
	char eqCpy[EQ_SIZE];
	char *delimiters = " *+=";
	strcpy(eqCpy, eqs[eqNum]);
	float coe[MAX_EQUATIONS];
	float num;
	int i = 0;
	char var[MAX_EQUATIONS];
	char *splitEq = strtok(eqCpy, delimiters);
	while (splitEq != NULL) {
		sscanf(splitEq, "%f", &num);
		splitEq = strtok(NULL, delimiters);
		if (splitEq != NULL) {
			sscanf(splitEq, "%c", &var[i]);
			coe[var[i] - 'x'] = num;
		}
	}
	tempEq->count = numOfEq;
	tempEq->A = coe;
	tempEq->B = num;
	return tempEq;
}

void getEquations(int numOfEq, char **eqs) {
	int i;
	for (i = 0; i < numOfEq; ++i) {
		printf("Enter equation %d: ", i + 1);
		scanf("%s", eqs[i]);
	}
}

int main() {
	int numOfEq;
	char eqs[MAX_EQUATIONS][EQ_SIZE];
	struct Equation *eq1, *eq2, *eq3;
	printf("Number of equations: ");
	scanf("%d", &numOfEq);
	getEquations(numOfEq, (char**) eqs);
	eq1 = setEquation(1, (char**) eqs, numOfEq);
	eq2 = setEquation(2, (char**) eqs, numOfEq);
	eq3 = setEquation(3, (char**) eqs, numOfEq);
}
