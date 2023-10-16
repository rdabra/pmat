#ifndef CONTAINER1D_H
#define CONTAINER1D_H
#include <cstddef>
#pragma once

#include <blitz/array.h>
#include <memory>
#include <utility>

namespace pmat {

class Container1d {
   private:
      std::unique_ptr<blitz::Array<double, 1>> _ptrVector;

   public:
      Container1d() : _ptrVector{std::make_unique<blitz::Array<double, 1>>()} {};
      Container1d(const Container1d &container)
          : _ptrVector{std::make_unique<blitz::Array<double, 1>>(*container._ptrVector)} {};
      Container1d(Container1d &&container) noexcept
          : _ptrVector{std::move(container._ptrVector)} {};
      Container1d &operator=(const Container1d &container);
      Container1d &operator=(Container1d &&container) noexcept;
      ~Container1d();

      Container1d(const unsigned &size)
          : _ptrVector{std::make_unique<blitz::Array<double, 1>>(size)} {};
      Container1d(const unsigned &size, const double &value);
      Container1d(double data[], const unsigned &size)
          : _ptrVector{std::make_unique<blitz::Array<double, 1>>(data, size)} {};

      inline double operator()(const unsigned &index) const { return (*_ptrVector)(index); };
      inline void set(const unsigned &index, const double &value) { (*_ptrVector)(index) = value; };
      [[nodiscard]] inline unsigned size() const { return _ptrVector->numElements(); };
      inline void resize(const unsigned &size) {
         // Caution: narrowing from unsigned to int
         _ptrVector->resizeAndPreserve(size);
      };
      inline void clear() { _ptrVector->resize(0); };
      void push_back(const double &value);
      void exchange(const unsigned &indexA, const unsigned &indexB);
      void ascendingSort();
      void descendingSort();
};

} // namespace pmat

#endif