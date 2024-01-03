#ifndef MATRIXSYMMETRIC_H
#define MATRIXSYMMETRIC_H
#pragma once

#include "MatrixSymmetry.h"
#include "pmatUtils.h"

namespace pmat {

class DecompositionCholesky;

class MatrixSymmetric : public pmat::MatrixSymmetry {

   public:
      MatrixSymmetric() = default;
      MatrixSymmetric(const MatrixSymmetric &matrix) = default;
      MatrixSymmetric(MatrixSymmetric &&matrix) noexcept
          : MatrixSymmetry::MatrixSymmetry{std::move(matrix)} {};
      MatrixSymmetric &operator=(const MatrixSymmetric &matrix) = default;
      MatrixSymmetric &operator=(MatrixSymmetric &&matrix) = default;
      ~MatrixSymmetric() override = default;
      explicit MatrixSymmetric(const int &size) : MatrixSymmetry::MatrixSymmetry(size){};
      MatrixSymmetric(const MatrixSquare &matrix, pmat::utils::TriangType type);
      inline double operator()(const int &row, const int &column) const override {
         return column > row ? this->vectorElement(column, row) : this->vectorElement(row, column);
      }
      [[nodiscard]] double at(const int &row, const int &column) const override;
      MatrixSymmetric operator+(const MatrixSymmetric &matrix) const;
      MatrixSquare operator+(const MatrixSymmetry &matrix) const;
      virtual void operator+=(const MatrixSymmetric &matrix);
      virtual void addBy(const MatrixSymmetric &matrix);
      MatrixSymmetric operator-(const MatrixSymmetric &matrix) const;
      MatrixSquare operator-(const MatrixSymmetry &matrix) const;
      virtual void operator-=(const MatrixSymmetric &matrix);
      virtual void subtractBy(const MatrixSymmetric &matrix);
      MatrixSymmetric operator*(const double &scalar) const;
      MatrixSquare operator*(const MatrixSymmetric &matrix) const;
      Matrix operator*(const Matrix &matrix) const override;
      Vector operator*(const Vector &vector) const override;
      void operator*=(const double &scalar) override;
      void transpose() override{};
      void fillWithRandomValues(const double &min, const double &max) override;

      /**
       * @brief Returns a calculator for the Cholesky Decomposition of this matrix
       *
       * @return DecompositionCholesky Cholesky calculator
       */
      DecompositionCholesky decomposeToCholesky();

      /**
       * @brief Returns the Gram Matrix of the specified matrix
       * @details The Gram Matrix of matrix \f$A\f$ is the symmetric matrix \f$A^{T} A\f$
       * @param matrix
       * @return pmat::MatrixSymmetric
       */
      static pmat::MatrixSymmetric gramMatrix(const pmat::Matrix &matrix);
};

} // namespace pmat

#endif