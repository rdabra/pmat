#include <algorithm>
#include <iostream>
#include <memory>
#include <mutex>

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
};

int main() {

   B b;

   b.f();

   return 0;
}