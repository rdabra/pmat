#include "Container1d.h"
#include <blitz/array.h>
#include <cmath>
#include <iostream>
#include <iterator>
#include <vector>

int main() {

   double data[]{1., 2., 3., 4.};
   blitz::Array<double, 1> d(data, 4);
   unsigned initialPosition = 3;
   unsigned step = 2;
   double value = 99;

   unsigned inc = std::floor(4. / 2.);
   unsigned oldSize = d.size();
   unsigned newSize = oldSize + inc;

   d.resizeAndPreserve(newSize);

   unsigned i{0};
   for (unsigned j{newSize - 1}; j >= inc; j--) {
      unsigned pos = initialPosition - i * inc + 1;
      if (pos == j) {
         d(j) = value;
         i++;
      } else {
         d(j) = d(j - inc);
      }
      if (i > inc)
         break;
   }

   std::cout << std::floor(5. / 2.) << "\n";

   return 0;
}
