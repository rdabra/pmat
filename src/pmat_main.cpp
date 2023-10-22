#include "Container1d.h"
#include "Matrix.h"
#include "MatrixSquare.h"

// #include <blitz/array.h>
#include <cmath>
#include <cstddef>
#include <iostream>
#include <iterator>
#include <vector>

class Foo {
   private:
      int _v[6] = {1, 2, 3, 4, 5, 6};

   public:
      void soma();

      //      int operator()(int i) const { return _v[i]; }
      //      int &operator()(int i) { return _v[i]; }
};

int main() {

   pmat::Matrix m(2, 3);

   m.fillWithRandomValues(-1, 1);

   std::cout << m.formattedString();

   return 0;
}
