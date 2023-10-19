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
      MatrixSquare operator*(const double &scalar) const;
      Matrix operator*(const Matrix &matrix) const override;

      Vector operator*(const Vector &vector) const override;
      virtual void fillDiagonalWith(const double &value);

      /**
       * @brief Calculates the multiplication of this matrix and the first parameter.
       * @details Given matrices \f$ A\f$ with size \f$ n\f$ and \f$ B\f$ with size \f$ m>n\f$, this
       * function performs \f$A'.B\f$ of size \f$ m\f$ where \f$ A' = [A \quad 0; \quad 0 \quad 1]
       * \f$ or  \f$ A' = [1 \quad 0; \quad 0 \quad A] \f$.
       *
       * @param matrix The right operand, which must not be smaller
       * @param pos Position of this matrix on the matrix \f$A'\f$
       * @return The product of \f$A'\f$ and the parameter
       * @exception invalid_argument Parameters are not compatible
       */
      virtual MatrixSquare multiplyByBiggerMatrix(const MatrixSquare &matrix, SubMatrixPos pos);

      /**
       * @brief Calculates the trace of this matrix
       *
       * @return double Trace of this matrix
       */
      [[nodiscard]] virtual double trace() const;

      /**
       * @brief Returns a calculator for the PLU Decomposition of this matrix
       *
       * @return DecompositionPLU PLU calculator
       */
      [[nodiscard]] DecompositionPLU decomposeToPLU() const;

      /**
       * @brief Returns a calculator for the SAS Decomposition of this matrix
       *
       * @return DecompositionSAS SAS calculator
       */
      [[nodiscard]] DecompositionSAS decomposeToSAS() const;

      /**
       * @brief Returns a calculator for the PQR Decomposition of this matrix
       *
       * @return DecompositionPQR PQR calculator
       */
      [[nodiscard]] DecompositionPQR decomposeToPQR() const;
};

} // namespace pmat

#endif