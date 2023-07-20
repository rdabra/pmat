#include "MatrixLowerTriangular.h"
#include "MatrixSquare.h"
#include "MatrixUpperTriangular.h"
#include <algorithm>
#include <iostream>
#include <memory>
#include <mutex>
#include <vector>

int main() {

   pmat::MatrixSquare B(3);

   B.setValue(1.0, 0, 0);
   B.setValue(1.0, 0, 1);
   B.setValue(1.0, 0, 2);

   B.setValue(1.0, 1, 0);
   B.setValue(1.0, 1, 1);
   B.setValue(3.0, 1, 2);

   B.setValue(2.0, 2, 0);
   B.setValue(5.0, 2, 1);
   B.setValue(8.0, 2, 2);

   if (true) {
      pmat::MatrixSquare A{B};
   }

   std::cout << "Fim\n";

   return 0;
}