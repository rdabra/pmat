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

   pmat::Matrix m(3, 3);
   pmat::MatrixSquare mq(3);

   pmat::Matrix x{mq * m};

   return 0;
}
