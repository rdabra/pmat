#include "../src/Matrix.h"
#include "../src/pmatUtils.h"
#include "gtest/gtest.h"
#include <cmath>
#include <iostream>
#include <vector>

using namespace pmat;

TEST(TestMatrix, TestEqualityOperator) {
   Matrix z(4, 3);
   z.assign(1.0, 0, 0);
   z.assign(2.0, 0, 1);
   z.assign(3.0, 0, 2);
   z.assign(4.0, 1, 0);
   z.assign(5.0, 1, 1);
   z.assign(6.0, 1, 2);
   z.assign(7.0, 2, 0);
   z.assign(8.0, 2, 1);
   z.assign(9.0, 2, 2);
   z.assign(10.0, 3, 0);
   z.assign(11.0, 3, 1);
   z.assign(12.0, 3, 2);

   Matrix v(4, 3);
   v.assign(1.0, 0, 0);
   v.assign(2.0, 0, 1);
   v.assign(3.0, 0, 2);
   v.assign(4.0, 1, 0);
   v.assign(5.0, 1, 1);
   v.assign(6.0, 1, 2);
   v.assign(7.0, 2, 0);
   v.assign(8.0, 2, 1);
   v.assign(9.0, 2, 2);
   v.assign(10.0, 3, 0);
   v.assign(11.0, 3, 1);
   v.assign(12.0, 3, 2);

   EXPECT_TRUE(v == z);
   EXPECT_TRUE(v.at(3, 2) == 12);
}

TEST(TestMatrix, TestDotProduct) {
   Matrix z(4, 3);
   z.assign(1.0, 0, 0);
   z.assign(2.0, 0, 1);
   z.assign(3.0, 0, 2);
   z.assign(4.0, 1, 0);
   z.assign(5.0, 1, 1);
   z.assign(6.0, 1, 2);
   z.assign(7.0, 2, 0);
   z.assign(8.0, 2, 1);
   z.assign(9.0, 2, 2);
   z.assign(10.0, 3, 0);
   z.assign(11.0, 3, 1);
   z.assign(12.0, 3, 2);

   Matrix v(4, 3);
   v.assign(1.0, 0, 0);
   v.assign(2.0, 0, 1);
   v.assign(3.0, 0, 2);
   v.assign(4.0, 1, 0);
   v.assign(5.0, 1, 1);
   v.assign(6.0, 1, 2);
   v.assign(7.0, 2, 0);
   v.assign(8.0, 2, 1);
   v.assign(9.0, 2, 2);
   v.assign(10.0, 3, 0);
   v.assign(11.0, 3, 1);
   v.assign(12.0, 3, 2);

   double resp = z.dotProduct(v);
   EXPECT_TRUE(utils::areEqual(resp, 650.0));
}

TEST(TestMatrix, TestPlus) {
   Matrix z(4, 3);
   z.assign(1.0, 0, 0);
   z.assign(2.0, 0, 1);
   z.assign(3.0, 0, 2);
   z.assign(4.0, 1, 0);
   z.assign(5.0, 1, 1);
   z.assign(6.0, 1, 2);
   z.assign(7.0, 2, 0);
   z.assign(8.0, 2, 1);
   z.assign(9.0, 2, 2);
   z.assign(10.0, 3, 0);
   z.assign(11.0, 3, 1);
   z.assign(12.0, 3, 2);

   Matrix v(4, 3);
   v.assign(1.0, 0, 0);
   v.assign(2.0, 0, 1);
   v.assign(3.0, 0, 2);
   v.assign(4.0, 1, 0);
   v.assign(5.0, 1, 1);
   v.assign(6.0, 1, 2);
   v.assign(7.0, 2, 0);
   v.assign(8.0, 2, 1);
   v.assign(9.0, 2, 2);
   v.assign(10.0, 3, 0);
   v.assign(11.0, 3, 1);
   v.assign(12.0, 3, 2);

   Matrix resp(4, 3);
   resp.assign(2.0, 0, 0);
   resp.assign(4.0, 0, 1);
   resp.assign(6.0, 0, 2);
   resp.assign(8.0, 1, 0);
   resp.assign(10.0, 1, 1);
   resp.assign(12.0, 1, 2);
   resp.assign(14.0, 2, 0);
   resp.assign(16.0, 2, 1);
   resp.assign(18.0, 2, 2);
   resp.assign(20.0, 3, 0);
   resp.assign(22.0, 3, 1);
   resp.assign(24.0, 3, 2);

   Matrix x1(4, 3);
   x1 = z + v;
   Matrix x2(z + v);
   z.addBy(v);

   EXPECT_TRUE(resp == x1);
   EXPECT_TRUE(resp == x2);
   EXPECT_TRUE(resp == z);
}

TEST(TestMatrix, TestMinus) {
   Matrix z(4, 3);
   z.assign(1.0, 0, 0);
   z.assign(2.0, 0, 1);
   z.assign(3.0, 0, 2);
   z.assign(4.0, 1, 0);
   z.assign(5.0, 1, 1);
   z.assign(6.0, 1, 2);
   z.assign(7.0, 2, 0);
   z.assign(8.0, 2, 1);
   z.assign(9.0, 2, 2);
   z.assign(10.0, 3, 0);
   z.assign(11.0, 3, 1);
   z.assign(12.0, 3, 2);

   Matrix v(4, 3);
   v.assign(12.0, 0, 0);
   v.assign(11.0, 0, 1);
   v.assign(10.0, 0, 2);
   v.assign(9.0, 1, 0);
   v.assign(8.0, 1, 1);
   v.assign(7.0, 1, 2);
   v.assign(6.0, 2, 0);
   v.assign(5.0, 2, 1);
   v.assign(4.0, 2, 2);
   v.assign(3.0, 3, 0);
   v.assign(2.0, 3, 1);
   v.assign(1.0, 3, 2);

   Matrix resp(4, 3);
   resp.assign(-11.0, 0, 0);
   resp.assign(-9.0, 0, 1);
   resp.assign(-7.0, 0, 2);
   resp.assign(-5.0, 1, 0);
   resp.assign(-3.0, 1, 1);
   resp.assign(-1.0, 1, 2);
   resp.assign(1.0, 2, 0);
   resp.assign(3.0, 2, 1);
   resp.assign(5.0, 2, 2);
   resp.assign(7.0, 3, 0);
   resp.assign(9.0, 3, 1);
   resp.assign(11.0, 3, 2);

   Matrix x1(4, 3);
   x1 = z - v;
   Matrix x2(z - v);
   z.subtractBy(v);

   EXPECT_TRUE(resp == x1);
   EXPECT_TRUE(resp == x2);
   EXPECT_TRUE(resp == z);
}

TEST(TestMatrix, TestTimes) {
   Matrix z(4, 3);
   z.assign(1.0, 0, 0);
   z.assign(2.0, 0, 1);
   z.assign(3.0, 0, 2);
   z.assign(4.0, 1, 0);
   z.assign(5.0, 1, 1);
   z.assign(6.0, 1, 2);
   z.assign(7.0, 2, 0);
   z.assign(8.0, 2, 1);
   z.assign(9.0, 2, 2);
   z.assign(10.0, 3, 0);
   z.assign(11.0, 3, 1);
   z.assign(12.0, 3, 2);

   Vector u(3);
   u.assign(3.0, 0);
   u.assign(2.0, 1);
   u.assign(-1.0, 2);

   Matrix v(3, 4);
   v.assign(1.0, 0, 0);
   v.assign(2.0, 0, 1);
   v.assign(3.0, 0, 2);
   v.assign(4.0, 0, 3);
   v.assign(5.0, 1, 0);
   v.assign(6.0, 1, 1);
   v.assign(7.0, 1, 2);
   v.assign(8.0, 1, 3);
   v.assign(9.0, 2, 0);
   v.assign(10.0, 2, 1);
   v.assign(11.0, 2, 2);
   v.assign(12.0, 2, 3);

   Matrix resp(4, 4);
   resp.assign(38.0, 0, 0);
   resp.assign(44.0, 0, 1);
   resp.assign(50.0, 0, 2);
   resp.assign(56.0, 0, 3);
   resp.assign(83.0, 1, 0);
   resp.assign(98.0, 1, 1);
   resp.assign(113.0, 1, 2);
   resp.assign(128.0, 1, 3);
   resp.assign(128.0, 2, 0);
   resp.assign(152.0, 2, 1);
   resp.assign(176.0, 2, 2);
   resp.assign(200.0, 2, 3);
   resp.assign(173.0, 3, 0);
   resp.assign(206.0, 3, 1);
   resp.assign(239.0, 3, 2);
   resp.assign(272.0, 3, 3);

   Matrix resp2(4, 3);
   resp2.assign(2.0, 0, 0);
   resp2.assign(4.0, 0, 1);
   resp2.assign(6.0, 0, 2);
   resp2.assign(8.0, 1, 0);
   resp2.assign(10.0, 1, 1);
   resp2.assign(12.0, 1, 2);
   resp2.assign(14.0, 2, 0);
   resp2.assign(16.0, 2, 1);
   resp2.assign(18.0, 2, 2);
   resp2.assign(20.0, 3, 0);
   resp2.assign(22.0, 3, 1);
   resp2.assign(24.0, 3, 2);

   Vector resp3(4);
   resp3.assign(4.0, 0);
   resp3.assign(16.0, 1);
   resp3.assign(28.0, 2);
   resp3.assign(40.0, 3);

   Vector x5 = z * u;

   Matrix x1(4, 4);
   x1 = z * v;
   Matrix x2(z * v);

   Matrix respp{z.multiply(v, 5)};

   Matrix x3(4, 3);
   x3 = z * 2.0;
   Matrix x4(z * 2.0);
   z.multiplyBy(2.0);

   EXPECT_TRUE(resp == x1);
   EXPECT_TRUE(resp == x2);
   EXPECT_TRUE(resp == respp);
   EXPECT_TRUE(resp2 == x3);
   EXPECT_TRUE(resp2 == x4);
   EXPECT_TRUE(resp2 == z);
   EXPECT_TRUE(resp3 == x5);
}

TEST(TestMatrix, TestFrobenius) {
   Matrix z(4, 3);
   z.assign(1.0, 0, 0);
   z.assign(2.0, 0, 1);
   z.assign(3.0, 0, 2);
   z.assign(4.0, 1, 0);
   z.assign(5.0, 1, 1);
   z.assign(6.0, 1, 2);
   z.assign(7.0, 2, 0);
   z.assign(8.0, 2, 1);
   z.assign(9.0, 2, 2);
   z.assign(10.0, 3, 0);
   z.assign(11.0, 3, 1);
   z.assign(12.0, 3, 2);

   double frobZ{sqrt(z.dotProduct(z))};

   EXPECT_TRUE(utils::areEqual(z.getFrobeniusNorm(), frobZ));
}

TEST(TestMatrix, TestHadamard) {
   Matrix A(4, 3);
   A.assign(1.0, 0, 0);
   A.assign(2.0, 0, 1);
   A.assign(3.0, 0, 2);
   A.assign(4.0, 1, 0);
   A.assign(5.0, 1, 1);
   A.assign(6.0, 1, 2);
   A.assign(7.0, 2, 0);
   A.assign(8.0, 2, 1);
   A.assign(9.0, 2, 2);
   A.assign(10.0, 3, 0);
   A.assign(11.0, 3, 1);
   A.assign(12.0, 3, 2);

   Matrix B(4, 3);
   B.assign(1.0, 0, 0);
   B.assign(2.0, 0, 1);
   B.assign(2.0, 0, 2);
   B.assign(3.0, 1, 0);
   B.assign(2.0, 1, 1);
   B.assign(1.0, 1, 2);
   B.assign(2.0, 2, 0);
   B.assign(3.0, 2, 1);
   B.assign(4.0, 2, 2);
   B.assign(2.0, 3, 0);
   B.assign(10.0, 3, 1);
   B.assign(100.0, 3, 2);

   Matrix C(4, 3);
   C.assign(1.0, 0, 0);
   C.assign(4.0, 0, 1);
   C.assign(6.0, 0, 2);
   C.assign(12.0, 1, 0);
   C.assign(10.0, 1, 1);
   C.assign(6.0, 1, 2);
   C.assign(14.0, 2, 0);
   C.assign(24.0, 2, 1);
   C.assign(36.0, 2, 2);
   C.assign(20.0, 3, 0);
   C.assign(110.0, 3, 1);
   C.assign(1200.0, 3, 2);

   EXPECT_TRUE(C == A.multiplyHadamardBy(B));
}

TEST(TestMatrix, TestTranspose) {
   Matrix z(4, 3);
   z.assign(1.0, 0, 0);
   z.assign(2.0, 0, 1);
   z.assign(3.0, 0, 2);
   z.assign(4.0, 1, 0);
   z.assign(5.0, 1, 1);
   z.assign(6.0, 1, 2);
   z.assign(7.0, 2, 0);
   z.assign(8.0, 2, 1);
   z.assign(9.0, 2, 2);
   z.assign(10.0, 3, 0);
   z.assign(11.0, 3, 1);
   z.assign(12.0, 3, 2);

   Matrix zt(3, 4);
   zt.assign(1.0, 0, 0);
   zt.assign(2.0, 1, 0);
   zt.assign(3.0, 2, 0);
   zt.assign(4.0, 0, 1);
   zt.assign(5.0, 1, 1);
   zt.assign(6.0, 2, 1);
   zt.assign(7.0, 0, 2);
   zt.assign(8.0, 1, 2);
   zt.assign(9.0, 2, 2);
   zt.assign(10.0, 0, 3);
   zt.assign(11.0, 1, 3);
   zt.assign(12.0, 2, 3);

   z.transpose();

   EXPECT_TRUE(zt == z);
}

TEST(TestMatrix, TestOccurences) {
   Matrix z(4, 3);
   z.assign(1.0, 0, 0);
   z.assign(2.0, 0, 1);
   z.assign(3.0, 0, 2);
   z.assign(8.0, 1, 0);
   z.assign(5.0, 1, 1);
   z.assign(9.0, 1, 2);
   z.assign(7.0, 2, 0);
   z.assign(8.0, 2, 1);
   z.assign(9.0, 2, 2);
   z.assign(10.0, 3, 0);
   z.assign(10.0, 3, 1);
   z.assign(9.0, 3, 2);

   EXPECT_TRUE(z.occurrences(8.0) == 2);
   EXPECT_TRUE(z.occurrences(58.0) == 0);
   EXPECT_TRUE(z.occurrencesInColumn(2, 9.0) == 3);
   EXPECT_TRUE(z.occurrencesInRow(3, 10.0) == 2);
}

TEST(TestMatrix, TestMisc) {
   Matrix z(4, 3);
   z.assign(1.0, 0, 0);
   z.assign(2.0, 0, 1);
   z.assign(3.0, 0, 2);
   z.assign(4.0, 1, 0);
   z.assign(5.0, 1, 1);
   z.assign(6.0, 1, 2);
   z.assign(7.0, 2, 0);
   z.assign(8.0, 2, 1);
   z.assign(9.0, 2, 2);
   z.assign(10.0, 3, 0);
   z.assign(11.0, 3, 1);
   z.assign(12.0, 3, 2);

   Matrix a;
   a = z;

   Matrix b;
   b = z * 1.0;

   Matrix v(4, 3);
   v.assign(3.0, 0, 0);
   v.assign(1.0, 0, 1);
   v.assign(2.0, 0, 2);
   v.assign(-4.0, 1, 0);
   v.assign(3.0, 1, 1);
   v.assign(1.0, 1, 2);
   v.assign(1.0, 2, 0);
   v.assign(0.0, 2, 1);
   v.assign(3.0, 2, 2);
   v.assign(2.0, 3, 0);
   v.assign(1.0, 3, 1);
   v.assign(6.0, 3, 2);

   Matrix resp(4, 3);
   resp.assign(3.0, 0, 0);
   resp.assign(1.0, 0, 1);
   resp.assign(2.0, 0, 2);
   resp.assign(-8.0, 1, 0);
   resp.assign(6.0, 1, 1);
   resp.assign(2.0, 1, 2);
   resp.assign(1.0, 2, 0);
   resp.assign(0.0, 2, 1);
   resp.assign(3.0, 2, 2);
   resp.assign(2.0, 3, 0);
   resp.assign(1.0, 3, 1);
   resp.assign(6.0, 3, 2);

   Matrix resp1(4, 3);
   resp1.assign(3.0, 0, 0);
   resp1.assign(2.0, 0, 1);
   resp1.assign(2.0, 0, 2);
   resp1.assign(-8.0, 1, 0);
   resp1.assign(12.0, 1, 1);
   resp1.assign(2.0, 1, 2);
   resp1.assign(1.0, 2, 0);
   resp1.assign(0.0, 2, 1);
   resp1.assign(3.0, 2, 2);
   resp1.assign(2.0, 3, 0);
   resp1.assign(2.0, 3, 1);
   resp1.assign(6.0, 3, 2);

   Matrix resp2(4, 3);
   resp2.assign(3.0, 0, 1);
   resp2.assign(2.0, 0, 0);
   resp2.assign(2.0, 0, 2);
   resp2.assign(-8.0, 1, 1);
   resp2.assign(12.0, 1, 0);
   resp2.assign(2.0, 1, 2);
   resp2.assign(1.0, 2, 1);
   resp2.assign(0.0, 2, 0);
   resp2.assign(3.0, 2, 2);
   resp2.assign(2.0, 3, 1);
   resp2.assign(2.0, 3, 0);
   resp2.assign(6.0, 3, 2);

   Matrix resp3(4, 3);
   resp3.assign(3.0, 0, 1);
   resp3.assign(2.0, 0, 0);
   resp3.assign(2.0, 0, 2);
   resp3.assign(2.0, 1, 1);
   resp3.assign(2.0, 1, 0);
   resp3.assign(6.0, 1, 2);
   resp3.assign(1.0, 2, 1);
   resp3.assign(0.0, 2, 0);
   resp3.assign(3.0, 2, 2);
   resp3.assign(-8.0, 3, 1);
   resp3.assign(12.0, 3, 0);
   resp3.assign(2.0, 3, 2);

   v.multiplyRowBy(1, 2.0);

   Matrix c = v;

   c.multiplyColumnBy(1, 2.0);

   Matrix d{c};
   d.swapColumns(0, 1, 0, 3);

   Matrix f{d};
   f.swapRows(1, 3, 0, 2);

   Matrix e(5, 5);
   e.fillWithRandomValues(-1.0, 2.0);

   Matrix k(1, 1);
   k.clearAndResize(3, 7);

   Matrix kk(2, 3);
   kk.fillWith(5.);
   double dd[]{5., 5., 5., 5., 5., 5.};
   Matrix rr((double *)dd, 2, 3);

   EXPECT_TRUE(a.dimension() == 2);
   EXPECT_TRUE(a == z);
   EXPECT_TRUE(b == z);
   EXPECT_TRUE(resp == v);
   EXPECT_TRUE(resp1 == c);
   EXPECT_TRUE(resp2 == d);
   EXPECT_TRUE(resp3 == f);
   EXPECT_TRUE(k.length() == 21);
   EXPECT_TRUE(e(2, 2) < 2.0 && e(2, 2) > -1.0);
   EXPECT_TRUE(kk == rr);
}

TEST(TestMatrix, TestExtracts) {
   Matrix z(4, 3);
   z.assign(1.0, 0, 0);
   z.assign(2.0, 0, 1);
   z.assign(3.0, 0, 2);
   z.assign(8.0, 1, 0);
   z.assign(5.0, 1, 1);
   z.assign(9.0, 1, 2);
   z.assign(7.0, 2, 0);
   z.assign(8.0, 2, 1);
   z.assign(9.0, 2, 2);
   z.assign(10.0, 3, 0);
   z.assign(10.0, 3, 1);
   z.assign(9.0, 3, 2);

   std::vector<Vector> rows = z.rowsToVectors();
   std::vector<Vector> cols = z.columnsToVectors();

   Vector v1{};
   v1.pushBack(2.0);
   v1.pushBack(5.0);
   v1.pushBack(8.0);
   v1.pushBack(10.0);

   Vector v2{};
   v2.pushBack(7.0);
   v2.pushBack(8.0);
   v2.pushBack(9.0);

   EXPECT_TRUE(z.columnToVector(1) == v1);
   EXPECT_TRUE(z.rowToVector(2) == v2);
   EXPECT_TRUE(cols[1] == v1);
   EXPECT_TRUE(rows[2] == v2);
}

TEST(TestMatrix, TestFromFile) {

   std::string fileName = "../../../../test/matest.txt";

   double data[]{1.0, 2.0, 3.0, 4.0, 5.0, 5.0, 6.0, 7.0, 8.0, 6.0,
                 9.0, 1.0, 2.0, 3.0, 7.0, 4.0, 5.0, 6.0, 7.0, 8.0};

   Matrix x{(double *)data, 4, 5};

   x.writeToFile(fileName, ',');

   Matrix z(fileName, ','); // development environment  relative path
                            //  Matrix z("../../test/matest.txt"); // relative path

   EXPECT_TRUE(x == z);
}

TEST(TestMatrix, TestInserts) {
   double data[] = {1., 2., 3., 4., 5., 6., 7., 8., 9., 10., 11., 12.};
   double dataresp[] = {1., 2., 3., 99., 4., 5., 6., 7., 99., 8., 9., 10., 11., 99., 12.};
   pmat::Matrix m{data, 3, 4};
   pmat::Matrix res{dataresp, 3, 5};

   m.insertColumn(2, 99.);

   pmat::Matrix m1{m};
   double dataresp1[] = {1., 2., 3., 99., 4., 88., 88., 88., 88., 88.,
                         5., 6., 7., 99., 8., 9.,  10., 11., 99., 12.};
   pmat::Matrix res1{dataresp1, 4, 5};
   m1.insertRow(0, 88.);

   double datamm[] = {1., 2., 3., 4., 5., 6., 7., 8., 9., 10., 11., 12.};
   pmat::Matrix mm{datamm, 3, 4};
   double dataLinha[] = {9, 9, 9, 9};
   pmat::Vector vecmm{dataLinha, 4};
   mm.assignToRow(1, vecmm);
   double datarespmm[] = {1., 2., 3., 4., 9., 9., 9., 9., 9., 10., 11., 12.};
   pmat::Matrix resmm{datarespmm, 3, 4};

   double datammm[] = {1., 2., 3., 4., 5., 6., 7., 8., 9., 10., 11., 12.};
   pmat::Matrix mmm{datammm, 3, 4};
   double dataCol[] = {9, 9, 9};
   pmat::Vector vecmmm{dataCol, 3};
   mmm.assignToColumn(2, vecmmm);
   double datarespmmm[] = {1., 2., 9., 4., 5., 6., 9., 8., 9., 10., 9., 12.};
   pmat::Matrix resmmm{datarespmmm, 3, 4};

   EXPECT_TRUE(m == res);
   EXPECT_TRUE(m1 == res1);
   EXPECT_TRUE(mm == resmm);
   EXPECT_TRUE(mmm == resmmm);
}

TEST(TestMatrix, TestAppends) {

   double data1[] = {1., 2., 3., 4., 5., 6.};
   pmat::Matrix m1{(double *)data1, 2, 3};

   double data2[] = {8., 8.};
   pmat::Vector v1{(double *)data2, 2};

   double data3[] = {8., 8., 8, 8};
   pmat::Vector v2{(double *)data3, 4};

   double data4[] = {9., 9., 9, 9, 9, 9};
   pmat::Matrix x1{(double *)data4, 3, 2};

   double data5[] = {9., 9., 9, 9, 9, 9, 9., 9., 9, 9, 9, 9};
   pmat::Matrix x2{(double *)data5, 2, 6};

   m1.appendRight(v1);
   m1.appendBottom(v2);
   m1.appendRight(x1);
   m1.appendBottom(x2);

   double dataResp[] = {1., 2., 3., 8., 9., 9., 4., 5., 6., 8., 9., 9., 8., 8., 8.,
                        8., 9., 9., 9., 9., 9., 9., 9., 9., 9., 9., 9., 9., 9., 9.};
   pmat::Matrix resp{(double *)dataResp, 5, 6};

   double data6[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
   pmat::Matrix m2{(double *)data6, 3, 4};

   double dataResp1[] = {7, 8, 11, 12};
   pmat::Matrix resp1{(double *)dataResp1, 2, 2};

   EXPECT_TRUE(m2.subMatrix(1, 2) == resp1);
   EXPECT_TRUE(m1 == resp);
}
