#include <stdio.h>

#define EQ_SIZE 80;

char eq1[EQ_SIZE], eq2[EQ_SIZE], eq3[EQ_SIZE];


void clearEquations() {
  int i;
  for (i = 0; i < EQ_SIZE; i++) {
    eq1[i] = null;
    eq2[i] = null;
    eq3[i] = null;
  }
}

int main() {
  int numOfEq, i;
  clearEquations();
  printf("Number of equations: ");
  scanf("%d", &numOfEq);
  
  getEquations(numOfEq);
}
