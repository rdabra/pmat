#ifndef MATRIXSQUARE_H
#define MATRIXSQUARE_H
#pragma once

#include "Matrix.h"
#include <memory>

namespace pmat {

class DecompositionPLU;
class DecompositionSAS;
class DecompositionPQR;

enum class SubMatrixPos { lower, upper };

class MatrixSquare : public Matrix {
   public:
      MatrixSquare() = default;
      MatrixSquare(MatrixSquare &&matrix) noexcept = default;
      MatrixSquare(Matrix &&matrix);
      explicit MatrixSquare(const unsigned &size) : Matrix{size, size} {}
      MatrixSquare(const MatrixSquare &matrix);
      ~MatrixSquare() override = default;
      MatrixSquare &operator=(const MatrixSquare &matrix) = default;
      MatrixSquare &operator=(MatrixSquare &&matrix) noexcept = default;
      [[nodiscard]] unsigned size() const;
      virtual void resize(const unsigned &size);
      MatrixSquare operator+(const MatrixSquare &matrix) const;
      MatrixSquare operator-(const MatrixSquare &matrix) const;
      MatrixSquare operator*(const MatrixSquare &matrix) const;
      virtual MatrixSquare multiplyByBiggerMatrix(const MatrixSquare &matrix, SubMatrixPos pos);
      MatrixSquare operator*(const double &scalar) const;
      Vector operator*(const Vector &vector) const override;
      [[nodiscard]] virtual double trace() const;
      virtual void fillDiagonalWith(const double &value);
      [[nodiscard]] DecompositionPLU decomposeToPLU() const;
      [[nodiscard]] DecompositionSAS decomposeToSAS() const;
      [[nodiscard]] DecompositionPQR decomposeToPQR() const;
};

} // namespace pmat

#endif