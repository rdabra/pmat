#include "../src/MatrixLowerTriangular.h" // In order to define the class completely
#include "../src/MatrixSkewSymmetric.h"   // In order to define the class completely
#include "../src/MatrixSquare.h"
#include "../src/MatrixSymmetric.h"       // In order to define the class completely
#include "../src/MatrixUpperTriangular.h" // In order to define the class completely
#include "../src/utils.h"
#include "gtest/gtest.h"

using namespace pmat;

TEST(TestMatrixSquare, TestTrace) {
   MatrixSquare A(5);

   A.setValue(4.0, 0, 0);
   A.setValue(3.0, 0, 1);
   A.setValue(2.0, 0, 2);
   A.setValue(1.0, 0, 3);
   A.setValue(6.0, 0, 4);

   A.setValue(2.0, 1, 0);
   A.setValue(3.0, 1, 1);
   A.setValue(1.0, 1, 2);
   A.setValue(2.0, 1, 3);
   A.setValue(9.0, 1, 4);

   A.setValue(1.0, 2, 0);
   A.setValue(3.0, 2, 1);
   A.setValue(2.0, 2, 2);
   A.setValue(5.0, 2, 3);
   A.setValue(1.0, 2, 4);

   A.setValue(2.0, 3, 0);
   A.setValue(7.0, 3, 1);
   A.setValue(6.0, 3, 2);
   A.setValue(4.0, 3, 3);
   A.setValue(3.0, 3, 4);

   A.setValue(1.0, 4, 0);
   A.setValue(7.0, 4, 1);
   A.setValue(6.0, 4, 2);
   A.setValue(5.0, 4, 3);
   A.setValue(3.0, 4, 4);

   EXPECT_TRUE(A.trace() == 16.0);
}

// TEST(TestMatrixSquare, TestDeterminant) {
//    MatrixSquare A(4);

//    A.setValue(1.0, 0, 0);
//    A.setValue(2.0, 0, 1);
//    A.setValue(3.0, 0, 2);
//    A.setValue(4.0, 0, 3);

//    A.setValue(1.0, 1, 0);
//    A.setValue(3.0, 1, 1);
//    A.setValue(2.0, 1, 2);
//    A.setValue(5.0, 1, 3);

//    A.setValue(2.0, 2, 0);
//    A.setValue(1.0, 2, 1);
//    A.setValue(6.0, 2, 2);
//    A.setValue(3.0, 2, 3);

//    A.setValue(3.0, 3, 0);
//    A.setValue(2.0, 3, 1);
//    A.setValue(1.0, 3, 2);
//    A.setValue(1.0, 3, 3);

//    MatrixSquare B(3);

//    B.setValue(1.0, 0, 0);
//    B.setValue(1.0, 0, 1);
//    B.setValue(1.0, 0, 2);

//    B.setValue(1.0, 1, 0);
//    B.setValue(1.0, 1, 1);
//    B.setValue(3.0, 1, 2);

//    B.setValue(2.0, 2, 0);
//    B.setValue(5.0, 2, 1);
//    B.setValue(8.0, 2, 2);

//    MatrixSquare C(3);

//    EXPECT_TRUE(utils::areEqual(A.determinant(), -3.0));
//    EXPECT_TRUE(utils::areEqual(B.determinant(), -6.0));
//    EXPECT_TRUE(A.isInvertible());
//    EXPECT_FALSE(C.isInvertible());
// }

// TEST(TestMatrixSquare, TestDecompPLU) {
//    MatrixSquare A(4);

//    A.setValue(1.0, 0, 0);
//    A.setValue(2.0, 0, 1);
//    A.setValue(3.0, 0, 2);
//    A.setValue(4.0, 0, 3);

//    A.setValue(1.0, 1, 0);
//    A.setValue(3.0, 1, 1);
//    A.setValue(2.0, 1, 2);
//    A.setValue(5.0, 1, 3);

//    A.setValue(2.0, 2, 0);
//    A.setValue(1.0, 2, 1);
//    A.setValue(6.0, 2, 2);
//    A.setValue(3.0, 2, 3);

//    A.setValue(3.0, 3, 0);
//    A.setValue(2.0, 3, 1);
//    A.setValue(1.0, 3, 2);
//    A.setValue(1.0, 3, 3);

//    MatrixSquare B(3);

//    B.setValue(1.0, 0, 0);
//    B.setValue(2.0, 0, 1);
//    B.setValue(3.0, 0, 2);

//    B.setValue(2.0, 1, 0);
//    B.setValue(4.0, 1, 1);
//    B.setValue(7.0, 1, 2);

//    B.setValue(3.0, 2, 0);
//    B.setValue(5.0, 2, 1);
//    B.setValue(3.0, 2, 2);

//    MatrixSquare C(3);

//    C.setValue(1.0, 0, 0);
//    C.setValue(1.0, 0, 1);
//    C.setValue(1.0, 0, 2);

//    C.setValue(1.0, 1, 0);
//    C.setValue(1.0, 1, 1);
//    C.setValue(3.0, 1, 2);

//    C.setValue(2.0, 2, 0);
//    C.setValue(5.0, 2, 1);
//    C.setValue(8.0, 2, 2);

//    D_PLU mats = A.getPLU();

//    MatrixSquare PA((*mats.matP) * A);
//    MatrixSquare LU((*mats.matL) * (*mats.matU));

//    D_PLU mats1 = B.getPLU();

//    MatrixSquare PB((*mats1.matP) * B);
//    MatrixSquare LU1((*mats1.matL) * (*mats1.matU));

//    D_PLU mats2 = A.getStrictLU();

//    MatrixSquare LU2((*mats2.matL) * (*mats2.matU));

//    EXPECT_TRUE(PA == LU);
//    EXPECT_TRUE(PB == LU1);
//    EXPECT_TRUE(A == LU2);
//    EXPECT_FALSE(C.isStrictLUDecomposable());
// }

// TEST(TestMatrixSquare, TestInverse) {
//    MatrixSquare A(4);

//    A.setValue(1.0, 0, 0);
//    A.setValue(2.0, 0, 1);
//    A.setValue(3.0, 0, 2);
//    A.setValue(4.0, 0, 3);

//    A.setValue(1.0, 1, 0);
//    A.setValue(3.0, 1, 1);
//    A.setValue(2.0, 1, 2);
//    A.setValue(5.0, 1, 3);

//    A.setValue(2.0, 2, 0);
//    A.setValue(1.0, 2, 1);
//    A.setValue(6.0, 2, 2);
//    A.setValue(3.0, 2, 3);

//    A.setValue(3.0, 3, 0);
//    A.setValue(2.0, 3, 1);
//    A.setValue(1.0, 3, 2);
//    A.setValue(1.0, 3, 3);

//    MatrixSquare invA(4);

//    invA.setValue(12.0, 0, 0);
//    invA.setValue(-23.0 / 3.0, 0, 1);
//    invA.setValue(-11.0 / 3.0, 0, 2);
//    invA.setValue(4.0 / 3.0, 0, 3);

//    invA.setValue(-21.0, 1, 0);
//    invA.setValue(40.0 / 3.0, 1, 1);
//    invA.setValue(19.0 / 3.0, 1, 2);
//    invA.setValue(-5.0 / 3.0, 1, 3);

//    invA.setValue(-7.0, 2, 0);
//    invA.setValue(13.0 / 3.0, 2, 1);
//    invA.setValue(7.0 / 3.0, 2, 2);
//    invA.setValue(-2.0 / 3.0, 2, 3);

//    invA.setValue(13.0, 3, 0);
//    invA.setValue(-8.0, 3, 1);
//    invA.setValue(-4.0, 3, 2);
//    invA.setValue(1.0, 3, 3);

//    EXPECT_TRUE(A.getInverse() == invA);
// }

TEST(TestMatrixSquare, TestPlus) {
   MatrixSquare z(4);
   z.setValue(1.0, 0, 0);
   z.setValue(2.0, 0, 1);
   z.setValue(3.0, 0, 2);
   z.setValue(4.0, 0, 3);
   z.setValue(5.0, 1, 0);
   z.setValue(6.0, 1, 1);
   z.setValue(7.0, 1, 2);
   z.setValue(8.0, 1, 3);
   z.setValue(9.0, 2, 0);
   z.setValue(10.0, 2, 1);
   z.setValue(11.0, 2, 2);
   z.setValue(12.0, 2, 3);
   z.setValue(13.0, 3, 0);
   z.setValue(14.0, 3, 1);
   z.setValue(15.0, 3, 2);
   z.setValue(16.0, 3, 3);

   MatrixSquare resp(4);
   resp.setValue(2.0, 0, 0);
   resp.setValue(4.0, 0, 1);
   resp.setValue(6.0, 0, 2);
   resp.setValue(8.0, 0, 3);
   resp.setValue(10.0, 1, 0);
   resp.setValue(12.0, 1, 1);
   resp.setValue(14.0, 1, 2);
   resp.setValue(16.0, 1, 3);
   resp.setValue(18.0, 2, 0);
   resp.setValue(20.0, 2, 1);
   resp.setValue(22.0, 2, 2);
   resp.setValue(24.0, 2, 3);
   resp.setValue(26.0, 3, 0);
   resp.setValue(28.0, 3, 1);
   resp.setValue(30.0, 3, 2);
   resp.setValue(32.0, 3, 3);

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
   z.setValue(1.0, 0, 0);
   z.setValue(2.0, 0, 1);
   z.setValue(3.0, 0, 2);
   z.setValue(4.0, 0, 3);
   z.setValue(5.0, 1, 0);
   z.setValue(6.0, 1, 1);
   z.setValue(7.0, 1, 2);
   z.setValue(8.0, 1, 3);
   z.setValue(9.0, 2, 0);
   z.setValue(10.0, 2, 1);
   z.setValue(11.0, 2, 2);
   z.setValue(12.0, 2, 3);
   z.setValue(13.0, 3, 0);
   z.setValue(14.0, 3, 1);
   z.setValue(15.0, 3, 2);
   z.setValue(16.0, 3, 3);

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
   z.setValue(1.0, 0, 0);
   z.setValue(2.0, 0, 1);
   z.setValue(3.0, 0, 2);
   z.setValue(4.0, 1, 0);
   z.setValue(5.0, 1, 1);
   z.setValue(6.0, 1, 2);
   z.setValue(7.0, 2, 0);
   z.setValue(8.0, 2, 1);
   z.setValue(9.0, 2, 2);

   MatrixSquare v(3);
   v.setValue(-1.0, 0, 0);
   v.setValue(-2.0, 0, 1);
   v.setValue(-3.0, 0, 2);
   v.setValue(-4.0, 1, 0);
   v.setValue(-5.0, 1, 1);
   v.setValue(-6.0, 1, 2);
   v.setValue(-7.0, 2, 0);
   v.setValue(-8.0, 2, 1);
   v.setValue(-9.0, 2, 2);

   MatrixSquare resp(3);
   resp.setValue(-30.0, 0, 0);
   resp.setValue(-36.0, 0, 1);
   resp.setValue(-42.0, 0, 2);
   resp.setValue(-66.0, 1, 0);
   resp.setValue(-81.0, 1, 1);
   resp.setValue(-96.0, 1, 2);
   resp.setValue(-102.0, 2, 0);
   resp.setValue(-126.0, 2, 1);
   resp.setValue(-150.0, 2, 2);

   MatrixSquare resp1(3);
   resp1.setValue(2.0, 0, 0);
   resp1.setValue(4.0, 0, 1);
   resp1.setValue(6.0, 0, 2);
   resp1.setValue(8.0, 1, 0);
   resp1.setValue(10.0, 1, 1);
   resp1.setValue(12.0, 1, 2);
   resp1.setValue(14.0, 2, 0);
   resp1.setValue(16.0, 2, 1);
   resp1.setValue(18.0, 2, 2);

   EXPECT_TRUE(resp == z * v);
   EXPECT_TRUE(resp1 == z * 2.0);
}

TEST(TestMatrixSquare, TestMisc) {
   MatrixSquare A(4);

   A.setValue(1.0, 0, 0);
   A.setValue(2.0, 0, 1);
   A.setValue(3.0, 0, 2);
   A.setValue(4.0, 0, 3);

   A.setValue(1.0, 1, 0);
   A.setValue(3.0, 1, 1);
   A.setValue(2.0, 1, 2);
   A.setValue(5.0, 1, 3);

   A.setValue(2.0, 2, 0);
   A.setValue(1.0, 2, 1);
   A.setValue(6.0, 2, 2);
   A.setValue(3.0, 2, 3);

   A.setValue(3.0, 3, 0);
   A.setValue(2.0, 3, 1);
   A.setValue(1.0, 3, 2);
   A.setValue(1.0, 3, 3);

   MatrixLowerTriangular ALower(4);
   MatrixUpperTriangular AUpper(4);

   ALower.setValue(1.0, 0, 0);

   ALower.setValue(1.0, 1, 0);
   ALower.setValue(3.0, 1, 1);

   ALower.setValue(2.0, 2, 0);
   ALower.setValue(1.0, 2, 1);
   ALower.setValue(6.0, 2, 2);

   ALower.setValue(3.0, 3, 0);
   ALower.setValue(2.0, 3, 1);
   ALower.setValue(1.0, 3, 2);
   ALower.setValue(1.0, 3, 3);

   AUpper.setValue(1.0, 0, 0);
   AUpper.setValue(2.0, 0, 1);
   AUpper.setValue(3.0, 0, 2);
   AUpper.setValue(4.0, 0, 3);

   AUpper.setValue(3.0, 1, 1);
   AUpper.setValue(2.0, 1, 2);
   AUpper.setValue(5.0, 1, 3);

   AUpper.setValue(6.0, 2, 2);
   AUpper.setValue(3.0, 2, 3);

   AUpper.setValue(1.0, 3, 3);

   MatrixSquare B;

   B = A;

   MatrixSquare T(B);

   MatrixSquare C;
   C = (std::move(T));

   MatrixLowerTriangular Al{A};
   MatrixUpperTriangular Au{A};

   EXPECT_TRUE(A == B);
   EXPECT_TRUE(A == C);
   EXPECT_TRUE(Al == ALower);
   EXPECT_TRUE(Au == AUpper);
}

// TEST(TestMatrixSquare, TestPositiveDefinite) {
//    MatrixSquare z(4);
//    z.setValue(1.0, 0, 0);
//    z.setValue(-1.0, 0, 1);
//    z.setValue(2.0, 0, 2);
//    z.setValue(0.0, 0, 3);
//    z.setValue(-1.0, 1, 0);
//    z.setValue(4.0, 1, 1);
//    z.setValue(-1.0, 1, 2);
//    z.setValue(1.0, 1, 3);
//    z.setValue(2.0, 2, 0);
//    z.setValue(-1.0, 2, 1);
//    z.setValue(6.0, 2, 2);
//    z.setValue(-2.0, 2, 3);
//    z.setValue(0.0, 3, 0);
//    z.setValue(1.0, 3, 1);
//    z.setValue(-2.0, 3, 2);
//    z.setValue(4.0, 3, 3);

//    EXPECT_TRUE(z.isPositiveDefinite());
// }

// TEST(TestMatrixSquare, TestSymmetricAntiSym) {
//    MatrixSquare A(4);

//    A.setValue(1.0, 0, 0);
//    A.setValue(2.0, 0, 1);
//    A.setValue(3.0, 0, 2);
//    A.setValue(4.0, 0, 3);

//    A.setValue(1.0, 1, 0);
//    A.setValue(3.0, 1, 1);
//    A.setValue(2.0, 1, 2);
//    A.setValue(5.0, 1, 3);

//    A.setValue(2.0, 2, 0);
//    A.setValue(1.0, 2, 1);
//    A.setValue(6.0, 2, 2);
//    A.setValue(3.0, 2, 3);

//    A.setValue(3.0, 3, 0);
//    A.setValue(2.0, 3, 1);
//    A.setValue(1.0, 3, 2);
//    A.setValue(1.0, 3, 3);

//    D_SAS matSas = A.getSAS();

//    EXPECT_TRUE(A == (*matSas.matS) + (*matSas.matAS));
// }

// TEST(TestMatrixSquare, TestIsOrthogonal) {
//    MatrixSquare A(4);

//    A.setValue(1.0, 0, 0);
//    A.setValue(1.0, 0, 1);
//    A.setValue(1.0, 0, 2);
//    A.setValue(1.0, 0, 3);

//    A.setValue(1.0, 1, 0);
//    A.setValue(-1.0, 1, 1);
//    A.setValue(1.0, 1, 2);
//    A.setValue(-1.0, 1, 3);

//    A.setValue(1.0, 2, 0);
//    A.setValue(1.0, 2, 1);
//    A.setValue(-1.0, 2, 2);
//    A.setValue(-1.0, 2, 3);

//    A.setValue(1.0, 3, 0);
//    A.setValue(-1.0, 3, 1);
//    A.setValue(-1.0, 3, 2);
//    A.setValue(1.0, 3, 3);

//    MatrixSquare B(A * 0.5);

//    EXPECT_TRUE(B.isOrthogonal());
// }

// TEST(TestMatrixSquare, TestLinearSolve) {
//    MatrixSquare A(4);

//    A.setValue(1.0, 0, 0);
//    A.setValue(2.0, 0, 1);
//    A.setValue(3.0, 0, 2);
//    A.setValue(4.0, 0, 3);

//    A.setValue(1.0, 1, 0);
//    A.setValue(3.0, 1, 1);
//    A.setValue(2.0, 1, 2);
//    A.setValue(5.0, 1, 3);

//    A.setValue(2.0, 2, 0);
//    A.setValue(1.0, 2, 1);
//    A.setValue(6.0, 2, 2);
//    A.setValue(3.0, 2, 3);

//    A.setValue(3.0, 3, 0);
//    A.setValue(2.0, 3, 1);
//    A.setValue(1.0, 3, 2);
//    A.setValue(1.0, 3, 3);

//    Vector b(4);

//    b.setValue(1.0, 0);
//    b.setValue(2.0, 1);
//    b.setValue(3.0, 2);
//    b.setValue(1.0, 3);

//    const Vector x(A.linearSolve(b));

//    Vector resp(4);

//    resp.setValue(-13.0, 0);
//    resp.setValue(23.0, 1);
//    resp.setValue(8.0, 2);
//    resp.setValue(-14.0, 3);

//    EXPECT_TRUE(x == resp);
// }

TEST(TestMatrixSquare, TestMultiplySubSuperMatrices) {
   MatrixSquare A(5);

   A.setValue(1.0, 0, 0);
   A.setValue(2.0, 0, 1);
   A.setValue(3.0, 0, 2);
   A.setValue(4.0, 0, 3);
   A.setValue(5.0, 0, 4);

   A.setValue(2.0, 1, 0);
   A.setValue(1.0, 1, 1);
   A.setValue(-1.0, 1, 2);
   A.setValue(3.0, 1, 3);
   A.setValue(4.0, 1, 4);

   A.setValue(1.0, 2, 0);
   A.setValue(1.0, 2, 1);
   A.setValue(2.0, 2, 2);
   A.setValue(3.0, 2, 3);
   A.setValue(3.0, 2, 4);

   A.setValue(4.0, 3, 0);
   A.setValue(5.0, 3, 1);
   A.setValue(6.0, 3, 2);
   A.setValue(7.0, 3, 3);
   A.setValue(2.0, 3, 4);

   A.setValue(7.0, 4, 0);
   A.setValue(8.0, 4, 1);
   A.setValue(9.0, 4, 2);
   A.setValue(3.0, 4, 3);
   A.setValue(1.0, 4, 4);

   MatrixSquare B(2);

   B.setValue(2.0, 0, 0);
   B.setValue(3.0, 0, 1);
   B.setValue(-1.0, 1, 0);
   B.setValue(4.0, 1, 1);

   MatrixSquare resp(5);

   resp.setValue(1.0, 0, 0);
   resp.setValue(2.0, 0, 1);
   resp.setValue(3.0, 0, 2);
   resp.setValue(4.0, 0, 3);
   resp.setValue(5.0, 0, 4);

   resp.setValue(2.0, 1, 0);
   resp.setValue(1.0, 1, 1);
   resp.setValue(-1.0, 1, 2);
   resp.setValue(3.0, 1, 3);
   resp.setValue(4.0, 1, 4);

   resp.setValue(1.0, 2, 0);
   resp.setValue(1.0, 2, 1);
   resp.setValue(2.0, 2, 2);
   resp.setValue(3.0, 2, 3);
   resp.setValue(3.0, 2, 4);

   resp.setValue(29.0, 3, 0);
   resp.setValue(34.0, 3, 1);
   resp.setValue(39.0, 3, 2);
   resp.setValue(23.0, 3, 3);
   resp.setValue(7.0, 3, 4);

   resp.setValue(24.0, 4, 0);
   resp.setValue(27.0, 4, 1);
   resp.setValue(30.0, 4, 2);
   resp.setValue(5.0, 4, 3);
   resp.setValue(2.0, 4, 4);

   MatrixSquare resp2(5);

   resp2.setValue(8.0, 0, 0);
   resp2.setValue(7.0, 0, 1);
   resp2.setValue(3.0, 0, 2);
   resp2.setValue(17.0, 0, 3);
   resp2.setValue(22.0, 0, 4);

   resp2.setValue(7.0, 1, 0);
   resp2.setValue(2.0, 1, 1);
   resp2.setValue(-7.0, 1, 2);
   resp2.setValue(8.0, 1, 3);
   resp2.setValue(11.0, 1, 4);

   resp2.setValue(1.0, 2, 0);
   resp2.setValue(1.0, 2, 1);
   resp2.setValue(2.0, 2, 2);
   resp2.setValue(3.0, 2, 3);
   resp2.setValue(3.0, 2, 4);

   resp2.setValue(4.0, 3, 0);
   resp2.setValue(5.0, 3, 1);
   resp2.setValue(6.0, 3, 2);
   resp2.setValue(7.0, 3, 3);
   resp2.setValue(2.0, 3, 4);

   resp2.setValue(7.0, 4, 0);
   resp2.setValue(8.0, 4, 1);
   resp2.setValue(9.0, 4, 2);
   resp2.setValue(3.0, 4, 3);
   resp2.setValue(1.0, 4, 4);

   EXPECT_TRUE(B.multiplyByBiggerMatrix(A, SubMatrixPos::lower) == resp);
   EXPECT_TRUE(B.multiplyByBiggerMatrix(A, SubMatrixPos::upper) == resp2);
}

// TEST(TestMatrixSquare, TestDecompQR) {
//    MatrixSquare A(3);

//    A.setValue(12.0, 0, 0);
//    A.setValue(-51.0, 0, 1);
//    A.setValue(4.0, 0, 2);

//    A.setValue(6.0, 1, 0);
//    A.setValue(167.0, 1, 1);
//    A.setValue(-68.0, 1, 2);

//    A.setValue(-4.0, 2, 0);
//    A.setValue(24.0, 2, 1);
//    A.setValue(-41.0, 2, 2);

//    D_PQR qr{A.getPQR()};

//    MatrixSquare resp{(*qr.matQ) * (*qr.matR)};

//    MatrixSquare invA{A.getInverse()};

//    MatrixSquare identity(A.getSize());
//    identity.fillDiagonalWith(utils::ONE);

//    MatrixSquare B(3);

//    B.setValue(12.0, 0, 0);
//    B.setValue(-51.0, 0, 1);
//    B.setValue(4.0, 0, 2);

//    B.setValue(24.0, 1, 0);
//    B.setValue(-102.0, 1, 1);
//    B.setValue(8.0, 1, 2);

//    B.setValue(-4.0, 2, 0);
//    B.setValue(24.0, 2, 1);
//    B.setValue(-41.0, 2, 2);

//    EXPECT_TRUE(resp == A * (*qr.matP));
//    EXPECT_TRUE(B.getRank() == 2);
//    EXPECT_TRUE(identity == A * invA);
// }
