#include "../src/LAnalyticsBaseTable.h"
#include "../src/LLinearOLS.h"
#include "../src/LLinearOLS_GD.h"
#include "../src/Matrix.h"
#include "../src/Vector.h"
#include "../src/pmatUtils.h"
#include "gtest/gtest.h"
#include <ostream>
#include <utility>

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

   auto dcAn = an.distanceDeterminationCoefficients();
   auto dcGd = gd.distanceDeterminationCoefficients();

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

   std::cout << gd.predictTraining().formattedString(',', 9) << std::endl;
   std::cout << gd.predictTest().formattedString(',', 9) << std::endl;

   double data3[]{23.9191538777, 25.3183075934, 25.0133020395, 26.4127432524,
                  26.9107337832, 27.5528218918, 28.0868844402, 28.6123831261,
                  49.6570766741, 10.6142408229, 60.5985582921, 21.5585974132,
                  81.4324892913, 32.4695923439, 92.2641890810, 43.3101004182};
   pmat::Matrix pt{(double *)data3, 8, 2};

   double data4[]{3.1879146460, 26.0733638005, 49.6570766741, 10.6142408229};
   pmat::Matrix ptr{(double *)data4, 2, 2};

   EXPECT_TRUE(gd.predict(v) == grd);
   EXPECT_TRUE(an.predict(v) == analytc);
   EXPECT_TRUE(gd.predictTraining() == pt);
   EXPECT_TRUE(gd.predictTest() == ptr);
}

TEST(TestLinearOrdinaryLeastSquares, TestErrors) {

   pmat::LAnalyticsBaseTable tab{4,    2,  80, "D:/myWorks/programacao/pmat/test/pequeno.txt",
                                 true, ','};
   tab.readFile();
   pmat::LLinearOLS_GD lols{tab};
   lols.setTolerance(0.00001);

   auto dc = lols.determinationCoefficients();

   double data1[]{0.933291603, 0.600092656};
   double data2[]{-27.631144837, 0.432048735};

   auto resp_dc =
       std::make_pair(pmat::Vector{(double *)data1, 2}, pmat::Vector{(double *)data2, 2});

   auto ddc = lols.distanceDeterminationCoefficients();

   auto mqe = lols.relativeRootMeanSquareErrors();
   double data3[]{0.140307755, 0.262044513};
   double data4[]{1.012547781, 0.616250711};

   auto resp_mqe =
       std::make_pair(pmat::Vector{(double *)data3, 2}, pmat::Vector{(double *)data4, 2});

   auto mmqe = lols.distanceRelativeRootMeanSquareErrors();

   auto rmax = lols.maximumRelativeError();
   double data5[]{0.540117512, 0.526034671};
   double data6[]{11.861072065, 0.610839335};

   auto resp_rmax =
       std::make_pair(pmat::Vector{(double *)data5, 2}, pmat::Vector{(double *)data6, 2});

   auto rrmax = lols.distanceMaximumRelativeError();

   auto rmean = lols.meanRelativeError();
   double data7[]{0.1706198000, 0.189768477};
   double data8[]{5.944058006, 0.370697967};

   auto resp_rmean =
       std::make_pair(pmat::Vector{(double *)data7, 2}, pmat::Vector{(double *)data8, 2});

   auto rrmean = lols.distanceMeanRelativeError();

   // std::cout << pmat::utils::format(rrmean.first, pmat::utils::PRECISION) << std::endl;
   // std::cout << pmat::utils::format(rrmean.second, pmat::utils::PRECISION) << std::endl;

   EXPECT_TRUE(dc == resp_dc);
   EXPECT_TRUE(pmat::utils::areEqual(ddc.first, 0.882421535));
   EXPECT_TRUE(pmat::utils::areEqual(ddc.second, -2.374270622));
   EXPECT_TRUE(mqe == resp_mqe);
   EXPECT_TRUE(pmat::utils::areEqual(mmqe.first, 0.176826984));
   EXPECT_TRUE(pmat::utils::areEqual(mmqe.second, 0.902951913));
   EXPECT_TRUE(rmax == resp_rmax);
   EXPECT_TRUE(pmat::utils::areEqual(rrmax.first, 0.532722618));
   EXPECT_TRUE(pmat::utils::areEqual(rrmax.second, 1.561981635));
   EXPECT_TRUE(rmean == resp_rmean);
   EXPECT_TRUE(pmat::utils::areEqual(rrmean.first, 0.173737459));
   EXPECT_TRUE(pmat::utils::areEqual(rrmean.second, 0.799991929));
}
