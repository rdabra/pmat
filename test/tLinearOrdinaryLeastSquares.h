#include "../src/LAnalyticsBaseTable.h"
#include "../src/LLinearOLS.h"
#include "../src/LLinearOLS_GD.h"
#include "../src/Matrix.h"
#include "../src/Vector.h"
#include "../src/pmatUtils.h"
#include "gtest/gtest.h"

TEST(TestLinearOrdinaryLeastSquares, TestAnalyticalSolution) {

   pmat::LAnalyticsBaseTable tab{4,    2,  80, "D:/myWorks/programacao/pmat/test/pequeno.txt",
                                 true, ','};
   tab.readFile();
   pmat::LLinearOLS lols{tab};

   double data[]{2.73916482, -1.51972640, -0.25641727, 0.92879600,  21.30597329,
                 1.12728756, -0.85210798, -0.02582400, -0.24619481, 26.99922389};
   pmat::Matrix resp((double *)data, 2, 5);

   EXPECT_TRUE(lols.coefficients() == resp);
}

TEST(TestLinearOrdinaryLeastSquares, TestGdSolution) {

   pmat::LAnalyticsBaseTable tab{4,    2,  80, "D:/myWorks/programacao/pmat/test/pequeno.txt",
                                 true, ','};
   tab.readFile();
   pmat::LLinearOLS_GD lols{tab};
   lols.setTolerance(0.00001);

   double data[]{2.74013502, -1.51994457, -0.25669041, 0.92980678,  21.26975210,
                 1.12853312, -0.85238647, -0.02617545, -0.24489573, 26.95265672};

   pmat::Matrix resp((double *)data, 2, 5);

   EXPECT_TRUE(lols.coefficients() == resp);
}

TEST(TestLinearOrdinaryLeastSquares, TestDCs) {

   pmat::LAnalyticsBaseTable tab{4,    2,  80, "D:/myWorks/programacao/pmat/test/pequeno.txt",
                                 true, ','};
   tab.readFile();
   pmat::LLinearOLS_GD gd{tab};
   gd.setTolerance(0.00001);
   pmat::LLinearOLS an{tab};

   auto dcAn = an.determinationCoefficients();
   auto dcGd = gd.determinationCoefficients();

   EXPECT_TRUE(pmat::utils::areEqual(dcAn.first, 0.882423263));
   EXPECT_TRUE(pmat::utils::areEqual(dcAn.second, -2.360560985));
   EXPECT_TRUE(pmat::utils::areEqual(dcGd.first, 0.882421535));
   EXPECT_TRUE(pmat::utils::areEqual(dcGd.second, -2.374270622));
}

TEST(TestLinearOrdinaryLeastSquares, TestValuesOf) {

   pmat::LAnalyticsBaseTable tab{4,    2,  80, "D:/myWorks/programacao/pmat/test/pequeno.txt",
                                 true, ','};
   tab.readFile();
   pmat::LLinearOLS_GD gd{tab};
   gd.setTolerance(0.00001);
   pmat::LLinearOLS an{tab};

   double data[]{5., 6., 7., 8.};
   pmat::Vector v{data, 4};

   double data1[]{31.518886108, 25.372687260};
   double data2[]{31.492381168, 25.338609402};
   pmat::Vector analytc{(double *)data1, 2};
   pmat::Vector grd{(double *)data2, 2};

   EXPECT_TRUE(gd.predict(v) == grd);
   EXPECT_TRUE(an.predict(v) == analytc);
}
