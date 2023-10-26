#include "../src/DecompositionPLU.h"
#include "../src/DecompositionPQR.h"
#include "../src/DecompositionSAS.h"
#include "../src/MatrixLowerTriangular.h"
#include "../src/MatrixSkewSymmetric.h"
#include "../src/MatrixSquare.h"
#include "../src/MatrixSymmetric.h"
#include "../src/MatrixUpperTriangular.h"
#include "../src/pmatUtils.h"
#include "gtest/gtest.h"

using namespace pmat;

TEST(TestMatrixSquare, TestTrace) {
   MatrixSquare A(5);

   A.assign(4.0, 0, 0);
   A.assign(3.0, 0, 1);
   A.assign(2.0, 0, 2);
   A.assign(1.0, 0, 3);
   A.assign(6.0, 0, 4);

   A.assign(2.0, 1, 0);
   A.assign(3.0, 1, 1);
   A.assign(1.0, 1, 2);
   A.assign(2.0, 1, 3);
   A.assign(9.0, 1, 4);

   A.assign(1.0, 2, 0);
   A.assign(3.0, 2, 1);
   A.assign(2.0, 2, 2);
   A.assign(5.0, 2, 3);
   A.assign(1.0, 2, 4);

   A.assign(2.0, 3, 0);
   A.assign(7.0, 3, 1);
   A.assign(6.0, 3, 2);
   A.assign(4.0, 3, 3);
   A.assign(3.0, 3, 4);

   A.assign(1.0, 4, 0);
   A.assign(7.0, 4, 1);
   A.assign(6.0, 4, 2);
   A.assign(5.0, 4, 3);
   A.assign(3.0, 4, 4);

   EXPECT_TRUE(A.trace() == 16.0);
}

TEST(TestMatrixSquare, TestDeterminant) {
   MatrixSquare A(4);

   A.assign(1.0, 0, 0);
   A.assign(2.0, 0, 1);
   A.assign(3.0, 0, 2);
   A.assign(4.0, 0, 3);

   A.assign(1.0, 1, 0);
   A.assign(3.0, 1, 1);
   A.assign(2.0, 1, 2);
   A.assign(5.0, 1, 3);

   A.assign(2.0, 2, 0);
   A.assign(1.0, 2, 1);
   A.assign(6.0, 2, 2);
   A.assign(3.0, 2, 3);

   A.assign(3.0, 3, 0);
   A.assign(2.0, 3, 1);
   A.assign(1.0, 3, 2);
   A.assign(1.0, 3, 3);

   MatrixSquare B(3);

   B.assign(1.0, 0, 0);
   B.assign(1.0, 0, 1);
   B.assign(1.0, 0, 2);

   B.assign(1.0, 1, 0);
   B.assign(1.0, 1, 1);
   B.assign(3.0, 1, 2);

   B.assign(2.0, 2, 0);
   B.assign(5.0, 2, 1);
   B.assign(8.0, 2, 2);

   MatrixSquare C(3);

   DecompositionPLU dA{A.decomposeToPLU()};
   DecompositionPLU dB{B.decomposeToPLU()};
   DecompositionPLU dC{C.decomposeToPLU()};

   EXPECT_TRUE(utils::areEqual(dA.determinant(), -3.0));
   EXPECT_TRUE(utils::areEqual(dB.determinant(), -6.0));
   EXPECT_TRUE(dA.isInvertible());
   EXPECT_FALSE(dC.isInvertible());
}

TEST(TestMatrixSquare, TestDecompPLU) {
   MatrixSquare A(4);

   A.assign(1.0, 0, 0);
   A.assign(2.0, 0, 1);
   A.assign(3.0, 0, 2);
   A.assign(4.0, 0, 3);

   A.assign(1.0, 1, 0);
   A.assign(3.0, 1, 1);
   A.assign(2.0, 1, 2);
   A.assign(5.0, 1, 3);

   A.assign(2.0, 2, 0);
   A.assign(1.0, 2, 1);
   A.assign(6.0, 2, 2);
   A.assign(3.0, 2, 3);

   A.assign(3.0, 3, 0);
   A.assign(2.0, 3, 1);
   A.assign(1.0, 3, 2);
   A.assign(1.0, 3, 3);

   MatrixSquare B(3);

   B.assign(1.0, 0, 0);
   B.assign(2.0, 0, 1);
   B.assign(3.0, 0, 2);

   B.assign(2.0, 1, 0);
   B.assign(4.0, 1, 1);
   B.assign(7.0, 1, 2);

   B.assign(3.0, 2, 0);
   B.assign(5.0, 2, 1);
   B.assign(3.0, 2, 2);

   MatrixSquare C(3);

   C.assign(1.0, 0, 0);
   C.assign(1.0, 0, 1);
   C.assign(1.0, 0, 2);

   C.assign(1.0, 1, 0);
   C.assign(1.0, 1, 1);
   C.assign(3.0, 1, 2);

   C.assign(2.0, 2, 0);
   C.assign(5.0, 2, 1);
   C.assign(8.0, 2, 2);

   DecompositionPLU mats = A.decomposeToPLU();

   MatrixSquare PA((mats.matP()) * A);
   MatrixSquare LU((mats.matL()) * (mats.matU()));

   DecompositionPLU mats1 = B.decomposeToPLU();

   MatrixSquare PB((mats1.matP()) * B);
   MatrixSquare LU1((mats1.matL()) * (mats1.matU()));

   DecompositionPLU mats2{A, true};

   MatrixSquare LU2((mats2.matL()) * (mats2.matU()));

   DecompositionPLU mats3 = C.decomposeToPLU();
   mats3.setStrictLUMode();

   EXPECT_TRUE(PA == LU);
   EXPECT_TRUE(PB == LU1);
   EXPECT_TRUE(A == LU2);
   EXPECT_FALSE(mats3.isStrictLUDecomposable());
}

TEST(TestMatrixSquare, TestInverse) {

   MatrixSquare A(4);
   A.assign(1.0, 0, 0);
   A.assign(2.0, 0, 1);
   A.assign(3.0, 0, 2);
   A.assign(4.0, 0, 3);
   A.assign(1.0, 1, 0);
   A.assign(3.0, 1, 1);
   A.assign(2.0, 1, 2);
   A.assign(5.0, 1, 3);
   A.assign(2.0, 2, 0);
   A.assign(1.0, 2, 1);
   A.assign(6.0, 2, 2);
   A.assign(3.0, 2, 3);
   A.assign(3.0, 3, 0);
   A.assign(2.0, 3, 1);
   A.assign(1.0, 3, 2);
   A.assign(1.0, 3, 3);

   MatrixSquare invA(4);
   invA.assign(12.0, 0, 0);
   invA.assign(-23.0 / 3.0, 0, 1);
   invA.assign(-11.0 / 3.0, 0, 2);
   invA.assign(4.0 / 3.0, 0, 3);
   invA.assign(-21.0, 1, 0);
   invA.assign(40.0 / 3.0, 1, 1);
   invA.assign(19.0 / 3.0, 1, 2);
   invA.assign(-5.0 / 3.0, 1, 3);
   invA.assign(-7.0, 2, 0);
   invA.assign(13.0 / 3.0, 2, 1);
   invA.assign(7.0 / 3.0, 2, 2);
   invA.assign(-2.0 / 3.0, 2, 3);
   invA.assign(13.0, 3, 0);
   invA.assign(-8.0, 3, 1);
   invA.assign(-4.0, 3, 2);
   invA.assign(1.0, 3, 3);

   EXPECT_TRUE(A.decomposeToPLU().inverse() == invA);
}

TEST(TestMatrixSquare, TestPlus) {
   MatrixSquare z(4);
   z.assign(1.0, 0, 0);
   z.assign(2.0, 0, 1);
   z.assign(3.0, 0, 2);
   z.assign(4.0, 0, 3);
   z.assign(5.0, 1, 0);
   z.assign(6.0, 1, 1);
   z.assign(7.0, 1, 2);
   z.assign(8.0, 1, 3);
   z.assign(9.0, 2, 0);
   z.assign(10.0, 2, 1);
   z.assign(11.0, 2, 2);
   z.assign(12.0, 2, 3);
   z.assign(13.0, 3, 0);
   z.assign(14.0, 3, 1);
   z.assign(15.0, 3, 2);
   z.assign(16.0, 3, 3);

   MatrixSquare resp(4);
   resp.assign(2.0, 0, 0);
   resp.assign(4.0, 0, 1);
   resp.assign(6.0, 0, 2);
   resp.assign(8.0, 0, 3);
   resp.assign(10.0, 1, 0);
   resp.assign(12.0, 1, 1);
   resp.assign(14.0, 1, 2);
   resp.assign(16.0, 1, 3);
   resp.assign(18.0, 2, 0);
   resp.assign(20.0, 2, 1);
   resp.assign(22.0, 2, 2);
   resp.assign(24.0, 2, 3);
   resp.assign(26.0, 3, 0);
   resp.assign(28.0, 3, 1);
   resp.assign(30.0, 3, 2);
   resp.assign(32.0, 3, 3);

   MatrixSquare x1(4);
   x1 = z + z;
   MatrixSquare x2(z + z);
   z.addBy(z);

   EXPECT_TRUE(resp == x1);
   EXPECT_TRUE(resp == x2);
   EXPECT_TRUE(resp == z);
}

TEST(TestMatrixSquare, TestMinus) {
   MatrixSquare z(4);
   z.assign(1.0, 0, 0);
   z.assign(2.0, 0, 1);
   z.assign(3.0, 0, 2);
   z.assign(4.0, 0, 3);
   z.assign(5.0, 1, 0);
   z.assign(6.0, 1, 1);
   z.assign(7.0, 1, 2);
   z.assign(8.0, 1, 3);
   z.assign(9.0, 2, 0);
   z.assign(10.0, 2, 1);
   z.assign(11.0, 2, 2);
   z.assign(12.0, 2, 3);
   z.assign(13.0, 3, 0);
   z.assign(14.0, 3, 1);
   z.assign(15.0, 3, 2);
   z.assign(16.0, 3, 3);

   MatrixSquare resp(4);

   MatrixSquare x1(4);
   x1 = z - z;
   MatrixSquare x2(z - z);
   z.subtractBy(z);

   EXPECT_TRUE(resp == x1);
   EXPECT_TRUE(resp == x2);
   EXPECT_TRUE(resp == z);
}

TEST(TestMatrixSquare, TestTimes) {
   MatrixSquare z(3);
   z.assign(1.0, 0, 0);
   z.assign(2.0, 0, 1);
   z.assign(3.0, 0, 2);
   z.assign(4.0, 1, 0);
   z.assign(5.0, 1, 1);
   z.assign(6.0, 1, 2);
   z.assign(7.0, 2, 0);
   z.assign(8.0, 2, 1);
   z.assign(9.0, 2, 2);

   MatrixSquare v(3);
   v.assign(-1.0, 0, 0);
   v.assign(-2.0, 0, 1);
   v.assign(-3.0, 0, 2);
   v.assign(-4.0, 1, 0);
   v.assign(-5.0, 1, 1);
   v.assign(-6.0, 1, 2);
   v.assign(-7.0, 2, 0);
   v.assign(-8.0, 2, 1);
   v.assign(-9.0, 2, 2);

   MatrixSquare resp(3);
   resp.assign(-30.0, 0, 0);
   resp.assign(-36.0, 0, 1);
   resp.assign(-42.0, 0, 2);
   resp.assign(-66.0, 1, 0);
   resp.assign(-81.0, 1, 1);
   resp.assign(-96.0, 1, 2);
   resp.assign(-102.0, 2, 0);
   resp.assign(-126.0, 2, 1);
   resp.assign(-150.0, 2, 2);

   MatrixSquare resp1(3);
   resp1.assign(2.0, 0, 0);
   resp1.assign(4.0, 0, 1);
   resp1.assign(6.0, 0, 2);
   resp1.assign(8.0, 1, 0);
   resp1.assign(10.0, 1, 1);
   resp1.assign(12.0, 1, 2);
   resp1.assign(14.0, 2, 0);
   resp1.assign(16.0, 2, 1);
   resp1.assign(18.0, 2, 2);

   EXPECT_TRUE(resp == z * v);
   EXPECT_TRUE(resp1 == z * 2.0);
}

TEST(TestMatrixSquare, TestMisc) {
   MatrixSquare A(4);

   A.assign(1.0, 0, 0);
   A.assign(2.0, 0, 1);
   A.assign(3.0, 0, 2);
   A.assign(4.0, 0, 3);

   A.assign(1.0, 1, 0);
   A.assign(3.0, 1, 1);
   A.assign(2.0, 1, 2);
   A.assign(5.0, 1, 3);

   A.assign(2.0, 2, 0);
   A.assign(1.0, 2, 1);
   A.assign(6.0, 2, 2);
   A.assign(3.0, 2, 3);

   A.assign(3.0, 3, 0);
   A.assign(2.0, 3, 1);
   A.assign(1.0, 3, 2);
   A.assign(1.0, 3, 3);

   MatrixLowerTriangular ALower(4);
   MatrixUpperTriangular AUpper(4);

   ALower.assign(1.0, 0, 0);

   ALower.assign(1.0, 1, 0);
   ALower.assign(3.0, 1, 1);

   ALower.assign(2.0, 2, 0);
   ALower.assign(1.0, 2, 1);
   ALower.assign(6.0, 2, 2);

   ALower.assign(3.0, 3, 0);
   ALower.assign(2.0, 3, 1);
   ALower.assign(1.0, 3, 2);
   ALower.assign(1.0, 3, 3);

   AUpper.assign(1.0, 0, 0);
   AUpper.assign(2.0, 0, 1);
   AUpper.assign(3.0, 0, 2);
   AUpper.assign(4.0, 0, 3);

   AUpper.assign(3.0, 1, 1);
   AUpper.assign(2.0, 1, 2);
   AUpper.assign(5.0, 1, 3);

   AUpper.assign(6.0, 2, 2);
   AUpper.assign(3.0, 2, 3);

   AUpper.assign(1.0, 3, 3);

   MatrixSquare B;

   B = A;

   MatrixSquare T(B);

   MatrixSquare C;
   C = (std::move(T));

   EXPECT_TRUE(A == B);
   EXPECT_TRUE(A == C);
}

TEST(TestMatrixSquare, TestPositiveDefinite) {
   MatrixSquare z(4);
   z.assign(1.0, 0, 0);
   z.assign(-1.0, 0, 1);
   z.assign(2.0, 0, 2);
   z.assign(0.0, 0, 3);
   z.assign(-1.0, 1, 0);
   z.assign(4.0, 1, 1);
   z.assign(-1.0, 1, 2);
   z.assign(1.0, 1, 3);
   z.assign(2.0, 2, 0);
   z.assign(-1.0, 2, 1);
   z.assign(6.0, 2, 2);
   z.assign(-2.0, 2, 3);
   z.assign(0.0, 3, 0);
   z.assign(1.0, 3, 1);
   z.assign(-2.0, 3, 2);
   z.assign(4.0, 3, 3);

   DecompositionPLU dpu = z.decomposeToPLU();
   dpu.setStrictLUMode();

   EXPECT_TRUE(dpu.isPositiveDefinite());
}

TEST(TestMatrixSquare, TestSymmetricAntiSym) {
   MatrixSquare A(4);
   A.assign(1.0, 0, 0);
   A.assign(2.0, 0, 1);
   A.assign(3.0, 0, 2);
   A.assign(4.0, 0, 3);
   A.assign(1.0, 1, 0);
   A.assign(3.0, 1, 1);
   A.assign(2.0, 1, 2);
   A.assign(5.0, 1, 3);
   A.assign(2.0, 2, 0);
   A.assign(1.0, 2, 1);
   A.assign(6.0, 2, 2);
   A.assign(3.0, 2, 3);
   A.assign(3.0, 3, 0);
   A.assign(2.0, 3, 1);
   A.assign(1.0, 3, 2);
   A.assign(1.0, 3, 3);
   DecompositionSAS matSas = A.decomposeToSAS();
   EXPECT_TRUE(A == (matSas.matS() + matSas.matAS()));
}

TEST(TestMatrixSquare, TestIsOrthogonal) {
   MatrixSquare A(4);
   A.assign(1.0, 0, 0);
   A.assign(1.0, 0, 1);
   A.assign(1.0, 0, 2);
   A.assign(1.0, 0, 3);
   A.assign(1.0, 1, 0);
   A.assign(-1.0, 1, 1);
   A.assign(1.0, 1, 2);
   A.assign(-1.0, 1, 3);
   A.assign(1.0, 2, 0);
   A.assign(1.0, 2, 1);
   A.assign(-1.0, 2, 2);
   A.assign(-1.0, 2, 3);
   A.assign(1.0, 3, 0);
   A.assign(-1.0, 3, 1);
   A.assign(-1.0, 3, 2);
   A.assign(1.0, 3, 3);
   MatrixSquare B(A * 0.5);

   EXPECT_TRUE(B.decomposeToPLU().isOrthogonal());
}

TEST(TestMatrixSquare, TestLinearSolve) {
   MatrixSquare A(4);

   A.assign(1.0, 0, 0);
   A.assign(2.0, 0, 1);
   A.assign(3.0, 0, 2);
   A.assign(4.0, 0, 3);

   A.assign(1.0, 1, 0);
   A.assign(3.0, 1, 1);
   A.assign(2.0, 1, 2);
   A.assign(5.0, 1, 3);

   A.assign(2.0, 2, 0);
   A.assign(1.0, 2, 1);
   A.assign(6.0, 2, 2);
   A.assign(3.0, 2, 3);

   A.assign(3.0, 3, 0);
   A.assign(2.0, 3, 1);
   A.assign(1.0, 3, 2);
   A.assign(1.0, 3, 3);

   Vector b(4);

   b.assign(1.0, 0);
   b.assign(2.0, 1);
   b.assign(3.0, 2);
   b.assign(1.0, 3);

   const Vector x(A.decomposeToPLU().linearSolve(b));

   Vector resp(4);

   resp.assign(-13.0, 0);
   resp.assign(23.0, 1);
   resp.assign(8.0, 2);
   resp.assign(-14.0, 3);

   EXPECT_TRUE(x == resp);
}

TEST(TestMatrixSquare, TestMultiplySubSuperMatrices) {
   MatrixSquare A(5);

   A.assign(1.0, 0, 0);
   A.assign(2.0, 0, 1);
   A.assign(3.0, 0, 2);
   A.assign(4.0, 0, 3);
   A.assign(5.0, 0, 4);

   A.assign(2.0, 1, 0);
   A.assign(1.0, 1, 1);
   A.assign(-1.0, 1, 2);
   A.assign(3.0, 1, 3);
   A.assign(4.0, 1, 4);

   A.assign(1.0, 2, 0);
   A.assign(1.0, 2, 1);
   A.assign(2.0, 2, 2);
   A.assign(3.0, 2, 3);
   A.assign(3.0, 2, 4);

   A.assign(4.0, 3, 0);
   A.assign(5.0, 3, 1);
   A.assign(6.0, 3, 2);
   A.assign(7.0, 3, 3);
   A.assign(2.0, 3, 4);

   A.assign(7.0, 4, 0);
   A.assign(8.0, 4, 1);
   A.assign(9.0, 4, 2);
   A.assign(3.0, 4, 3);
   A.assign(1.0, 4, 4);

   MatrixSquare B(2);

   B.assign(2.0, 0, 0);
   B.assign(3.0, 0, 1);
   B.assign(-1.0, 1, 0);
   B.assign(4.0, 1, 1);

   MatrixSquare resp(5);

   resp.assign(1.0, 0, 0);
   resp.assign(2.0, 0, 1);
   resp.assign(3.0, 0, 2);
   resp.assign(4.0, 0, 3);
   resp.assign(5.0, 0, 4);

   resp.assign(2.0, 1, 0);
   resp.assign(1.0, 1, 1);
   resp.assign(-1.0, 1, 2);
   resp.assign(3.0, 1, 3);
   resp.assign(4.0, 1, 4);

   resp.assign(1.0, 2, 0);
   resp.assign(1.0, 2, 1);
   resp.assign(2.0, 2, 2);
   resp.assign(3.0, 2, 3);
   resp.assign(3.0, 2, 4);

   resp.assign(29.0, 3, 0);
   resp.assign(34.0, 3, 1);
   resp.assign(39.0, 3, 2);
   resp.assign(23.0, 3, 3);
   resp.assign(7.0, 3, 4);

   resp.assign(24.0, 4, 0);
   resp.assign(27.0, 4, 1);
   resp.assign(30.0, 4, 2);
   resp.assign(5.0, 4, 3);
   resp.assign(2.0, 4, 4);

   MatrixSquare resp2(5);

   resp2.assign(8.0, 0, 0);
   resp2.assign(7.0, 0, 1);
   resp2.assign(3.0, 0, 2);
   resp2.assign(17.0, 0, 3);
   resp2.assign(22.0, 0, 4);

   resp2.assign(7.0, 1, 0);
   resp2.assign(2.0, 1, 1);
   resp2.assign(-7.0, 1, 2);
   resp2.assign(8.0, 1, 3);
   resp2.assign(11.0, 1, 4);

   resp2.assign(1.0, 2, 0);
   resp2.assign(1.0, 2, 1);
   resp2.assign(2.0, 2, 2);
   resp2.assign(3.0, 2, 3);
   resp2.assign(3.0, 2, 4);

   resp2.assign(4.0, 3, 0);
   resp2.assign(5.0, 3, 1);
   resp2.assign(6.0, 3, 2);
   resp2.assign(7.0, 3, 3);
   resp2.assign(2.0, 3, 4);

   resp2.assign(7.0, 4, 0);
   resp2.assign(8.0, 4, 1);
   resp2.assign(9.0, 4, 2);
   resp2.assign(3.0, 4, 3);
   resp2.assign(1.0, 4, 4);

   EXPECT_TRUE(B.multiplyByBiggerMatrix(A, SubMatrixPos::lower) == resp);
   EXPECT_TRUE(B.multiplyByBiggerMatrix(A, SubMatrixPos::upper) == resp2);
}

TEST(TestMatrixSquare, TestDecompQR) {
   MatrixSquare A(3);

   A.assign(12.0, 0, 0);
   A.assign(-51.0, 0, 1);
   A.assign(4.0, 0, 2);

   A.assign(6.0, 1, 0);
   A.assign(167.0, 1, 1);
   A.assign(-68.0, 1, 2);

   A.assign(-4.0, 2, 0);
   A.assign(24.0, 2, 1);
   A.assign(-41.0, 2, 2);

   DecompositionPQR qr{A.decomposeToPQR()};

   MatrixSquare resp{qr.matQ() * qr.matR()};

   MatrixSquare invA{qr.inverse()};

   MatrixSquare identity(A.size());
   identity.fillDiagonalWith(utils::ONE);

   MatrixSquare B(3);

   B.assign(12.0, 0, 0);
   B.assign(-51.0, 0, 1);
   B.assign(4.0, 0, 2);

   B.assign(24.0, 1, 0);
   B.assign(-102.0, 1, 1);
   B.assign(8.0, 1, 2);

   B.assign(-4.0, 2, 0);
   B.assign(24.0, 2, 1);
   B.assign(-41.0, 2, 2);

   EXPECT_TRUE(resp == A * qr.matP());
   EXPECT_TRUE(pmat::utils::areEqual(B.decomposeToPQR().rank(), 2.0));
   EXPECT_TRUE(identity == A * invA);
}

TEST(TestMatrixSquare, TestInserts) {
   double data[] = {1., 2., 3., 4., 5., 6., 7., 8., 9., 10., 11., 12., 13., 14., 15., 16.};
   double dataresp[] = {1.,  2.,  3.,  99., 4.,  5.,  6.,  7.,  99., 8.,  9.,  10., 11.,
                        99., 12., 99., 99., 99., 99., 99., 13., 14., 15., 99., 16.};
   pmat::MatrixSquare m{data, 4};
   pmat::MatrixSquare res{dataresp, 5};

   m.insertRowColumn(2, 99.);

   EXPECT_TRUE(m == res);
}