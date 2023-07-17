#include "MatrixLowerTriangular.h"
#include <iostream>
#include <memory>
#include <mutex>

int main() {
   std::vector<double> v{5};
   v.clear();
   v.resize(10);
   std::cout << v[3] << "\n";

   return 0;
}