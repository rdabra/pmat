#include "../src/LAnalyticsBaseTable.h"
#include "../src/LWeightedNN.h"
#include "../src/Vector.h"
#include "../src/pmatUtils.h"
#include "gtest/gtest.h"

TEST(TestNearestNeighbor, TestValueOf) {

   pmat::LAnalyticsBaseTable tab{4,    2,  80, "D:/myWorks/programacao/pmat/test/pequeno.txt",
                                 true, ','};
   tab.readFile();
   pmat::LWeightedNN nn{tab, 6};

   nn.setKNeighbors(7);

   double data[]{5., 6., 7., 8.};
   pmat::Vector v{(double *)data, 4};

   double data1[]{30.645022247, 26.557220871};
   pmat::Vector resp{(double *)data1, 2};

   EXPECT_TRUE(nn.predict(v) == resp);
}

TEST(TestNearestNeighbor, TestErrors) {

   pmat::LAnalyticsBaseTable tab{4,    2,  80, "D:/myWorks/programacao/pmat/test/pequeno.txt",
                                 true, ','};
   tab.readFile();
   pmat::LWeightedNN lols{tab, 7};

   auto dc = lols.determinationCoefficients();

   double data1[]{1.000000000, 1.000000000};
   double data2[]{0.791187027, 0.438968099};

   auto resp_dc =
       std::make_pair(pmat::Vector{(double *)data1, 2}, pmat::Vector{(double *)data2, 2});

   auto ddc = lols.distanceDeterminationCoefficients();

   auto mqe = lols.relativeRootMeanSquareErrors();
   double data3[]{0.000000000, .000000000};
   double data4[]{0.047984335, 0.589611758};

   auto resp_mqe =
       std::make_pair(pmat::Vector{(double *)data3, 2}, pmat::Vector{(double *)data4, 2});

   auto mmqe = lols.distanceRelativeRootMeanSquareErrors();

   auto rmax = lols.maximumRelativeError();
   double data5[]{0.000000000, .000000000};
   double data6[]{0.073052490, 0.608525304};

   auto resp_rmax =
       std::make_pair(pmat::Vector{(double *)data5, 2}, pmat::Vector{(double *)data6, 2});

   auto rrmax = lols.distanceMaximumRelativeError();

   auto rmean = lols.meanRelativeError();
   double data7[]{0.000000000, 0.000000000};
   double data8[]{0.036526245, 0.304262652};

   auto resp_rmean =
       std::make_pair(pmat::Vector{(double *)data7, 2}, pmat::Vector{(double *)data8, 2});

   auto rrmean = lols.distanceMeanRelativeError();

   std::cout << rmean.first.formattedString(' ', pmat::utils::PRECISION) << std::endl;
   std::cout << rmean.second.formattedString(' ', pmat::utils::PRECISION) << std::endl;
   std::cout << pmat::utils::format(rrmean.first, pmat::utils::PRECISION) << std::endl;
   std::cout << pmat::utils::format(rrmean.second, pmat::utils::PRECISION) << std::endl;

   EXPECT_TRUE(dc == resp_dc);
   EXPECT_TRUE(pmat::utils::areEqual(ddc.first, 1.000000000));
   EXPECT_TRUE(pmat::utils::areEqual(ddc.second, 0.474189992));
   EXPECT_TRUE(mqe == resp_mqe);
   EXPECT_TRUE(pmat::utils::areEqual(mmqe.first, 0.000000000));
   EXPECT_TRUE(pmat::utils::areEqual(mmqe.second, 0.223551324));
   EXPECT_TRUE(rmax == resp_rmax);
   EXPECT_TRUE(pmat::utils::areEqual(rrmax.first, 0.000000000));
   EXPECT_TRUE(pmat::utils::areEqual(rrmax.second, 0.315680305));
   EXPECT_TRUE(rmean == resp_rmean);
   EXPECT_TRUE(pmat::utils::areEqual(rrmean.first, 0.000000000));
   EXPECT_TRUE(pmat::utils::areEqual(rrmean.second, 0.157840153));
}
