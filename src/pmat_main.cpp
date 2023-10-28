
#include <cstdlib>
#include <iostream>

void printArray(double *v, int size) {

   for (int i = 0; i < size; i++) {
      std::cout << v[i] << " , ";
   }
   std::cout << "\n";
}

int main() {

   double *v = (double *)calloc(5, sizeof(double));

   v[0] = 1;
   v[1] = 2;
   v[2] = 3;
   v[3] = 4;
   v[4] = 5;

   printArray(v, 5);

   // resize

   v = (double *)realloc(v, 6 * sizeof(double));

   printArray(v, 6);

   return 0;
}
