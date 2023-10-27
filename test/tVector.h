#include "../src/Matrix.h"
#include "../src/Vector.h"
#include "../src/pmatUtils.h"
#include "gtest/gtest.h"
#include <cmath>

using namespace pmat;

TEST(TestVector, TestEqualityOperator) {
   Vector v(7);
   v.assign(1.0, 0);
   v.assign(2.0, 1);
   v.assign(3.0, 2);
   v.assign(4.0, 3);
   v.assign(5.0, 4);
   v.assign(6.0, 5);
   v.assign(7.0, 6);

   Vector z(7);
   z.assign(1.0, 0);
   z.assign(2.0, 1);
   z.assign(3.0, 2);
   z.assign(4.0, 3);
   z.assign(5.0, 4);
   z.assign(6.0, 5);
   z.assign(7.0, 6);

   Vector y(7);
   y.assign(1.0, 0);
   y.assign(2.0, 1);
   y.assign(4.0, 2);
   y.assign(3.0, 3);
   y.assign(5.0, 4);
   y.assign(6.0, 5);
   y.assign(7.0, 6);

   EXPECT_TRUE(v == z);
   EXPECT_FALSE(z == y);
}

TEST(TestVector, TestDotProduct) {
   Vector v(7);
   v.assign(1.0, 0);
   v.assign(2.0, 1);
   v.assign(3.0, 2);
   v.assign(4.0, 3);
   v.assign(5.0, 4);
   v.assign(6.0, 5);
   v.assign(7.0, 6);

   Vector z(7);
   z.assign(7.0, 0);
   z.assign(6.0, 1);
   z.assign(5.0, 2);
   z.assign(4.0, 3);
   z.assign(3.0, 4);
   z.assign(2.0, 5);
   z.assign(1.0, 6);

   EXPECT_TRUE(v.dotProduct(z) == 84.0);
}

TEST(TestVector, TestPlus) {
   Vector v(7);
   v.assign(1.0, 0);
   v.assign(2.0, 1);
   v.assign(3.0, 2);
   v.assign(4.0, 3);
   v.assign(5.0, 4);
   v.assign(6.0, 5);
   v.assign(7.0, 6);

   Vector z(7);
   z.assign(7.0, 0);
   z.assign(6.0, 1);
   z.assign(5.0, 2);
   z.assign(4.0, 3);
   z.assign(3.0, 4);
   z.assign(2.0, 5);
   z.assign(1.0, 6);

   Vector res(7);
   res.assign(8.0, 0);
   res.assign(8.0, 1);
   res.assign(8.0, 2);
   res.assign(8.0, 3);
   res.assign(8.0, 4);
   res.assign(8.0, 5);
   res.assign(8.0, 6);

   Vector x1{z + v};
   const Vector &x2 = v + z;
   v.addBy(z);

   EXPECT_TRUE(res == x1);
   EXPECT_TRUE(res == x2);
   EXPECT_TRUE(res == v);
}

TEST(TestVector, TestMinus) {
   Vector v(7);
   v.assign(1.0, 0);
   v.assign(2.0, 1);
   v.assign(3.0, 2);
   v.assign(4.0, 3);
   v.assign(5.0, 4);
   v.assign(6.0, 5);
   v.assign(7.0, 6);

   Vector z(7);
   z.assign(7.0, 0);
   z.assign(6.0, 1);
   z.assign(5.0, 2);
   z.assign(4.0, 3);
   z.assign(3.0, 4);
   z.assign(2.0, 5);
   z.assign(1.0, 6);

   Vector res(7);
   res.assign(-6.0, 0);
   res.assign(-4.0, 1);
   res.assign(-2.0, 2);
   res.assign(0.0, 3);
   res.assign(2.0, 4);
   res.assign(4.0, 5);
   res.assign(6.0, 6);

   Vector x1{v - z};
   const Vector &x2 = v - z;
   v.subtractBy(z);

   EXPECT_TRUE(res == x1);
   EXPECT_TRUE(res == x2);
   EXPECT_TRUE(res == v);
}

TEST(TestVector, TestTimes) {
   Vector v(7);
   v.assign(1.0, 0);
   v.assign(2.0, 1);
   v.assign(3.0, 2);
   v.assign(4.0, 3);
   v.assign(5.0, 4);
   v.assign(6.0, 5);
   v.assign(7.0, 6);

   double scalar = 3.0;

   Vector res(7);
   res.assign(3.0, 0);
   res.assign(6.0, 1);
   res.assign(9.0, 2);
   res.assign(12.0, 3);
   res.assign(15.0, 4);
   res.assign(18.0, 5);
   res.assign(21.0, 6);

   Vector x1{v * scalar};
   const Vector &x2 = v * scalar;
   v.multiplyBy(scalar);

   EXPECT_TRUE(res == x1);
   EXPECT_TRUE(res == x2);
   EXPECT_TRUE(res == v);
}

TEST(TestVector, TestFrobenius) {
   Vector v(7);
   v.assign(1.0, 0);
   v.assign(2.0, 1);
   v.assign(3.0, 2);
   v.assign(4.0, 3);
   v.assign(5.0, 4);
   v.assign(6.0, 5);
   v.assign(7.0, 6);

   double frobV{sqrt(v.dotProduct(v))};

   EXPECT_TRUE(utils::areEqual(v.frobeniusNorm(), frobV));
}

TEST(TestVector, TestNormalization) {
   Vector v(7);
   v.assign(1.0, 0);
   v.assign(2.0, 1);
   v.assign(3.0, 2);
   v.assign(4.0, 3);
   v.assign(5.0, 4);
   v.assign(6.0, 5);
   v.assign(7.0, 6);

   EXPECT_TRUE(v == v.getUnitaryVector() * v.frobeniusNorm());
}

TEST(TestVector, TestOrder) {
   Vector v(7);
   v.assign(5.0, 0);
   v.assign(2.0, 1);
   v.assign(7.0, 2);
   v.assign(1.0, 3);
   v.assign(3.0, 4);
   v.assign(6.0, 5);
   v.assign(4.0, 6);

   Vector asc(7);
   asc.assign(1.0, 0);
   asc.assign(2.0, 1);
   asc.assign(3.0, 2);
   asc.assign(4.0, 3);
   asc.assign(5.0, 4);
   asc.assign(6.0, 5);
   asc.assign(7.0, 6);

   Vector dsc(7);
   dsc.assign(7.0, 0);
   dsc.assign(6.0, 1);
   dsc.assign(5.0, 2);
   dsc.assign(4.0, 3);
   dsc.assign(3.0, 4);
   dsc.assign(2.0, 5);
   dsc.assign(1.0, 6);

   v.ascendingSort();
   EXPECT_TRUE(v == asc);
   v.descendingSort();
   EXPECT_TRUE(v == dsc);
}

TEST(TestVector, TestOccurrences) {
   Vector v(7);
   v.assign(1.0, 0);
   v.assign(5.0, 1);
   v.assign(3.0, 2);
   v.assign(7.0, 3);
   v.assign(5.0, 4);
   v.assign(5.0, 5);
   v.assign(7.0, 6);

   EXPECT_TRUE(v.occurrences(5.0) == 3);
   EXPECT_TRUE(v.occurrences(7.0) == 2);
   EXPECT_TRUE(v.occurrences(9.0) == 0);
}

TEST(TestVector, TestMisc) {
   Vector v(7);
   v.assign(1.0, 0);
   v.assign(2.0, 1);
   v.assign(3.0, 2);
   v.assign(4.0, 3);
   v.assign(5.0, 4);
   v.assign(6.0, 5);
   v.assign(7.0, 6);

   Vector a(v);
   Vector b;
   b = v;
   Vector c;
   c = a * 2.0;

   Vector res(7);
   res.assign(2.0, 0);
   res.assign(4.0, 1);
   res.assign(6.0, 2);
   res.assign(8.0, 3);
   res.assign(10.0, 4);
   res.assign(12.0, 5);
   res.assign(14.0, 6);

   Vector res1(7);
   res1.assign(1.0, 0);
   res1.assign(5.0, 1);
   res1.assign(3.0, 2);
   res1.assign(4.0, 3);
   res1.assign(2.0, 4);
   res1.assign(6.0, 5);
   res1.assign(7.0, 6);

   Vector vv(v);
   vv.swapElements(1, 4);

   Vector v1{};
   v1.resize(5);
   v1.fillWithRandomValues(-2.0, 10.0);

   Matrix co{7, 1};
   co.assign(2.0, 0, 0);
   co.assign(4.0, 1, 0);
   co.assign(6.0, 2, 0);
   co.assign(8.0, 3, 0);
   co.assign(10.0, 4, 0);
   co.assign(12.0, 5, 0);
   co.assign(14.0, 6, 0);

   Matrix li{1, 7};
   li.assign(2.0, 0, 0);
   li.assign(4.0, 0, 1);
   li.assign(6.0, 0, 2);
   li.assign(8.0, 0, 3);
   li.assign(10.0, 0, 4);
   li.assign(12.0, 0, 5);
   li.assign(14.0, 0, 6);

   Vector vvv{4};
   vvv.fillWith(5.0);

   Vector rrr{4};
   rrr(0) = 5.0;
   rrr(1) = 5.0;
   rrr(2) = 5.0;
   rrr(3) = 5.0;

   Vector x{3};
   x(0) = 4.0;
   x(1) = 5.0;
   x(2) = 7.0;

   double data[] = {8., 13., 7.};
   Vector y{data, 3};

   EXPECT_TRUE(res.toColumnMatrix() == co);
   EXPECT_TRUE(res.toRowMatrix() == li);
   EXPECT_TRUE(v1.length() == 5);
   EXPECT_TRUE(v1(3) >= -2.0 && v1(3) <= 10.0);
   EXPECT_TRUE(a == v);
   EXPECT_TRUE(v.dimension() == 1);
   EXPECT_TRUE(b == v);
   EXPECT_TRUE(c == res);
   EXPECT_TRUE(vv == res1);
   EXPECT_TRUE(vvv == rrr);
   EXPECT_TRUE(pmat::utils::areEqual(x.euclideanDistantFrom(y), y.euclideanDistantFrom(x)));
   EXPECT_TRUE(pmat::utils::areEqual(x.euclideanDistantFrom(y), 8.94427191));
}
