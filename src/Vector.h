#ifndef VECTOR_H
#define VECTOR_H
#pragma once

#include "Array.h"
#include <vector>

// class Matrix;

namespace pmat {

class Matrix;

class Vector : public Array {
   private:
      std::vector<double> _vector{};

   public:
      Vector() = default;
      Vector(unsigned size) : _vector(size, 0.){};
      Vector(const Vector &vector);
      Vector(Vector &&vector) noexcept : _vector{std::move(vector._vector)} {};
      ~Vector() override = default;
      [[nodiscard]] unsigned length() const override { return _vector.size(); };
      [[nodiscard]] unsigned dimension() const override { return 1; };
      [[nodiscard]] unsigned size() const { return _vector.size(); }
      void resize(const unsigned &size);
      void clear() override { _vector.clear(); };
      void emplaceBack(const double &value);
      void setValue(const double &value, const unsigned &index);
      const double &operator()(const unsigned &index) const;
      Vector &operator=(const Vector &vector);
      Vector &operator=(Vector &&vector) noexcept;
      bool operator==(const Vector &vector) const;
      Vector operator+(const Vector &vector) const;
      void addBy(const Vector &vector);
      Vector operator-(const Vector &vector) const;
      void subtractBy(const Vector &vector);
      Vector operator*(const double &scalar) const;
      void multiplyBy(const double &scalar);
      [[nodiscard]] double dotProduct(const Vector &vector) const;
      [[nodiscard]] double frobeniusNorm() const;
      [[nodiscard]] Vector getUnitaryVector() const;
      [[nodiscard]] unsigned occurrences(const double &value) const override;
      void fillRandomly(const double &min, const double &max) override;
      void swapElements(const unsigned &elmIndexA, const unsigned &elmIndexB);
      void ascendingSort();
      void descendingSort();
      [[nodiscard]] Matrix toColumnMatrix() const;
      [[nodiscard]] Matrix toRowMatrix() const;
};

} // namespace pmat
#endif