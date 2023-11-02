#include "LAnalyticsBaseTable.h"
#include "LLinearOLS.h"
#include "LLinearOLS_GD.h"
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

   pmat::LAnalyticsBaseTable tab{42, 1, 90, "d:/sandbox/pprbe/pprbe.csv", true, ','};
   pmat::LLinearOLS_GD x{tab};

   return 0;
}
