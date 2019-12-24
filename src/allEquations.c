#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "allEquations.h"

//EQ_SIZE is in header.

//Taking user input for equation. ONE BY ONE! copying a set of equations and pasting it may result in a bug.
void setAllEquations(AllEquations *allEq) {
	int i = 0;
	char eqStr[EQ_SIZE]; //Define the string.
	for (i = 0; i < (allEq->count); ++i) { //Taking equation and setting up struct Equation and pointing to it with struct AllEquation.
		memset(eqStr, '\0', EQ_SIZE); //Reseting the equation string.
		printf("Enter equation %d: ", i + 1);
		fgets(eqStr, EQ_SIZE, stdin); //Equation string.
		allEq->eqArr[i] = setEquation(allEq, eqStr); //struct AllEquation point to struct Equation.
	}
}

//Taking pointer to struct AllEquation and setting up a single struct Equation and returning it.
void* setEquation(AllEquations *allEq, char *eqStr) {
	int i, end = 0;
	char *delimiters = " +*=";
	char eqCpy[EQ_SIZE];
	memset(eqCpy, '\0', EQ_SIZE); //Reseting equation string copy.
	Equation *tempEq = malloc(sizeof(Equation)); //Allocate memory to a temporary struct Equation to be returned.
	if (tempEq == NULL) {
		printf("ERROR! COULD NOT MALLOC tempEq!");
		return NULL;
	}
	tempEq->count = allEq->count;
	tempEq->A = malloc(allEq->count * sizeof(float)); //Allocate memory to row of parameters.
	if (tempEq->A == NULL) {
		printf("FAILED TO MALLOC tempEq->A!\n");
		return NULL;
	}
	//Reseting equation parameters to zero.
	//VERY IMPORTANT! this loop is important in the logic of program when a variable of equation is zero.
	for (i = 0; i < allEq->count; ++i) {
		tempEq->A[i] = 0;
	}
	char *splitEq = strtok(eqStr, delimiters);
	while (splitEq != NULL) {//Modifying the string to look like this: 2y-5z8x15
		strcat(eqCpy, splitEq);
		splitEq = strtok(NULL, delimiters);
		end = strlen(eqCpy);
		//If user only gave a variable meaning a dropped '1', plant it in modified equation string.
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

//Taking a modified equation string (2y-5z8x15) and breaking it down to numbers in row A of struct Equation.
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
