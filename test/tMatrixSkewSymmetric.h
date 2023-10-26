#include "../src/DecompositionPLU.h"
#include "../src/MatrixSkewSymmetric.h"
#include "../src/MatrixSymmetric.h"
#include "../src/pmatUtils.h"
#include "gtest/gtest.h"

using namespace pmat;

TEST(TestMatrixSkewSymmetric, TestEqualityOperator) {
   MatrixSkewSymmetric z(4);
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

   MatrixSkewSymmetric v(4);
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

TEST(TestMatrixSkewSymmetric, TestDotProduct) {
   MatrixSkewSymmetric z(4);
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

   MatrixSkewSymmetric v(4);
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

TEST(TestMatrixSkewSymmetric, TestPlus) {
   MatrixSkewSymmetric z(4);
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

   MatrixSkewSymmetric v(4);
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

   MatrixSkewSymmetric resp(4);
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
   resp1.assign(-8.0, 0, 1);
   resp1.assign(10.0, 1, 1);
   resp1.assign(14.0, 2, 0);
   resp1.assign(-14.0, 0, 2);
   resp1.assign(16.0, 2, 1);
   resp1.assign(-16.0, 1, 2);
   resp1.assign(18.0, 2, 2);
   resp1.assign(20.0, 3, 0);
   resp1.assign(-20.0, 0, 3);
   resp1.assign(22.0, 3, 1);
   resp1.assign(-22.0, 1, 3);
   resp1.assign(24.0, 3, 2);
   resp1.assign(-24.0, 2, 3);
   resp1.assign(26.0, 3, 3);

   MatrixSkewSymmetric r1(4);
   r1 = z + v;
   MatrixSkewSymmetric r2(z + v);
   z.addBy(v);

   MatrixSymmetric s{4};
   MatrixSquare rr{s + z};

   EXPECT_TRUE(resp == r1);
   EXPECT_TRUE(resp1 == r2);
   EXPECT_TRUE(resp == z);
   EXPECT_TRUE(rr == z);
}

TEST(TestMatrixSkewSymmetric, TestMinus) {
   MatrixSkewSymmetric z(4);
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

   MatrixSkewSymmetric v(4);
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

   MatrixSkewSymmetric resp(4);
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
   resp1.assign(-4.0, 0, 1);
   resp1.assign(5.0, 1, 1);
   resp1.assign(7.0, 2, 0);
   resp1.assign(-7.0, 0, 2);
   resp1.assign(8.0, 2, 1);
   resp1.assign(-8.0, 1, 2);
   resp1.assign(9.0, 2, 2);
   resp1.assign(10.0, 3, 0);
   resp1.assign(-10.0, 0, 3);
   resp1.assign(11.0, 3, 1);
   resp1.assign(-11.0, 1, 3);
   resp1.assign(12.0, 3, 2);
   resp1.assign(-12.0, 2, 3);
   resp1.assign(13.0, 3, 3);

   MatrixSkewSymmetric r1(4);
   r1 = z - v;
   MatrixSkewSymmetric r2(z - v);
   z.subtractBy(v);

   MatrixSymmetric s{4};
   MatrixSquare rr{z - s};

   EXPECT_TRUE(resp == r1);
   EXPECT_TRUE(resp1 == r2);
   EXPECT_TRUE(resp == z);
   EXPECT_TRUE(rr == z);
}

TEST(TestMatrixSkewSymmetric, TestTimes) {

   MatrixSkewSymmetric z1(2);
   z1.assign(1.0, 0, 0);
   z1.assign(2.0, 1, 0);
   z1.assign(3.0, 1, 1);

   MatrixSkewSymmetric v1(2);
   z1.assign(1.0, 0, 0);
   z1.assign(2.0, 1, 0);
   z1.assign(3.0, 1, 1);

   MatrixSkewSymmetric z(4);
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

   MatrixSkewSymmetric v(4);
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

   resp.assign(-184.0, 0, 0);
   resp.assign(-212.0, 0, 1);
   resp.assign(-172.0, 0, 2);
   resp.assign(-12.0, 0, 3);

   resp.assign(-152.0, 1, 0);
   resp.assign(-194.0, 1, 1);
   resp.assign(-300.0, 1, 2);
   resp.assign(-154.0, 1, 3);

   resp.assign(-6.0, 2, 0);
   resp.assign(-50.0, 2, 1);
   resp.assign(-194.0, 2, 2);
   resp.assign(-458.0, 2, 3);

   resp.assign(314.0, 3, 0);
   resp.assign(280.0, 3, 1);
   resp.assign(110.0, 3, 2);
   resp.assign(-216.0, 3, 3);

   MatrixSkewSymmetric resp1(4);
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

   MatrixSquare r1(4);
   r1 = z * v;
   MatrixSquare r2(z * v);
   MatrixSkewSymmetric r3;
   r3 = z;

   r3.multiplyBy(2.0);

   EXPECT_TRUE(resp == r1);
   EXPECT_TRUE(resp == r2);
   EXPECT_TRUE(z * 2.0 == resp1);
   EXPECT_TRUE(r3 == resp1);
}

TEST(TestMatrixSkewSymmetric, TestFrobenius) {
   MatrixSkewSymmetric z(4);
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

TEST(TestMatrixSkewSymmetric, TestDeterminant) {
   MatrixSkewSymmetric z(4);
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

   EXPECT_TRUE(utils::areEqual(z.decomposeToPLU().determinant(), 15384.0000000000));
}

TEST(TestMatrixSkewSymmetric, TestTranspose) {
   MatrixSkewSymmetric z(4);
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

   MatrixSkewSymmetric v(z * -1.0);

   z.transpose();

   EXPECT_TRUE(v == z);
}

TEST(TestMatrixSkewSymmetric, TestMisc) {

   MatrixSkewSymmetric z(4);
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

   MatrixSkewSymmetric v(4);
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

   MatrixSkewSymmetric resp(4);
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

   MatrixSkewSymmetric resp1(2);
   resp1.assign(0.0, 0, 0);
   resp1.assign(0.0, 1, 0);
   resp1.assign(0.0, 1, 1);

   pmat::Vector vet{4};
   vet.assign(2.0, 0);
   vet.assign(8.0, 1);
   vet.assign(10.0, 2);
   vet.assign(14.0, 3);

   pmat::Vector respv{4};
   respv.assign(-240.0, 0);
   respv.assign(-186.0, 1);
   respv.assign(0.0, 2);
   respv.assign(410.0, 3);

   Vector vv{z * vet};

   MatrixSkewSymmetric a;
   a = (std::move(z));

   v.resize(2);

   EXPECT_TRUE(a == resp);
   EXPECT_TRUE(v == resp1);
   EXPECT_TRUE(vv == respv);
}
