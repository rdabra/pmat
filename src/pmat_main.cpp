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

   // pmat::MatrixSquare mq{2};
   // mq.setValue(1, 0, 0);
   // mq.setValue(2, 0, 1);
   // mq.setValue(3, 1, 0);
   // mq.setValue(4, 1, 1);

   // pmat::Matrix m{2, 2};
   // m.setValue(1, 0, 0);
   // m.setValue(2, 0, 1);
   // m.setValue(3, 1, 0);
   // m.setValue(4, 1, 1);

   // pmat::Matrix res{mq * m};

   // std::cout << res.formattedString();

   double data[] = {1., 2., 3., 4., 5., 6., 7., 8., 9., 10., 11., 12.};

   // pmat::Matrix m{data, 3, 4};

   // m.insertRow(1, 99);

   // std::cout << m.formattedString();

   pmat::Container1d x{data, 12};

   x.pushBack(11, 4, 99);

   std::cout << *x._ptrVector;

   return 0;
}
