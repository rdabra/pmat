#include "Container1d.h"
#include "Matrix.h"
#include "MatrixSquare.h"

// #include <blitz/array.h>
#include <cmath>
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

   std::vector<double> data{1., 2., 3., 4.};
   pmat::Container1d c{data, 4};

   c.insertValues(1, 88, 4);
   std::cout << *c._ptrVector << "\n";

   return 0;
}
