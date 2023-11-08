#include "LAnalyticsBaseTable.h"
#include "LLinearOLS_GD.h"
#include "pmatUtils.h"
#include <iostream>

int main() {

   std::string root{"D:/myWorks/programacao/rbepp/data/"};
   char separator{','};

   std::cout << "Reading File..." << std::endl;
   pmat::LAnalyticsBaseTable tableRBE{47, 1, 90, root + "pprbeSojaRBE.csv", true, separator};
   tableRBE.readFile();
   std::cout << "Training size: " << tableRBE.trainingSize() << std::endl;
   std::cout << "Test size: " << tableRBE.testSize() << std::endl;
   pmat::LLinearOLS_GD gdRBE{tableRBE};
   gdRBE.setTolerance(0.00001);
   std::cout << "Writing  Coefficients..." << std::endl;
   gdRBE.coefficients().writeToFile(root + "coefsSojaRBE.csv", separator, pmat::utils::PRECISION);
   std::cout << "Writing  Test Predictions..." << std::endl;
   gdRBE.predictTest().writeToFile(root + "predictTestSojaRBE.csv", separator,
                                   pmat::utils::PRECISION);
}
