#include "MatrixLowerTriangular.h"
#include "MatrixSquare.h"
#include "MatrixUpperTriangular.h"
#include <algorithm>
#include <iostream>
#include <memory>
#include <mutex>
#include <vector>

class A {

   public:
      A() { std::cout << "Construtor Default\n"; }
      A(const A &a) { std::cout << "Construtor Copia\n"; }
      A(A &&) { std::cout << "Construtor move\n"; }
      A &operator=(const A &) {
         std::cout << "Assign copia\n";
         return *this;
      }
      A &operator=(A &&) {
         std::cout << "Assign move\n";
         return *this;
      }
      virtual int operator*(int a) { return 1; }

      virtual A operator+(A a) { return A{}; }

      virtual std::string g() { return "Estou no pai"; }
      void f() { std::cout << this->g() << "\n"; }
};

class B : public A {
   public:
      B() = default;
      B(const B &b) = default;
      B(B &&b) = default;
      B &operator=(const B &b) = default;
      B &operator=(B &&b) = default;
      std::string g() override { return "Estou no filho"; }
      A operator+(A a) override {
         std::cout << "Sou de B\n";
         return A{};
      }
      int operator*(int a) override { return 1; }
};

class C : public B {
   public:
      C() = default;
      C(const C &c) = default;
      C(C &&b) = default;
      C &operator=(const C &c) = default;
      C &operator=(C &&c) = default;
      std::string g() override { return "Estou no neto"; }

      virtual int hh(int a) = 0;
};

class K {
   public:
      virtual int x() = 0;
      int operator*(const K &k) const {
         std::cout << "Entrei no hh\n";
         return 2;
      };
};

class K1 : public K {
   public:
      int x() override { return 2; }
};

class K2 : public K {
   public:
      int x() override { return 2; }
};

int main() {

   pmat::MatrixLowerTriangular l;
   pmat::MatrixUpperTriangular u;

   pmat::MatrixSquare a = u * l;

   return 0;
}