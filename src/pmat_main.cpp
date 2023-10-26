#include "Container1d.h"
#include "Matrix.h"
#include "MatrixSquare.h"

// #include <blitz/array.h>

#include "Matrix.h"

class Foo {
   private:
      int _number{0};

   public:
      Foo() = default;
      Foo(int number) : _number{number} {};
      Foo(const Foo &other) { std::cout << "Copy constructor\n"; };
      Foo(Foo &&other) noexcept { std::cout << "Move constructor\n"; };
      ~Foo() = default;
      Foo operator+(Foo otherFoo) const {
         Foo resp{this->number() + otherFoo.number()};
         return resp;
      }

      int number() const { return _number; }
};

int main() {

   Foo f1{12};
   Foo f2{15};

   Foo f{f1};

   Foo f3{std::move(f1)};

   return 0;
}
