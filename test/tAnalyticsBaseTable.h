#include "../src/LAnalyticsBaseTable.h"
#include "../src/Matrix.h"
#include "gtest/gtest.h"

TEST(TestAnalyticsBaseTable, TestMatrices) {

   pmat::LAnalyticsBaseTable tab{4,    2,  80, "D:/myWorks/programacao/pmat/test/pequeno.txt",
                                 true, ','};
   tab.readFile();

   const pmat::Matrix &features = tab.featureTrainingData();
   const pmat::Matrix &targets = tab.targetTrainingData();
   const pmat::Matrix &features_t = tab.featureTestData();
   const pmat::Matrix &targets_t = tab.targetTestData();

   double dvfeatures[]{1,  2,  3,  4,  3,  4,  1,  2,  7,  8,  9,  1,  4,  3,  2,  1,
                       11, 21, 31, 41, 31, 41, 11, 21, 71, 81, 91, 13, 41, 31, 21, 12};
   double dvtargets[]{11, 12, 21, 22, 31, 32, 41, 42, 51, 12, 61, 22, 81, 32, 91, 42};
   double dvfeatures_t[]{4, 3, 99, 1, 11, 21, 31, 41};
   double dvtargets_t[]{41, 42, 51, 12};

   pmat::Matrix vfeatures((double *)dvfeatures, 8, 4);
   pmat::Matrix vtargets((double *)dvtargets, 8, 2);
   pmat::Matrix vfeatures_t((double *)dvfeatures_t, 2, 4);
   pmat::Matrix vtargets_t((double *)dvtargets_t, 2, 2);

   EXPECT_TRUE(features == vfeatures);
   EXPECT_TRUE(targets == vtargets);
   EXPECT_TRUE(features_t == vfeatures_t);
   EXPECT_TRUE(targets_t == vtargets_t);
}
