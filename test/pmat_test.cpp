// #include "../src/*.h"
#include "gtest/gtest.h"
#include <iostream>

// TEST(TestSandTes, TestSum) { EXPECT_TRUE(soma(4, 5) == 9); }

// TEST(TestSandTes, TestProd) {
//   if (true) {
//     std::cout << "aqui\n";
//   } else {
//     std::cout << "aqui nao\n";
//   }

//   EXPECT_TRUE(produto(4, 5) == 20);
// }

int main(int argc, char **argv) {
   ::testing::InitGoogleTest(&argc, argv);
   return RUN_ALL_TESTS();
}
