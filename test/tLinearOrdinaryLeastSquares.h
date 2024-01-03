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

   double data[]{2.7394496637, -1.5197885899, -0.2565016677, 0.9290905285,  21.2953729228,
                 1.1276488929, -0.8521876451, -0.0259281619, -0.2458188227, 26.9857346719};

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
   EXPECT_TRUE(pmat::utils::areEqual(dcGd.first, 0.8824231172));
   EXPECT_TRUE(pmat::utils::areEqual(dcGd.second, -2.3646362329));
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
   double data2[]{31.5111022565, 25.3628055506};
   pmat::Vector analytc{(double *)data1, 2};
   pmat::Vector grd{(double *)data2, 2};

   double data3[]{23.9421025178, 25.3479484980, 25.0362469439, 26.4423649627,
                  26.9337873692, 27.5826034809, 28.1098930012, 28.6420921614,
                  49.6549188071, 10.6115871966, 60.5963630680, 21.5557518429,
                  81.4299483785, 32.4664993798, 92.2619141701, 43.3072050080};
   pmat::Matrix pt{(double *)data3, 8, 2};

   double data4[]{3.2292312346, 26.1270604551, 49.6549188071, 10.6115871966};
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

   double data1[]{0.9332923064, 0.6000991175};
   double data2[]{-27.5688043309, 0.4358268891};

   auto resp_dc =
       std::make_pair(pmat::Vector{(double *)data1, 2}, pmat::Vector{(double *)data2, 2});

   auto ddc = lols.distanceDeterminationCoefficients();

   auto mqe = lols.relativeRootMeanSquareErrors();
   double data3[]{0.1402770761, 0.2619122397};
   double data4[]{1.0106958991, 0.6133442250};

   auto resp_mqe =
       std::make_pair(pmat::Vector{(double *)data3, 2}, pmat::Vector{(double *)data4, 2});

   auto mmqe = lols.distanceRelativeRootMeanSquareErrors();

   auto rmax = lols.maximumRelativeError();
   double data5[]{0.5405583118, 0.5265889071};
   double data6[]{11.6965203237, 0.6075287181};

   auto resp_rmax =
       std::make_pair(pmat::Vector{(double *)data5, 2}, pmat::Vector{(double *)data6, 2});

   auto rrmax = lols.distanceMaximumRelativeError();

   auto rmean = lols.meanRelativeError();
   double data7[]{0.1705016901, 0.1896396583};
   double data8[]{5.8618044513, 0.3691840167};

   auto resp_rmean =
       std::make_pair(pmat::Vector{(double *)data7, 2}, pmat::Vector{(double *)data8, 2});

   auto rrmean = lols.distanceMeanRelativeError();

   // std::cout << rmean.first.formattedString(',', 9) << std::endl;
   // std::cout << rmean.second.formattedString(',', 9) << std::endl;

   // std::cout << pmat::utils::format(rrmean.first, pmat::utils::PRECISION) << std::endl;
   // std::cout << pmat::utils::format(rrmean.second, pmat::utils::PRECISION) << std::endl;

   EXPECT_TRUE(dc == resp_dc);
   EXPECT_TRUE(pmat::utils::areEqual(ddc.first, 0.882423117));
   EXPECT_TRUE(pmat::utils::areEqual(ddc.second, -2.364636233));
   EXPECT_TRUE(mqe == resp_mqe);
   EXPECT_TRUE(pmat::utils::areEqual(mmqe.first, 0.176776213));
   EXPECT_TRUE(pmat::utils::areEqual(mmqe.second, 0.900803857));
   EXPECT_TRUE(rmax == resp_rmax);
   EXPECT_TRUE(pmat::utils::areEqual(rrmax.first, 0.53322109));
   EXPECT_TRUE(pmat::utils::areEqual(rrmax.second, 1.556282766));
   EXPECT_TRUE(rmean == resp_rmean);
   EXPECT_TRUE(pmat::utils::areEqual(rrmean.first, 0.173601591));
   EXPECT_TRUE(pmat::utils::areEqual(rrmean.second, 0.797177045));
}
