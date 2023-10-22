#include "Container1d.h"
#include "Matrix.h"
#include "MatrixSquare.h"

// #include <blitz/array.h>
#include <cmath>
#include <cstddef>
#include <iostream>
#include <iterator>
#include <vector>

inline int vectorIndex(const int &i, const int &j) {
   return (i * (i + 1)) / 2 + j;
}

int main() {

   pmat::Matrix m(2, 3);

   m.fillWithRandomValues(-1, 1);

   std::cout << m.formattedString();

   return 0;
}
