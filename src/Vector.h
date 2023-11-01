#ifndef VECTOR_H
#define VECTOR_H
#pragma once

#include "Array.h"
#include "Container1d.h"

namespace pmat {

class Matrix;

/**
 * @brief Entity for one-dimensional array
 *
 */
class Vector : public Array {
   private:
      pmat::Container1d _vector{};

   public:
      Vector() = default;
      Vector(const int &size) : _vector(size){};
      Vector(const Vector &vector);
      Vector(Vector &&vector) noexcept : _vector{std::move(vector._vector)} {};
      ~Vector() override = default;
      Vector(double data[], const int &size);
      [[nodiscard]] int length() const override { return _vector.size(); };
      [[nodiscard]] int dimension() const override { return 1; };

      /**
       * @brief Informs the size of vector dimension
       *
       * @return int Size of vector dimension
       */
      [[nodiscard]] int size() const { return _vector.size(); }

      /**
       * @brief Clears this vector and sets a new size
       *
       * @param size New size
       */
      void resize(const int &size);

      void clear() override { _vector.clear(); };
      void pushBack(const double &value);

      /**
       * @brief Sets the specified value at the specified position with bounds checking
       *
       * @param value Value to be set
       * @param index Position in vector
       */
      void assign(const double &value, const int &index);

      /**
       * @brief Returns the value at the specified position with bounds checking
       *
       * @param index Position
       * @return double
       */
      [[nodiscard]] double at(const int &index) const;

      /**
       * @brief Informs the value at the specified position without bounds checking
       *
       * @param index Position of the value to be specified
       * @return const double Value at the specified position
       */
      inline double operator()(const int &index) const { return _vector(index); };

      /**
       * @brief Informs the reference at the specified position without bounds checking
       *
       * @param index Position of the value to be specified
       * @return const double& Reference at the specified position
       */
      inline double &operator()(const int &index) { return _vector(index); }

      Vector &operator=(const Vector &vector);
      Vector &operator=(Vector &&vector) noexcept;
      bool operator==(const Vector &vector) const;

      /**
       * @brief Sums this vector and the specified vector
       *
       * @param vector Second operand of the sum
       * @return Vector Sum result
       */
      Vector operator+(const Vector &vector) const;

      /**
       * @brief Sums this vector and the specified vector, setting the result in this vector
       *
       * @param vector Second operand
       */
      void addBy(const Vector &vector);

      /**
       * @brief Subtracts this vector and the specified vector
       *
       * @param vector Right operand of the sum
       * @return Vector Sum result
       */
      Vector operator-(const Vector &vector) const;

      /**
       * @brief Subtracts this vector and the specified vector, setting the result in this vector
       *
       * @param vector Right operand
       */
      void subtractBy(const Vector &vector);

      /**
       * @brief Multiplies this vector by the specified scalar
       *
       * @param scalar Second operand of the multiplication
       * @return Vector Multiplication result
       */
      Vector operator*(const double &scalar) const;

      /**
       * @brief Multiplies this vector by the specified scalar, setting the result in this vector
       *
       * @param scalar Second operand of the multiplication
       */
      void multiplyBy(const double &scalar);

      /**
       * @brief Calculates the dot product of this vector with the specified vector
       * @param vector Second operand
       * @details The dot product of vectors \f$ v\f$ and \f$ u\f$ is
       *  \f[
       *		v.u = \sum_{i}v_{i}u_{i}
       *  \f]
       * @return double Dot product result
       * @exception std::invalid_argument Operands are not compatible
       */
      [[nodiscard]] double dotProduct(const Vector &vector) const;

      /**
       * @brief Calculates the Frobenius Norm of this vector
       * @details Frobenius Norm of vector \f$ v\f$ is calculated from the dot product the following
       *way: \f[ \sqrt{v:v} \f]
       * @return Frobenius Norm result
       */
      [[nodiscard]] double frobeniusNorm() const;

      /**
       * @brief Gets the unitary vector related to this vector
       *
       * @return Vector Unitary vector
       */
      [[nodiscard]] Vector getUnitaryVector() const;
      [[nodiscard]] int occurrences(const double &value) const override;

      void fillWith(const double &value) override;
      void fillWithRandomValues(const double &min, const double &max) override;

      /**
       * @brief Swaps the elements of the vector according to the specified positions
       *
       * @param elmIndexA Position A
       * @param elmIndexB Position B
       * @exception std::invalid_argument Index out of bounds
       */
      void swapElements(const int &elmIndexA, const int &elmIndexB);

      /**
       * @brief Sorts the values of this vector in ascending order
       *
       */
      void ascendingSort();

      /**
       * @brief Sorts the values of this vector in descending order
       *
       */
      void descendingSort();

      /**
       * @brief Converts this vector to a column matrix
       *
       * @return Matrix Column matrix
       */
      [[nodiscard]] Matrix toColumnMatrix() const;

      /**
       * @brief Converts this vector to a row matrix
       *
       * @return Matrix Row matrix
       */
      [[nodiscard]] Matrix toRowMatrix() const;

      /**
       * @brief Returns the Euclidean distance between this vector and the specified
       *
       * @param vector
       * @return double
       */
      [[nodiscard]] double euclideanDistantFrom(const Vector &vector) const;

      [[nodiscard]] int hammingDistantFrom(const Vector &vector) const;

      [[nodiscard]] std::string formattedString() const override;
};

} // namespace pmat
#endif