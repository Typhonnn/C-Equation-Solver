#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "equation.c"

#define EQ_SIZE 80
#define MAX_EQUATIONS 3

void setEquation(int eqNum, char *eqStr, int numOfEq, Equation *tempEq) {
	char eqCpy[EQ_SIZE];
	char *delimiters = " *+=";
	strcpy(eqCpy, eqStr);
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
			splitEq = strtok(NULL, delimiters);
		}
	}
	tempEq->count = numOfEq;
	tempEq->A = coe;
	tempEq->B = num;
}

void getEquation(int eqNum, char *eqStr) {
	printf("Enter equation %d: ", eqNum);
	scanf("%s", eqStr);
}

int main() {
	int numOfEq;
	char eqStr1[EQ_SIZE], eqStr2[EQ_SIZE], eqStr3[EQ_SIZE];
	Equation *eq1 = NULL, *eq2 = NULL, *eq3 = NULL;
	printf("Number of equations: ");
	scanf("%d", &numOfEq);
	getEquation(1, eqStr1);
	setEquation(1, eqStr1, numOfEq, eq1);
}
