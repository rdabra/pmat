#include "Vector.h"
#include <iostream>

int main() {

   // std::cout << "Reading file...\n";

   // AnalyticsBaseTable tab{42, 1, 90, "d:/sandbox/pprbe/pprbe.csv", true, ','};
   // tab.readFile();

   // std::cout << "Training size: " << tab.trainingSize() << "\n";
   // std::cout << "Test size: " << tab.testSize() << "\n";

   // LinearOrdinaryLeastSquares lols{tab};
   // lols.setTolerance(0.00001);

   // std::cout << "Calculating GD solution...\n";
   // double train = lols.gradientDescentTrainingCorrelation();
   // double test = lols.gradientDescentTestCorrelation();

   // std::cout << "GD training correlation: " << train << "\n";
   // std::cout << "GD test correlation: " << test << "\n";
   // std::cout << "Number of iterations: " << lols.nIterations() << "\n";

   // int a = 3;
   // double b = 1.233;
   // double c = a * b;

   // std::string aa{"roberto"};

   double data1[]{1, 2, 3, 44, 5, 6, 7, 8, 9};
   double data2[]{1, 2, 0, 45, 5, 0, 7, 0, 0};

   pmat::Vector d1{(double *)data1, 9};
   pmat::Vector d2{(double *)data2, 9};

   std::cout << d2.hammingDistantFrom(d1);

   return 0;
}
