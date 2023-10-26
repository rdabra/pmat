#include "../src/DecompositionPLU.h"
#include "../src/MatrixLowerTriangular.h"
#include "../src/MatrixUpperTriangular.h"
#include "../src/pmatUtils.h"
#include "gtest/gtest.h"

using namespace pmat;

TEST(TestMatrixTriangular, TestEqualityOperator) {
   MatrixLowerTriangular z(4);
   z.assign(1.0, 0, 0);
   z.assign(4.0, 1, 0);
   z.assign(5.0, 1, 1);
   z.assign(7.0, 2, 0);
   z.assign(8.0, 2, 1);
   z.assign(9.0, 2, 2);
   z.assign(10.0, 3, 0);
   z.assign(11.0, 3, 1);
   z.assign(12.0, 3, 2);
   z.assign(13.0, 3, 3);

   MatrixLowerTriangular v(4);
   v.assign(1.0, 0, 0);
   v.assign(4.0, 1, 0);
   v.assign(5.0, 1, 1);
   v.assign(7.0, 2, 0);
   v.assign(8.0, 2, 1);
   v.assign(9.0, 2, 2);
   v.assign(10.0, 3, 0);
   v.assign(11.0, 3, 1);
   v.assign(12.0, 3, 2);
   v.assign(13.0, 3, 3);

   EXPECT_TRUE(v == z);
}

TEST(TestMatrixTriangular, TestDotProduct) {
   MatrixUpperTriangular z(4);
   z.assign(1.0, 3, 3);
   z.assign(4.0, 2, 2);
   z.assign(5.0, 2, 3);
   z.assign(7.0, 1, 1);
   z.assign(8.0, 1, 2);
   z.assign(9.0, 1, 3);
   z.assign(10.0, 0, 0);
   z.assign(11.0, 0, 1);
   z.assign(12.0, 0, 2);
   z.assign(13.0, 0, 3);

   MatrixUpperTriangular v(4);
   v.assign(1.5, 3, 3);
   v.assign(4.5, 2, 2);
   v.assign(5.5, 2, 3);
   v.assign(7.5, 1, 1);
   v.assign(8.5, 1, 2);
   v.assign(9.5, 1, 3);
   v.assign(10.5, 0, 0);
   v.assign(11.5, 0, 1);
   v.assign(12.5, 0, 2);
   v.assign(13.5, 0, 3);

   double resp = z.dotProduct(v);

   MatrixLowerTriangular z1(z.getTranspose());
   MatrixLowerTriangular v1(v.getTranspose());

   double resp1 = z1.dotProduct(v1);

   EXPECT_TRUE(utils::areEqual(resp, 810.0));
   EXPECT_TRUE(utils::areEqual(resp1, 810.0));
}

TEST(TestMatrixTriangular, TestPlus) {
   MatrixLowerTriangular z(4);
   z.assign(1.0, 0, 0);
   z.assign(4.0, 1, 0);
   z.assign(5.0, 1, 1);
   z.assign(7.0, 2, 0);
   z.assign(8.0, 2, 1);
   z.assign(9.0, 2, 2);
   z.assign(10.0, 3, 0);
   z.assign(11.0, 3, 1);
   z.assign(12.0, 3, 2);
   z.assign(13.0, 3, 3);

   MatrixUpperTriangular v(4);
   v.assign(10.5, 0, 0);
   v.assign(11.5, 0, 1);
   v.assign(12.5, 0, 2);
   v.assign(13.5, 0, 3);
   v.assign(7.5, 1, 1);
   v.assign(8.5, 1, 2);
   v.assign(9.5, 1, 3);
   v.assign(10.5, 2, 2);
   v.assign(11.5, 2, 3);
   v.assign(12.5, 3, 3);

   MatrixSquare resp(4);
   resp.assign(11.5, 0, 0);
   resp.assign(11.5, 0, 1);
   resp.assign(12.5, 0, 2);
   resp.assign(13.5, 0, 3);

   resp.assign(4.0, 1, 0);
   resp.assign(12.5, 1, 1);
   resp.assign(8.5, 1, 2);
   resp.assign(9.5, 1, 3);

   resp.assign(7.0, 2, 0);
   resp.assign(8.0, 2, 1);
   resp.assign(19.5, 2, 2);
   resp.assign(11.5, 2, 3);

   resp.assign(10.0, 3, 0);
   resp.assign(11.0, 3, 1);
   resp.assign(12.0, 3, 2);
   resp.assign(25.5, 3, 3);

   MatrixLowerTriangular resp2(4);
   resp2.assign(2.0, 0, 0);
   resp2.assign(8.0, 1, 0);
   resp2.assign(10.0, 1, 1);
   resp2.assign(14.0, 2, 0);
   resp2.assign(16.0, 2, 1);
   resp2.assign(18.0, 2, 2);
   resp2.assign(20.0, 3, 0);
   resp2.assign(22.0, 3, 1);
   resp2.assign(24.0, 3, 2);
   resp2.assign(26.0, 3, 3);

   MatrixLowerTriangular resp3(4);
   resp3.assign(2.0, 0, 0);
   resp3.assign(8.0, 1, 0);
   resp3.assign(10.0, 1, 1);
   resp3.assign(14.0, 2, 0);
   resp3.assign(16.0, 2, 1);
   resp3.assign(18.0, 2, 2);
   resp3.assign(20.0, 3, 0);
   resp3.assign(22.0, 3, 1);
   resp3.assign(24.0, 3, 2);
   resp3.assign(26.0, 3, 3);

   MatrixUpperTriangular resp4(4);
   resp4.assign(21, 0, 0);
   resp4.assign(23, 0, 1);
   resp4.assign(25, 0, 2);
   resp4.assign(27, 0, 3);
   resp4.assign(15, 1, 1);
   resp4.assign(17, 1, 2);
   resp4.assign(19, 1, 3);
   resp4.assign(21, 2, 2);
   resp4.assign(23, 2, 3);
   resp4.assign(25, 3, 3);

   MatrixSquare x1(4);
   x1 = z + v;
   MatrixSquare x2(z + v);
   MatrixLowerTriangular z1(z);
   MatrixLowerTriangular z2(z + z);
   MatrixUpperTriangular v2(v + v);
   z.addBy(z);

   MatrixUpperTriangular v1(v);
   MatrixSquare resp1(resp);
   MatrixUpperTriangular zz1(z1.getTranspose());
   MatrixLowerTriangular vv1(v1.getTranspose());

   resp1.transpose();
   v.addBy(v);

   EXPECT_TRUE(resp == x1);
   EXPECT_TRUE(resp == x2);
   EXPECT_TRUE(resp2 == z);
   EXPECT_TRUE(resp1 == zz1 + vv1);
   EXPECT_TRUE(resp3 == z2);
   EXPECT_TRUE(resp4 == v2);
   EXPECT_TRUE(resp4 == v);
}

TEST(TestMatrixTriangular, TestMinus) {
   MatrixLowerTriangular z(4);
   z.assign(1.0, 0, 0);
   z.assign(4.0, 1, 0);
   z.assign(5.0, 1, 1);
   z.assign(7.0, 2, 0);
   z.assign(8.0, 2, 1);
   z.assign(9.0, 2, 2);
   z.assign(10.0, 3, 0);
   z.assign(11.0, 3, 1);
   z.assign(12.0, 3, 2);
   z.assign(13.0, 3, 3);

   MatrixUpperTriangular v(4);
   v.assign(10.5, 0, 0);
   v.assign(11.5, 0, 1);
   v.assign(12.5, 0, 2);
   v.assign(13.5, 0, 3);

   v.assign(7.5, 1, 1);
   v.assign(8.5, 1, 2);
   v.assign(9.5, 1, 3);

   v.assign(10.5, 2, 2);
   v.assign(11.5, 2, 3);

   v.assign(12.5, 3, 3);

   Matrix resp(4, 4);
   resp.assign(-9.5, 0, 0);
   resp.assign(-11.5, 0, 1);
   resp.assign(-12.5, 0, 2);
   resp.assign(-13.5, 0, 3);

   resp.assign(4.0, 1, 0);
   resp.assign(-2.5, 1, 1);
   resp.assign(-8.5, 1, 2);
   resp.assign(-9.5, 1, 3);

   resp.assign(7.0, 2, 0);
   resp.assign(8.0, 2, 1);
   resp.assign(-1.5, 2, 2);
   resp.assign(-11.5, 2, 3);

   resp.assign(10.0, 3, 0);
   resp.assign(11.0, 3, 1);
   resp.assign(12.0, 3, 2);
   resp.assign(0.5, 3, 3);

   MatrixLowerTriangular resp2(4);
   resp2.assign(0.0, 0, 0);
   resp2.assign(0.0, 1, 0);
   resp2.assign(0.0, 1, 1);
   resp2.assign(0.0, 2, 0);
   resp2.assign(0.0, 2, 1);
   resp2.assign(0.0, 2, 2);
   resp2.assign(0.0, 3, 0);
   resp2.assign(0.0, 3, 1);
   resp2.assign(0.0, 3, 2);
   resp2.assign(0.0, 3, 3);

   MatrixUpperTriangular resp3(4);
   resp3.assign(0.0, 0, 0);
   resp3.assign(0.0, 0, 1);
   resp3.assign(0.0, 0, 2);
   resp3.assign(0.0, 0, 3);
   resp3.assign(0.0, 1, 1);
   resp3.assign(0.0, 1, 2);
   resp3.assign(0.0, 1, 3);
   resp3.assign(0.0, 2, 2);
   resp3.assign(0.0, 2, 3);
   resp3.assign(0.0, 3, 3);

   MatrixLowerTriangular zz(z);
   MatrixUpperTriangular vv(v);

   MatrixSquare x1(4);
   x1 = z - v;
   MatrixSquare x2(z - v);

   z.subtractBy(z);

   MatrixUpperTriangular x3(4);
   MatrixLowerTriangular x4(4);
   x3 = v - v;

   MatrixLowerTriangular vvv(v.getTranspose());
   x4 = vvv - vvv;

   MatrixUpperTriangular x5(4);
   x5 = v - v;

   MatrixSquare x6(vv - zz);

   vv.subtractBy(vv);

   EXPECT_TRUE(resp == x1);
   EXPECT_TRUE(resp == x2);
   EXPECT_TRUE(resp2 == z);
   EXPECT_TRUE(resp2 == x3);
   EXPECT_TRUE(resp2 == x4);
   EXPECT_TRUE(resp2 == x5);
   EXPECT_TRUE(resp * -1.0 == x6);
   EXPECT_TRUE(resp3 == vv);
}

TEST(TestMatrixTriangular, TestTimes) {
   MatrixLowerTriangular z(4);
   z.assign(1.0, 0, 0);
   z.assign(4.0, 1, 0);
   z.assign(5.0, 1, 1);
   z.assign(7.0, 2, 0);
   z.assign(8.0, 2, 1);
   z.assign(9.0, 2, 2);
   z.assign(10.0, 3, 0);
   z.assign(11.0, 3, 1);
   z.assign(12.0, 3, 2);
   z.assign(13.0, 3, 3);

   MatrixUpperTriangular v(4);
   v.assign(1.5, 3, 3);
   v.assign(4.5, 2, 2);
   v.assign(5.5, 2, 3);
   v.assign(7.5, 1, 1);
   v.assign(8.5, 1, 2);
   v.assign(9.5, 1, 3);
   v.assign(10.5, 0, 0);
   v.assign(11.5, 0, 1);
   v.assign(12.5, 0, 2);
   v.assign(13.5, 0, 3);

   MatrixUpperTriangular k(4);
   k.assign(10.5, 0, 0);
   k.assign(11.5, 0, 1);
   k.assign(12.5, 0, 2);
   k.assign(13.5, 0, 3);
   k.assign(7.5, 1, 1);
   k.assign(8.5, 1, 2);
   k.assign(9.5, 1, 3);
   k.assign(10.5, 2, 2);
   k.assign(11.5, 2, 3);
   k.assign(12.5, 3, 3);

   MatrixUpperTriangular kx(4);
   kx.assign(5.5, 0, 0);
   kx.assign(6.5, 0, 1);
   kx.assign(7.5, 0, 2);
   kx.assign(9.5, 0, 3);
   kx.assign(8.5, 1, 1);
   kx.assign(3.5, 1, 2);
   kx.assign(4.5, 1, 3);
   kx.assign(1.5, 2, 2);
   kx.assign(12.5, 2, 3);
   kx.assign(2.5, 3, 3);

   Vector w(4);
   w.assign(1.0, 0);
   w.assign(2.0, 1);
   w.assign(3.0, 2);
   w.assign(4.0, 3);

   Matrix resp(4, 4);
   resp.assign(10.5, 0, 0);
   resp.assign(11.5, 0, 1);
   resp.assign(12.5, 0, 2);
   resp.assign(13.5, 0, 3);

   resp.assign(42.0, 1, 0);
   resp.assign(83.5, 1, 1);
   resp.assign(92.5, 1, 2);
   resp.assign(101.5, 1, 3);

   resp.assign(73.5, 2, 0);
   resp.assign(140.5, 2, 1);
   resp.assign(196.0, 2, 2);
   resp.assign(220.0, 2, 3);

   resp.assign(105.0, 3, 0);
   resp.assign(197.5, 3, 1);
   resp.assign(272.5, 3, 2);
   resp.assign(325.0, 3, 3);

   MatrixLowerTriangular resp2(4);
   resp2.assign(2.0, 0, 0);
   resp2.assign(8.0, 1, 0);
   resp2.assign(10.0, 1, 1);
   resp2.assign(14.0, 2, 0);
   resp2.assign(16.0, 2, 1);
   resp2.assign(18.0, 2, 2);
   resp2.assign(20.0, 3, 0);
   resp2.assign(22.0, 3, 1);
   resp2.assign(24.0, 3, 2);
   resp2.assign(26.0, 3, 3);

   Matrix resp3(4, 4);
   resp3.assign(279., 0, 0);
   resp3.assign(306., 0, 1);
   resp3.assign(274.5, 0, 2);
   resp3.assign(175.5, 0, 3);

   resp3.assign(184.5, 1, 0);
   resp3.assign(210., 1, 1);
   resp3.assign(190.5, 1, 2);
   resp3.assign(123.5, 1, 3);

   resp3.assign(86.5, 2, 0);
   resp3.assign(96.5, 2, 1);
   resp3.assign(106.5, 2, 2);
   resp3.assign(71.5, 2, 3);

   resp3.assign(15.0, 3, 0);
   resp3.assign(16.5, 3, 1);
   resp3.assign(18., 3, 2);
   resp3.assign(19.5, 3, 3);

   MatrixUpperTriangular resp5(4);
   resp5.assign(57.75, 0, 0);
   resp5.assign(166.0, 0, 1);
   resp5.assign(137.75, 0, 2);
   resp5.assign(341.5, 0, 3);
   resp5.assign(63.75, 1, 1);
   resp5.assign(39., 1, 2);
   resp5.assign(163.75, 1, 3);
   resp5.assign(15.75, 2, 2);
   resp5.assign(160., 2, 3);
   resp5.assign(31.25, 3, 3);

   Vector respVecLow(4);
   respVecLow.assign(1.0, 0);
   respVecLow.assign(14.0, 1);
   respVecLow.assign(50.0, 2);
   respVecLow.assign(120.0, 3);

   Vector respVecUp(4);
   respVecUp.assign(125.0, 0);
   respVecUp.assign(78.5, 1);
   respVecUp.assign(35.5, 2);
   respVecUp.assign(6.0, 3);

   MatrixUpperTriangular resp6(4);
   resp6.assign(3., 3, 3);
   resp6.assign(9., 2, 2);
   resp6.assign(11., 2, 3);
   resp6.assign(15., 1, 1);
   resp6.assign(17., 1, 2);
   resp6.assign(19., 1, 3);
   resp6.assign(21., 0, 0);
   resp6.assign(23., 0, 1);
   resp6.assign(25., 0, 2);
   resp6.assign(27., 0, 3);

   Vector low(z * w);
   Vector up(v * w);

   MatrixSquare x1(4);
   x1 = z * v;
   MatrixSquare x2(z * v);
   MatrixSquare x5(v * z);

   MatrixLowerTriangular x3(4);
   x3 = z * 2.0;
   MatrixLowerTriangular x4(z * 2.0);
   z.multiplyBy(2.0);

   MatrixUpperTriangular x6(v * 2.0);
   v.multiplyBy(2.0);

   EXPECT_TRUE(resp == x1);
   EXPECT_TRUE(resp == x2);
   EXPECT_TRUE(resp2 == x3);
   EXPECT_TRUE(resp2 == x4);
   EXPECT_TRUE(resp2 == z);
   EXPECT_TRUE(resp3 == x5);
   EXPECT_TRUE(respVecLow == low);
   EXPECT_TRUE(respVecUp == up);
   EXPECT_TRUE(resp6 == x6);
   EXPECT_TRUE(resp6 == v);
   EXPECT_TRUE(resp5 == k * kx);
   EXPECT_TRUE(resp6.at(0, 3) == 27.);
}

TEST(TestMatrixTriangular, TestFrobenius) {
   MatrixLowerTriangular z(4);
   z.assign(1.0, 0, 0);
   z.assign(4.0, 1, 0);
   z.assign(5.0, 1, 1);
   z.assign(7.0, 2, 0);
   z.assign(8.0, 2, 1);
   z.assign(9.0, 2, 2);
   z.assign(10.0, 3, 0);
   z.assign(11.0, 3, 1);
   z.assign(12.0, 3, 2);
   z.assign(13.0, 3, 3);

   double frobZ{sqrt(z.dotProduct(z))};

   MatrixUpperTriangular v(4);
   v.assign(1.0, 3, 3);
   v.assign(4.0, 2, 2);
   v.assign(5.0, 2, 3);
   v.assign(7.0, 1, 1);
   v.assign(8.0, 1, 2);
   v.assign(9.0, 1, 3);
   v.assign(10.0, 0, 0);
   v.assign(11.0, 0, 1);
   v.assign(12.0, 0, 2);
   v.assign(13.0, 0, 3);

   double frobV{sqrt(v.dotProduct(v))};

   EXPECT_TRUE(utils::areEqual(z.getFrobeniusNorm(), frobZ));
   EXPECT_TRUE(utils::areEqual(v.getFrobeniusNorm(), frobV));
   EXPECT_TRUE(v.at(0, 3) == 13.);
}

TEST(TestMatrixTriangular, TestLUDecomp) {

   MatrixUpperTriangular v(4);
   v.assign(1.0, 3, 3);
   v.assign(4.0, 2, 2);
   v.assign(5.0, 2, 3);
   v.assign(7.0, 1, 1);
   v.assign(8.0, 1, 2);
   v.assign(9.0, 1, 3);
   v.assign(10.0, 0, 0);
   v.assign(11.0, 0, 1);
   v.assign(12.0, 0, 2);
   v.assign(13.0, 0, 3);

   MatrixLowerTriangular l((v.decomposeToPLU().matL()));
   MatrixUpperTriangular u((v.decomposeToPLU().matU()));

   EXPECT_TRUE(l * u == v);
}

TEST(TestMatrixTriangular, TestDeterminant) {
   MatrixLowerTriangular z(4);
   z.assign(1.0, 0, 0);
   z.assign(4.0, 1, 0);
   z.assign(5.0, 1, 1);
   z.assign(7.0, 2, 0);
   z.assign(8.0, 2, 1);
   z.assign(9.0, 2, 2);
   z.assign(10.0, 3, 0);
   z.assign(11.0, 3, 1);
   z.assign(12.0, 3, 2);
   z.assign(13.0, 3, 3);

   EXPECT_TRUE(utils::areEqual(z.determinant(), 585.0));
}

TEST(TestMatrixTriangular, TestTranspose) {
   MatrixLowerTriangular z(4);
   z.assign(1.0, 0, 0);
   z.assign(4.0, 1, 0);
   z.assign(5.0, 1, 1);
   z.assign(7.0, 2, 0);
   z.assign(8.0, 2, 1);
   z.assign(9.0, 2, 2);
   z.assign(10.0, 3, 0);
   z.assign(11.0, 3, 1);
   z.assign(12.0, 3, 2);
   z.assign(13.0, 3, 3);

   MatrixUpperTriangular zt(4);
   zt.assign(1.0, 0, 0);
   zt.assign(4.0, 0, 1);
   zt.assign(5.0, 1, 1);
   zt.assign(7.0, 0, 2);
   zt.assign(8.0, 1, 2);
   zt.assign(9.0, 2, 2);
   zt.assign(10.0, 0, 3);
   zt.assign(11.0, 1, 3);
   zt.assign(12.0, 2, 3);
   zt.assign(13.0, 3, 3);

   MatrixUpperTriangular zz(z.getTranspose());

   EXPECT_TRUE(zz == zt);
}

TEST(TestMatrixTriangular, TestInverse) {
   MatrixLowerTriangular z(4);
   z.assign(1.0, 0, 0);
   z.assign(4.0, 1, 0);
   z.assign(5.0, 1, 1);
   z.assign(7.0, 2, 0);
   z.assign(8.0, 2, 1);
   z.assign(9.0, 2, 2);
   z.assign(10.0, 3, 0);
   z.assign(11.0, 3, 1);
   z.assign(12.0, 3, 2);
   z.assign(13.0, 3, 3);

   MatrixLowerTriangular zz(4);
   zz.assign(1.0, 0, 0);
   zz.assign(4.0, 1, 0);
   zz.assign(5.0, 1, 1);
   zz.assign(7.0, 2, 0);
   zz.assign(8.0, 2, 1);
   zz.assign(0.0, 2, 2);
   zz.assign(10.0, 3, 0);
   zz.assign(11.0, 3, 1);
   zz.assign(12.0, 3, 2);
   zz.assign(13.0, 3, 3);

   EXPECT_TRUE(z.isInvertible());
   EXPECT_FALSE(zz.isInvertible());
}

TEST(TestMatrixTriangular, TestSwaps) {
   MatrixLowerTriangular z(4);
   z.assign(1.0, 0, 0);
   z.assign(4.0, 1, 0);
   z.assign(5.0, 1, 1);
   z.assign(7.0, 2, 0);
   z.assign(8.0, 2, 1);
   z.assign(9.0, 2, 2);
   z.assign(10.0, 3, 0);
   z.assign(11.0, 3, 1);
   z.assign(12.0, 3, 2);
   z.assign(13.0, 3, 3);

   MatrixSquare resp(4);
   resp.assign(0.0, 0, 0);
   resp.assign(0.0, 0, 1);
   resp.assign(1.0, 0, 2);
   resp.assign(0.0, 0, 3);

   resp.assign(0.0, 1, 0);
   resp.assign(5.0, 1, 1);
   resp.assign(4.0, 1, 2);
   resp.assign(0.0, 1, 3);

   resp.assign(9.0, 2, 0);
   resp.assign(8.0, 2, 1);
   resp.assign(7.0, 2, 2);
   resp.assign(0.0, 2, 3);

   resp.assign(12.0, 3, 0);
   resp.assign(11.0, 3, 1);
   resp.assign(10.0, 3, 2);
   resp.assign(13.0, 3, 3);

   MatrixSquare resp1(4);
   resp1.assign(1.0, 0, 0);
   resp1.assign(0.0, 0, 1);
   resp1.assign(0.0, 0, 2);
   resp1.assign(0.0, 0, 3);

   resp1.assign(10.0, 1, 0);
   resp1.assign(11.0, 1, 1);
   resp1.assign(12.0, 1, 2);
   resp1.assign(13.0, 1, 3);

   resp1.assign(7.0, 2, 0);
   resp1.assign(8.0, 2, 1);
   resp1.assign(9.0, 2, 2);
   resp1.assign(0.0, 2, 3);

   resp1.assign(4.0, 3, 0);
   resp1.assign(5.0, 3, 1);
   resp1.assign(0.0, 3, 2);
   resp1.assign(0.0, 3, 3);

   MatrixSquare cols(z.getSwappedByColumns(0, 2));
   MatrixSquare rows(z.getSwappedByRows(1, 3));

   EXPECT_TRUE(cols == resp);
   EXPECT_TRUE(rows == resp1);
}

TEST(TestMatrixTriangular, TestMisc) {
   MatrixLowerTriangular z(4);
   z.assign(1.0, 0, 0);
   z.assign(4.0, 1, 0);
   z.assign(5.0, 1, 1);
   z.assign(7.0, 2, 0);
   z.assign(8.0, 2, 1);
   z.assign(9.0, 2, 2);
   z.assign(10.0, 3, 0);
   z.assign(11.0, 3, 1);
   z.assign(12.0, 3, 2);
   z.assign(13.0, 3, 3);

   MatrixLowerTriangular resp1(4);
   resp1.assign(1.0, 0, 0);
   resp1.assign(4.0, 1, 0);
   resp1.assign(5.0, 1, 1);
   resp1.assign(10.0, 2, 0);
   resp1.assign(11.0, 2, 1);
   resp1.assign(12.0, 2, 2);
   resp1.assign(7.0, 3, 0);
   resp1.assign(8.0, 3, 1);
   resp1.assign(9.0, 3, 2);
   resp1.assign(13.0, 3, 3);

   MatrixLowerTriangular resp2(4);
   resp2.assign(1.0, 0, 0);
   resp2.assign(4.0, 1, 0);
   resp2.assign(5.0, 1, 1);
   resp2.assign(7.0, 2, 0);
   resp2.assign(9.0, 2, 1);
   resp2.assign(8.0, 2, 2);
   resp2.assign(10.0, 3, 0);
   resp2.assign(12.0, 3, 1);
   resp2.assign(11.0, 3, 2);
   resp2.assign(13.0, 3, 3);

   MatrixLowerTriangular zz(z);

   MatrixLowerTriangular zzz(z);
   zzz.swapRows(2, 3, 0, 2);

   MatrixLowerTriangular zzzz(z);
   zzzz.swapColumns(1, 2, 2, 3);

   MatrixUpperTriangular a(z.getTranspose());

   MatrixUpperTriangular b(a);

   MatrixLowerTriangular t(z);

   MatrixLowerTriangular c(std::move(t));

   MatrixUpperTriangular d;
   d = a;
   MatrixLowerTriangular e;
   e = z;

   MatrixUpperTriangular t1(a);

   MatrixUpperTriangular f;
   f = std::move(t1);

   MatrixLowerTriangular ee(5);
   ee.fillWithRandomValues(-1.0, 2.0);

   MatrixUpperTriangular eee(5);
   eee.fillWithRandomValues(-1.0, 2.0);

   EXPECT_TRUE(z == zz);
   EXPECT_TRUE(b == a);
   EXPECT_TRUE(c == z);
   EXPECT_TRUE(d == a);
   EXPECT_TRUE(e == z);
   EXPECT_TRUE(f == a);
   EXPECT_TRUE(resp1 == zzz);
   EXPECT_TRUE(resp2 == zzzz);
   EXPECT_TRUE(ee(2, 2) < 2.0 && ee(2, 2) > -1.0);
   EXPECT_TRUE(eee(2, 2) < 2.0 && eee(2, 2) > -1.0);
}

TEST(TestMatrixTriangular, TestMisc2) {
   MatrixUpperTriangular z(4);
   z.assign(1.0, 0, 0);
   z.assign(4.0, 0, 1);
   z.assign(5.0, 0, 2);
   z.assign(7.0, 0, 3);
   z.assign(8.0, 1, 1);
   z.assign(9.0, 1, 2);
   z.assign(10.0, 1, 3);
   z.assign(11.0, 2, 2);
   z.assign(12.0, 2, 3);
   z.assign(13.0, 3, 3);

   MatrixUpperTriangular resp(4);
   resp.assign(2.0, 0, 0);
   resp.assign(8.0, 0, 1);
   resp.assign(10.0, 0, 2);
   resp.assign(14.0, 0, 3);
   resp.assign(16.0, 1, 1);
   resp.assign(18.0, 1, 2);
   resp.assign(20.0, 1, 3);
   resp.assign(22.0, 2, 2);
   resp.assign(24.0, 2, 3);
   resp.assign(26.0, 3, 3);

   MatrixUpperTriangular kx(4);
   kx.assign(5.5, 0, 0);
   kx.assign(6.5, 0, 1);
   kx.assign(7.5, 0, 2);
   kx.assign(9.5, 0, 3);
   kx.assign(8.5, 1, 1);
   kx.assign(3.5, 1, 2);
   kx.assign(4.5, 1, 3);
   kx.assign(1.5, 2, 2);
   kx.assign(12.5, 2, 3);
   kx.assign(2.5, 3, 3);

   kx.swapRows(1, 2, 2, 3);

   MatrixUpperTriangular resp1(4);
   resp1.assign(5.5, 0, 0);
   resp1.assign(6.5, 0, 1);
   resp1.assign(7.5, 0, 2);
   resp1.assign(9.5, 0, 3);
   resp1.assign(8.5, 1, 1);
   resp1.assign(1.5, 1, 2);
   resp1.assign(12.5, 1, 3);
   resp1.assign(3.5, 2, 2);
   resp1.assign(4.5, 2, 3);
   resp1.assign(2.5, 3, 3);

   MatrixUpperTriangular kxx(4);
   kxx.assign(6.5, 0, 1);
   kxx.assign(7.5, 0, 2);
   kxx.assign(5.5, 0, 0);
   kxx.assign(9.5, 0, 3);
   kxx.assign(8.5, 1, 1);
   kxx.assign(3.5, 1, 2);
   kxx.assign(4.5, 1, 3);
   kxx.assign(1.5, 2, 2);
   kxx.assign(12.5, 2, 3);
   kxx.assign(2.5, 3, 3);

   kxx.swapColumns(2, 3, 0, 2);

   MatrixUpperTriangular resp2(4);
   resp2.assign(6.5, 0, 1);
   resp2.assign(9.5, 0, 2);
   resp2.assign(5.5, 0, 0);
   resp2.assign(7.5, 0, 3);
   resp2.assign(8.5, 1, 1);
   resp2.assign(4.5, 1, 2);
   resp2.assign(3.5, 1, 3);
   resp2.assign(12.5, 2, 2);
   resp2.assign(1.5, 2, 3);
   resp2.assign(2.5, 3, 3);

   MatrixUpperTriangular aux{z * 2.0};
   MatrixUpperTriangular zz(std::move(aux));

   z.resize(3);

   EXPECT_TRUE(zz == resp);
   EXPECT_TRUE(z.size() == 3);
   EXPECT_TRUE(kx == resp1);
   EXPECT_TRUE(kxx == resp2);
}
