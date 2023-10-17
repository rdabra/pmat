#ifndef CONTAINER1D_H
#define CONTAINER1D_H
#pragma once

#include <blitz/array.h>
#include <memory>
#include <utility>

namespace pmat {

/**
 * @brief One-dimensional container used by the arrays of the lib
 *
 */
class Container1d {
   private:
      std::unique_ptr<blitz::Array<double, 1>> _ptrVector;

   public:
      Container1d() : _ptrVector{std::make_unique<blitz::Array<double, 1>>()} {};
      Container1d(const Container1d &container);
      Container1d(Container1d &&container) noexcept
          : _ptrVector{std::move(container._ptrVector)} {};
      Container1d &operator=(const Container1d &container);
      Container1d &operator=(Container1d &&container) noexcept;
      ~Container1d() = default;

      /**
       * @brief Construct a new Container 1d object
       *
       * @param size Container size
       */
      Container1d(const unsigned &size)
          : _ptrVector{std::make_unique<blitz::Array<double, 1>>(size)} {};

      /**
       * @brief Construct a new Container 1d object
       *
       * @param size Container size
       * @param value Value to be set for all elements
       */
      Container1d(const unsigned &size, const double &value);

      /**
       * @brief Construct a new Container 1d object from a raw array of values
       *
       * @param data Raw array of values
       * @param size Size of the raw array
       */
      Container1d(double data[], const unsigned &size)
          : _ptrVector{std::make_unique<blitz::Array<double, 1>>(data, size)} {};

      /**
       * @brief Returns the value at the specified index
       *
       * @param index
       * @return double
       */
      inline double operator()(const unsigned &index) const { return (*_ptrVector)(index); };

      /**
       * @brief Sets the specified value at the specified index
       *
       * @param index
       * @param value
       */
      inline void set(const unsigned &index, const double &value) { (*_ptrVector)(index) = value; };

      /**
       * @brief Returns the size of the container
       *
       * @return unsigned
       */
      [[nodiscard]] inline unsigned size() const { return _ptrVector->numElements(); };

      /**
       * @brief Resize the container. If the new size is greater than the old size, the new elements
       * are initialized to zero
       *
       * @param size
       */
      void resize(const unsigned &size);

      /**
       * @brief Clears the container and sets its size to zero
       *
       */
      inline void clear() { _ptrVector->resize(0); };

      /**
       * @brief Inserts one element at the end of the container and sets it to the specified value
       *
       * @param value
       */
      void push_back(const double &value);

      /**
       * @brief Exchanges the values of indexA and indexB of the container
       *
       * @param indexA
       * @param indexB
       */
      void exchange(const unsigned &indexA, const unsigned &indexB);

      /**
       * @brief Sorts the container in ascending order
       *
       */
      void ascendingSort();

      /**
       * @brief Sorts the container in descending order
       *
       */
      void descendingSort();
};

} // namespace pmat

#endif