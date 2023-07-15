#include "../src/Matrix.h"
#include "../src/Vector.h"
#include "../src/utils.h"
#include "gtest/gtest.h"

using namespace pmat;

TEST(TestVector, TestEqualityOperator) {
   Vector v(7);
   v.setValue(1.0, 0);
   v.setValue(2.0, 1);
   v.setValue(3.0, 2);
   v.setValue(4.0, 3);
   v.setValue(5.0, 4);
   v.setValue(6.0, 5);
   v.setValue(7.0, 6);

   Vector z(7);
   z.setValue(1.0, 0);
   z.setValue(2.0, 1);
   z.setValue(3.0, 2);
   z.setValue(4.0, 3);
   z.setValue(5.0, 4);
   z.setValue(6.0, 5);
   z.setValue(7.0, 6);

   Vector y(7);
   y.setValue(1.0, 0);
   y.setValue(2.0, 1);
   y.setValue(4.0, 2);
   y.setValue(3.0, 3);
   y.setValue(5.0, 4);
   y.setValue(6.0, 5);
   y.setValue(7.0, 6);

   EXPECT_TRUE(v == z);
   EXPECT_FALSE(z == y);
}

TEST(TestVector, TestDotProduct) {
   Vector v(7);
   v.setValue(1.0, 0);
   v.setValue(2.0, 1);
   v.setValue(3.0, 2);
   v.setValue(4.0, 3);
   v.setValue(5.0, 4);
   v.setValue(6.0, 5);
   v.setValue(7.0, 6);

   Vector z(7);
   z.setValue(7.0, 0);
   z.setValue(6.0, 1);
   z.setValue(5.0, 2);
   z.setValue(4.0, 3);
   z.setValue(3.0, 4);
   z.setValue(2.0, 5);
   z.setValue(1.0, 6);

   EXPECT_TRUE(v.dotProduct(z) == 84.0);
}

TEST(TestVector, TestPlus) {
   Vector v(7);
   v.setValue(1.0, 0);
   v.setValue(2.0, 1);
   v.setValue(3.0, 2);
   v.setValue(4.0, 3);
   v.setValue(5.0, 4);
   v.setValue(6.0, 5);
   v.setValue(7.0, 6);

   Vector z(7);
   z.setValue(7.0, 0);
   z.setValue(6.0, 1);
   z.setValue(5.0, 2);
   z.setValue(4.0, 3);
   z.setValue(3.0, 4);
   z.setValue(2.0, 5);
   z.setValue(1.0, 6);

   Vector res(7);
   res.setValue(8.0, 0);
   res.setValue(8.0, 1);
   res.setValue(8.0, 2);
   res.setValue(8.0, 3);
   res.setValue(8.0, 4);
   res.setValue(8.0, 5);
   res.setValue(8.0, 6);

   Vector x1{z + v};
   const Vector &x2 = v + z;
   v.addBy(z);

   EXPECT_TRUE(res == x1);
   EXPECT_TRUE(res == x2);
   EXPECT_TRUE(res == v);
}

TEST(TestVector, TestMinus) {
   Vector v(7);
   v.setValue(1.0, 0);
   v.setValue(2.0, 1);
   v.setValue(3.0, 2);
   v.setValue(4.0, 3);
   v.setValue(5.0, 4);
   v.setValue(6.0, 5);
   v.setValue(7.0, 6);

   Vector z(7);
   z.setValue(7.0, 0);
   z.setValue(6.0, 1);
   z.setValue(5.0, 2);
   z.setValue(4.0, 3);
   z.setValue(3.0, 4);
   z.setValue(2.0, 5);
   z.setValue(1.0, 6);

   Vector res(7);
   res.setValue(-6.0, 0);
   res.setValue(-4.0, 1);
   res.setValue(-2.0, 2);
   res.setValue(0.0, 3);
   res.setValue(2.0, 4);
   res.setValue(4.0, 5);
   res.setValue(6.0, 6);

   Vector x1{v - z};
   const Vector &x2 = v - z;
   v.subtractBy(z);

   EXPECT_TRUE(res == x1);
   EXPECT_TRUE(res == x2);
   EXPECT_TRUE(res == v);
}

TEST(TestVector, TestTimes) {
   Vector v(7);
   v.setValue(1.0, 0);
   v.setValue(2.0, 1);
   v.setValue(3.0, 2);
   v.setValue(4.0, 3);
   v.setValue(5.0, 4);
   v.setValue(6.0, 5);
   v.setValue(7.0, 6);

   double scalar = 3.0;

   Vector res(7);
   res.setValue(3.0, 0);
   res.setValue(6.0, 1);
   res.setValue(9.0, 2);
   res.setValue(12.0, 3);
   res.setValue(15.0, 4);
   res.setValue(18.0, 5);
   res.setValue(21.0, 6);

   Vector x1{v * scalar};
   const Vector &x2 = v * scalar;
   v.multiplyBy(scalar);

   EXPECT_TRUE(res == x1);
   EXPECT_TRUE(res == x2);
   EXPECT_TRUE(res == v);
}

TEST(TestVector, TestFrobenius) {
   Vector v(7);
   v.setValue(1.0, 0);
   v.setValue(2.0, 1);
   v.setValue(3.0, 2);
   v.setValue(4.0, 3);
   v.setValue(5.0, 4);
   v.setValue(6.0, 5);
   v.setValue(7.0, 6);

   double frobV{sqrt(v.dotProduct(v))};

   EXPECT_TRUE(utils::areEqual(v.frobeniusNorm(), frobV));
}

TEST(TestVector, TestNormalization) {
   Vector v(7);
   v.setValue(1.0, 0);
   v.setValue(2.0, 1);
   v.setValue(3.0, 2);
   v.setValue(4.0, 3);
   v.setValue(5.0, 4);
   v.setValue(6.0, 5);
   v.setValue(7.0, 6);

   EXPECT_TRUE(v == v.getUnitaryVector() * v.frobeniusNorm());
}

TEST(TestVector, TestOrder) {
   Vector v(7);
   v.setValue(5.0, 0);
   v.setValue(2.0, 1);
   v.setValue(7.0, 2);
   v.setValue(1.0, 3);
   v.setValue(3.0, 4);
   v.setValue(6.0, 5);
   v.setValue(4.0, 6);

   Vector asc(7);
   asc.setValue(1.0, 0);
   asc.setValue(2.0, 1);
   asc.setValue(3.0, 2);
   asc.setValue(4.0, 3);
   asc.setValue(5.0, 4);
   asc.setValue(6.0, 5);
   asc.setValue(7.0, 6);

   Vector dsc(7);
   dsc.setValue(7.0, 0);
   dsc.setValue(6.0, 1);
   dsc.setValue(5.0, 2);
   dsc.setValue(4.0, 3);
   dsc.setValue(3.0, 4);
   dsc.setValue(2.0, 5);
   dsc.setValue(1.0, 6);

   v.ascendingSort();
   EXPECT_TRUE(v == asc);
   v.descendingSort();
   EXPECT_TRUE(v == dsc);
}

TEST(TestVector, TestOccurrences) {
   Vector v(7);
   v.setValue(1.0, 0);
   v.setValue(5.0, 1);
   v.setValue(3.0, 2);
   v.setValue(7.0, 3);
   v.setValue(5.0, 4);
   v.setValue(5.0, 5);
   v.setValue(7.0, 6);

   EXPECT_TRUE(v.occurrences(5.0) == 3);
   EXPECT_TRUE(v.occurrences(7.0) == 2);
   EXPECT_TRUE(v.occurrences(9.0) == 0);
}

TEST(TestVector, TestMisc) {
   Vector v(7);
   v.setValue(1.0, 0);
   v.setValue(2.0, 1);
   v.setValue(3.0, 2);
   v.setValue(4.0, 3);
   v.setValue(5.0, 4);
   v.setValue(6.0, 5);
   v.setValue(7.0, 6);

   Vector a(v);
   Vector b;
   b = v;
   Vector c;
   c = a * 2.0;

   Vector res(7);
   res.setValue(2.0, 0);
   res.setValue(4.0, 1);
   res.setValue(6.0, 2);
   res.setValue(8.0, 3);
   res.setValue(10.0, 4);
   res.setValue(12.0, 5);
   res.setValue(14.0, 6);

   Vector res1(7);
   res1.setValue(1.0, 0);
   res1.setValue(5.0, 1);
   res1.setValue(3.0, 2);
   res1.setValue(4.0, 3);
   res1.setValue(2.0, 4);
   res1.setValue(6.0, 5);
   res1.setValue(7.0, 6);

   Vector vv(v);
   vv.swapElements(1, 4);

   Vector v1{};
   v1.resize(5);
   v1.fillRandomly(-2.0, 10.0);

   Matrix co{7, 1};
   co.setValue(2.0, 0, 0);
   co.setValue(4.0, 1, 0);
   co.setValue(6.0, 2, 0);
   co.setValue(8.0, 3, 0);
   co.setValue(10.0, 4, 0);
   co.setValue(12.0, 5, 0);
   co.setValue(14.0, 6, 0);

   Matrix li{1, 7};
   li.setValue(2.0, 0, 0);
   li.setValue(4.0, 0, 1);
   li.setValue(6.0, 0, 2);
   li.setValue(8.0, 0, 3);
   li.setValue(10.0, 0, 4);
   li.setValue(12.0, 0, 5);
   li.setValue(14.0, 0, 6);

   EXPECT_TRUE(res.toColumnMatrix() == co);
   EXPECT_TRUE(res.toRowMatrix() == li);
   EXPECT_TRUE(v1.size() == 5);
   EXPECT_TRUE(v1(3) >= -2.0 && v1(3) <= 10.0);
   EXPECT_TRUE(a == v);
   EXPECT_TRUE(v.dimension() == 1);
   EXPECT_TRUE(b == v);
   EXPECT_TRUE(c == res);
   EXPECT_TRUE(vv == res1);
}
