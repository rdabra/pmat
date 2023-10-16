#include "Container1d.h"
#include <blitz/array.h>
#include <iostream>
#include <iterator>
#include <vector>

int main() {

   double a[] = {1, 2, 3, 5};

   blitz::Array<double, 1> r(a, 4);
   double *rr = r.data();
   std::sort(rr, rr + 4, [](double &left, double &right) -> bool { return left > right; });
   r = blitz::Array<double, 1>(rr, 4);

   for (int i{0}; i < 4; i++) {
      std::cout << r(i) << "\n";
   }

   return 0;
}
