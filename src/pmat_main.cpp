#include "LAnalyticsBaseTable.h"
#include "LLinearOLS_GD.h"
#include "LWeightedNN.h"
#include <algorithm>
#include <cmath>
#include <cstdlib>
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

   std::cout << "Reading file...\n";
   pmat::LAnalyticsBaseTable tab{47, 1, 90, "d:/sandbox/pprbe/pprbeSojaPP.csv", true, ','};
   tab.setFeatureType(pmat::DATA_TYPE::DISCRETE);
   tab.readFile();

   pmat::LWeightedNN nn{tab, 10};
   pmat::LLinearOLS_GD gd{tab};
   gd.setTolerance(0.00001);

   auto eGD = gd.rootMeanSquareErrors();
   std::cout << "GD Test correlation: " << eGD.second << "\n";
   auto eNN = nn.rootMeanSquareErrors();
   std::cout << "NN Test correlation: " << eNN.second << "\n";

   // std::string a = "1";
   // std::string b = "21";

   // auto max = std::max(a.length(), b.length());
   // a = std::string(max - a.length(), '0') + a;
   // b = std::string(max - b.length(), '0') + b;

   // std::cout << "a: " << a << "\n";
   // std::cout << "b: " << b << "\n";

   return 0;
}
