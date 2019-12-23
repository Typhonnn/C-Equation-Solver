#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "allEquations.h"

void setAllEquations(AllEquations *allEq) {
	int i = 0;
	char eqStr[EQ_SIZE];
	for (i = 0; i < (allEq->count); ++i) {
		printf("Enter equation %d: ", i + 1);
		fgets(eqStr, EQ_SIZE, stdin);
		allEq->eqArr[i] = setEquation(allEq, eqStr);
		memset(eqStr, '\0', EQ_SIZE);
	}
}

void* setEquation(AllEquations *allEq, char *eqStr) {
	int i, end = 0;
	char *delimiters = " +*=";
	char eqCpy[EQ_SIZE];
	memset(eqCpy, '\0', EQ_SIZE);
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
	for (i = 0; i < allEq->count; ++i) {
		tempEq->A[i] = 0;
	}
	char *splitEq = strtok(eqStr, delimiters);
	while (splitEq != NULL) {
		strcat(eqCpy, splitEq);
		splitEq = strtok(NULL, delimiters);
		end = strlen(eqCpy);
		if (eqCpy[end - 1] == 'x' || eqCpy[end - 1] == 'y'
				|| eqCpy[end - 1] == 'z') {
			if (*splitEq == 'x' || *splitEq == 'y' || *splitEq == 'z') {
				strcat(eqCpy, "1");
			}
		}
	}
	setNumbers(eqCpy, tempEq, tempEq->count, strlen(eqCpy));
	return tempEq;
}

void setNumbers(char *eqCpy, Equation *tempEq, int size, int strLen) {
	int i;
	float num = 0;
	char *delimiters = "xyz";
	char eqCpy2[EQ_SIZE];
	strcpy(eqCpy2, eqCpy);
	char *splitEq = strtok(eqCpy, delimiters);
	for (i = 0; i < strLen && splitEq != NULL; ++i) {
		num = atof(splitEq);
		switch (eqCpy2[i]) {
		case 'x':
			tempEq->A[0] = num;
			splitEq = strtok(NULL, delimiters);
			break;
		case 'y':
			tempEq->A[1] = num;
			splitEq = strtok(NULL, delimiters);
			break;
		case 'z':
			tempEq->A[2] = num;
			splitEq = strtok(NULL, delimiters);
			break;
		default:
			break;
		}
	}
	tempEq->B = num;
}
