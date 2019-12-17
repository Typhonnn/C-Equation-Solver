typedef struct
{
  int count; //Number of coefficients
  float* A; //Coefficients of x,y,z (in that order)
  float B; //The free number on the right side
} Equation
