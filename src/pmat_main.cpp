#include "Container1d.h"
#include "Matrix.h"
#include "MatrixSquare.h"

// #include <blitz/array.h>
#include <cmath>
#include <cstddef>
#include <iostream>
#include <iterator>
#include <vector>

int main() {

   double a = 1.123456789;

   std::stringstream stream;
   stream.setf(std::ios::fixed);
   stream.precision(8 + 1);
   stream << a;

   std::string s{stream.str()};

   std::cout << s;

   return 0;
}
