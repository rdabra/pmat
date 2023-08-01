#include "MatrixSquare.h"
#include "MatrixUpperTriangular.h"
#include <iostream>

int main() {

   pmat::MatrixUpperTriangular B{3};

   pmat::MatrixSquare C{3};

   pmat::MatrixSquare R{B * C};

   std::cout << "Fim\n";

   return 0;
}