#include "Container1d.h"
#include <blitz/array.h>
#include <iostream>
#include <iterator>
#include <vector>

int main() {

   std::vector<double> d{1, 2, 3, 4};

   pmat::Container1d c1{d.data(), 4};

   pmat::Container1d c2{c1};

   c2.set(1, 77);

   std::cout << c1(1) << "\n";

   return 0;
}
