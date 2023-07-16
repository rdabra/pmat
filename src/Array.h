#ifndef ABSTRACTARRAY_H
#define ABSTRACTARRAY_H
#pragma once

#include <vector>

namespace pmat {

class Array {

   protected:
      // TODO criar um método abstrato para ler dados de arquivo
   public:
      Array() = default;
      Array(const Array &array) = default;
      Array(Array &&) = default;
      Array &operator=(const Array &) = default;
      Array &operator=(Array &&) = default;
      virtual ~Array() = default;

      [[nodiscard]] virtual unsigned length() const = 0;
      [[nodiscard]] virtual unsigned dimension() const = 0;
      [[nodiscard]] virtual unsigned occurrences(const double &value) const = 0;
      virtual void fillRandomly(const double &min, const double &max) = 0;
};

} // namespace pmat

#endif // ABSTRACTARRAY_H
