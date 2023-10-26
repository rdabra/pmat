#include "../src/DecompositionCholesky.h"
#include "../src/DecompositionPLU.h"
#include "../src/MatrixSymmetric.h"
#include "../src/pmatUtils.h"
#include "gtest/gtest.h"

using namespace pmat;

TEST(TestMatrixSymmetric, TestEqualityOperator) {
   MatrixSymmetric z(4);
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

   MatrixSymmetric v(4);
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

TEST(TestMatrixSymmetric, TestDotProduct) {
   MatrixSymmetric z(4);
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

   MatrixSymmetric v(4);
   v.assign(1.5, 0, 0);
   v.assign(4.5, 1, 0);
   v.assign(5.5, 1, 1);
   v.assign(7.5, 2, 0);
   v.assign(8.5, 2, 1);
   v.assign(9.5, 2, 2);
   v.assign(10.5, 3, 0);
   v.assign(11.5, 3, 1);
   v.assign(12.5, 3, 2);
   v.assign(13.5, 3, 3);

   double resp = z.dotProduct(v);

   EXPECT_TRUE(utils::areEqual(resp, 1330.0));
}

TEST(TestMatrixSymmetric, TestPlus) {
   MatrixSymmetric z(4);
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

   MatrixSymmetric v(4);
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

   MatrixSymmetric resp(4);
   resp.assign(2.0, 0, 0);
   resp.assign(8.0, 1, 0);
   resp.assign(10.0, 1, 1);
   resp.assign(14.0, 2, 0);
   resp.assign(16.0, 2, 1);
   resp.assign(18.0, 2, 2);
   resp.assign(20.0, 3, 0);
   resp.assign(22.0, 3, 1);
   resp.assign(24.0, 3, 2);
   resp.assign(26.0, 3, 3);

   MatrixSquare resp1(4);
   resp1.assign(2.0, 0, 0);
   resp1.assign(8.0, 1, 0);
   resp1.assign(8.0, 0, 1);
   resp1.assign(10.0, 1, 1);
   resp1.assign(14.0, 2, 0);
   resp1.assign(14.0, 0, 2);
   resp1.assign(16.0, 2, 1);
   resp1.assign(16.0, 1, 2);
   resp1.assign(18.0, 2, 2);
   resp1.assign(20.0, 3, 0);
   resp1.assign(20.0, 0, 3);
   resp1.assign(22.0, 3, 1);
   resp1.assign(22.0, 1, 3);
   resp1.assign(24.0, 3, 2);
   resp1.assign(24.0, 2, 3);
   resp1.assign(26.0, 3, 3);

   MatrixSymmetric r1(4);
   r1 = z + v;
   MatrixSymmetric r2(z + v);
   z.addBy(v);

   EXPECT_TRUE(resp == r1);
   EXPECT_TRUE(resp1 == r2);
   EXPECT_TRUE(resp == z);
}

TEST(TestMatrixSymmetric, TestMinus) {
   MatrixSymmetric z(4);
   z.assign(2.0, 0, 0);
   z.assign(8.0, 1, 0);
   z.assign(10.0, 1, 1);
   z.assign(14.0, 2, 0);
   z.assign(16.0, 2, 1);
   z.assign(18.0, 2, 2);
   z.assign(20.0, 3, 0);
   z.assign(22.0, 3, 1);
   z.assign(24.0, 3, 2);
   z.assign(26.0, 3, 3);

   MatrixSymmetric v(4);
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

   MatrixSymmetric resp(4);
   resp.assign(1.0, 0, 0);
   resp.assign(4.0, 1, 0);
   resp.assign(5.0, 1, 1);
   resp.assign(7.0, 2, 0);
   resp.assign(8.0, 2, 1);
   resp.assign(9.0, 2, 2);
   resp.assign(10.0, 3, 0);
   resp.assign(11.0, 3, 1);
   resp.assign(12.0, 3, 2);
   resp.assign(13.0, 3, 3);

   MatrixSquare resp1(4);
   resp1.assign(1.0, 0, 0);
   resp1.assign(4.0, 1, 0);
   resp1.assign(4.0, 0, 1);
   resp1.assign(5.0, 1, 1);
   resp1.assign(7.0, 2, 0);
   resp1.assign(7.0, 0, 2);
   resp1.assign(8.0, 2, 1);
   resp1.assign(8.0, 1, 2);
   resp1.assign(9.0, 2, 2);
   resp1.assign(10.0, 3, 0);
   resp1.assign(10.0, 0, 3);
   resp1.assign(11.0, 3, 1);
   resp1.assign(11.0, 1, 3);
   resp1.assign(12.0, 3, 2);
   resp1.assign(12.0, 2, 3);
   resp1.assign(13.0, 3, 3);

   MatrixSymmetric r1(4);
   r1 = z - v;
   MatrixSymmetric r2(z - v);
   z.subtractBy(v);

   EXPECT_TRUE(resp == r1);
   EXPECT_TRUE(resp1 == r2);
   EXPECT_TRUE(resp == z);
}

TEST(TestMatrixSymmetric, TestTimes) {
   MatrixSymmetric z(4);
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

   MatrixSymmetric v(4);
   v.assign(2.0, 0, 0);
   v.assign(5.0, 1, 0);
   v.assign(6.0, 1, 1);
   v.assign(8.0, 2, 0);
   v.assign(9.0, 2, 1);
   v.assign(10.0, 2, 2);
   v.assign(11.0, 3, 0);
   v.assign(12.0, 3, 1);
   v.assign(13.0, 3, 2);
   v.assign(14.0, 3, 3);

   MatrixSquare resp(4);
   resp.assign(188.0, 0, 0);
   resp.assign(212.0, 0, 1);
   resp.assign(244.0, 0, 2);
   resp.assign(290.0, 0, 3);

   resp.assign(218.0, 1, 0);
   resp.assign(254.0, 1, 1);
   resp.assign(300.0, 1, 2);
   resp.assign(362.0, 1, 3);

   resp.assign(258.0, 2, 0);
   resp.assign(308.0, 2, 1);
   resp.assign(374.0, 2, 2);
   resp.assign(458.0, 2, 3);

   resp.assign(314.0, 3, 0);
   resp.assign(380.0, 3, 1);
   resp.assign(468.0, 3, 2);
   resp.assign(580.0, 3, 3);

   MatrixSymmetric resp1(4);
   resp1.assign(2.0, 0, 0);
   resp1.assign(8.0, 1, 0);
   resp1.assign(10.0, 1, 1);
   resp1.assign(14.0, 2, 0);
   resp1.assign(16.0, 2, 1);
   resp1.assign(18.0, 2, 2);
   resp1.assign(20.0, 3, 0);
   resp1.assign(22.0, 3, 1);
   resp1.assign(24.0, 3, 2);
   resp1.assign(26.0, 3, 3);

   pmat::Vector vet{4};
   vet.assign(2.0, 0);
   vet.assign(8.0, 1);
   vet.assign(10.0, 2);
   vet.assign(14.0, 3);

   pmat::Vector respv{4};
   respv.assign(244.0, 0);
   respv.assign(282.0, 1);
   respv.assign(336.0, 2);
   respv.assign(410.0, 3);

   pmat::Matrix x{4, 4};
   Matrix rrr{z * x};

   MatrixSquare r1(4);
   r1 = z * v;
   MatrixSquare r2(z * v);
   MatrixSymmetric r3;
   r3 = z;

   r3.multiplyBy(2.0);

   EXPECT_TRUE(resp == r1);
   EXPECT_TRUE(resp == r2);
   EXPECT_TRUE(z * 2.0 == resp1);
   EXPECT_TRUE(r3 == resp1);
   EXPECT_TRUE(z * vet == respv);
}

TEST(TestMatrixSymmetric, TestFrobenius) {
   MatrixSymmetric z(4);
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

   EXPECT_TRUE(utils::areEqual(z.getFrobeniusNorm(), 35.55277767));
}

TEST(TestMatrixSymmetric, TestPositiveDefinite) {
   MatrixSymmetric z(4);
   z.assign(1.0, 0, 0);
   z.assign(-1.0, 1, 0);
   z.assign(4.0, 1, 1);
   z.assign(2.0, 2, 0);
   z.assign(-1.0, 2, 1);
   z.assign(6.0, 2, 2);
   z.assign(0.0, 3, 0);
   z.assign(1.0, 3, 1);
   z.assign(-2.0, 3, 2);
   z.assign(4.0, 3, 3);

   DecompositionCholesky ch{z.decomposeToCholesky()};

   MatrixLowerTriangular chol(ch.choleskyFactor());
   MatrixUpperTriangular cholt(chol.getTranspose());

   EXPECT_TRUE(ch.isPositiveDefinite());
   EXPECT_TRUE((chol * cholt) == z);
}

TEST(TestMatrixSymmetric, TestInverse) {

   MatrixSymmetric z(4);
   z.assign(1.0, 0, 0);
   z.assign(-1.0, 1, 0);
   z.assign(4.0, 1, 1);
   z.assign(2.0, 2, 0);
   z.assign(-1.0, 2, 1);
   z.assign(6.0, 2, 2);
   z.assign(0.0, 3, 0);
   z.assign(1.0, 3, 1);
   z.assign(-2.0, 3, 2);
   z.assign(4.0, 3, 3);

   MatrixSymmetric zinv(4);
   zinv.assign(37.0, 0, 0);
   zinv.assign(8.0, 1, 0);
   zinv.assign(2.0, 1, 1);
   zinv.assign(-14.0, 2, 0);
   zinv.assign(-3.0, 2, 1);
   zinv.assign(5.5, 2, 2);
   zinv.assign(-9.0, 3, 0);
   zinv.assign(-2.0, 3, 1);
   zinv.assign(3.5, 3, 2);
   zinv.assign(2.5, 3, 3);

   MatrixSymmetric zz(z.decomposeToCholesky().inverseAsSymmetric());

   EXPECT_TRUE(zz == zinv);
}

TEST(TestMatrixSymmetric, TestDeterminant) {
   MatrixSymmetric z(4);
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

   MatrixSymmetric b(4);
   b.assign(1.0, 0, 0);
   b.assign(-1.0, 1, 0);
   b.assign(4.0, 1, 1);
   b.assign(2.0, 2, 0);
   b.assign(-1.0, 2, 1);
   b.assign(6.0, 2, 2);
   b.assign(0.0, 3, 0);
   b.assign(1.0, 3, 1);
   b.assign(-2.0, 3, 2);
   b.assign(4.0, 3, 3);

   EXPECT_TRUE(utils::areEqual(z.decomposeToCholesky().determinant(), -116.0));
   EXPECT_TRUE(utils::areEqual(b.decomposeToCholesky().determinant(), 2.0));
}

TEST(TestMatrixSymmetric, TestTranspose) {
   MatrixSymmetric z(4);
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

   MatrixSymmetric v(z);

   z.transpose();

   EXPECT_TRUE(v == z);
}

TEST(TestMatrixSymmetric, TestMisc) {

   MatrixSymmetric z(4);
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

   MatrixSymmetric v(4);
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

   MatrixSymmetric resp(4);
   resp.assign(1.0, 0, 0);
   resp.assign(4.0, 1, 0);
   resp.assign(5.0, 1, 1);
   resp.assign(7.0, 2, 0);
   resp.assign(8.0, 2, 1);
   resp.assign(9.0, 2, 2);
   resp.assign(10.0, 3, 0);
   resp.assign(11.0, 3, 1);
   resp.assign(12.0, 3, 2);
   resp.assign(13.0, 3, 3);

   MatrixSymmetric resp1(2);
   resp1.assign(0.0, 0, 0);
   resp1.assign(0.0, 1, 0);
   resp1.assign(0.0, 1, 1);

   MatrixSymmetric a;
   a = (std::move(z));

   v.resize(2);

   EXPECT_TRUE(a == resp);
   EXPECT_TRUE(v == resp1);
}

TEST(TestMatrixSymmetric, TestLinearSolve) {
   MatrixSymmetric z(4);
   z.assign(1.0, 0, 0);
   z.assign(-1.0, 1, 0);
   z.assign(4.0, 1, 1);
   z.assign(2.0, 2, 0);
   z.assign(-1.0, 2, 1);
   z.assign(6.0, 2, 2);
   z.assign(0.0, 3, 0);
   z.assign(1.0, 3, 1);
   z.assign(-2.0, 3, 2);
   z.assign(4.0, 3, 3);

   Vector b(4);

   b.assign(1.0, 0);
   b.assign(3.0, 1);
   b.assign(2.0, 2);
   b.assign(1.0, 3);

   DecompositionCholesky dch = z.decomposeToCholesky();

   const Vector x(dch.linearSolve(b));

   Vector resp(4);

   resp.assign(24.0, 0);
   resp.assign(6.0, 1);
   resp.assign(-8.5, 2);
   resp.assign(-5.5, 3);

   EXPECT_TRUE(x == resp);
   EXPECT_TRUE(resp.at(3) == -5.5);
   EXPECT_TRUE(z.at(3, 3) == 4);
}

TEST(TestMatrixSymmetric, TestStatics) {
   double dat[]{1.,  2,  3,  4,  3.,  4,  1,  2,  7.,  8,  9,  1,  4.,  3,  2,  1,
                11., 21, 31, 41, 31., 41, 11, 21, 71., 81, 91, 13, 41., 31, 21, 12};

   Matrix z((double *)dat, 8, 4);

   double dat1[]{7879., 8606., 8081., 2538., 8606., 9737., 9212., 3174.,
                 8081., 9212., 9899., 2962., 2538., 3174., 2962., 2457.};

   MatrixSymmetric resp{MatrixSquare{(double *)dat1, 4}, pmat::utils::TriangType::LOWER};

   EXPECT_TRUE(MatrixSymmetric::gramMatrix(z) == resp);
}