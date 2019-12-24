#pragma once

#define EQ_SIZE 80 //Max characters in equation string.

typedef struct {
	int count; //Number of coefficients
	float *A; //Coefficients of x,y,z (in that order)
	float B; //The free number on the right side
} Equation;

typedef struct {
	int count; //Number of equations
	Equation **eqArr; //All equations
} AllEquations;

//Taking a modified equation string (2y-5z8x15) and breaking it down to numbers in row A of struct Equation.
void setNumbers(char *eqCpy, Equation *tempEq, int size, int strLen);

//Taking user input for equation. ONE BY ONE! copying a set of equations and pasting it may result in a bug.
void setAllEquations(AllEquations *allEq);

//Taking pointer to struct AllEquation and setting up a single struct Equation and returning it.
void* setEquation(AllEquations *allEq, char *eqStr);
