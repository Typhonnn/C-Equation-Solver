#pragma once

#define EQ_SIZE 80

typedef struct {
	int count; //Number of coefficients
	float *A; //Coefficients of x,y,z (in that order)
	float B; //The free number on the right side
} Equation;

typedef struct {
	int count; //Number of equations
	Equation **eqArr; //All equations
} AllEquations;

void setNumbers(char *eqCpy, Equation *tempEq, int size, int strLen);

void setAllEquations(AllEquations *allEq);

void* setEquation(AllEquations *allEq, char *eqStr);
