#ifndef MATRIXSYMMETRIC_H
#define MATRIXSYMMETRIC_H
#pragma once

#include "MatrixSymmetry.h"

namespace pmat {

class DecompositionCholesky;

class MatrixSymmetric : public pmat::MatrixSymmetry {

   public:
      MatrixSymmetric() = default;
      explicit MatrixSymmetric(const int &size) : MatrixSymmetry::MatrixSymmetry(size){};
      MatrixSymmetric(const MatrixSymmetric &matrix) = default;
      MatrixSymmetric(MatrixSymmetric &&matrix)
          : MatrixSymmetry::MatrixSymmetry{std::move(matrix)} {};
      MatrixSymmetric &operator=(const MatrixSymmetric &matrix) = default;
      MatrixSymmetric &operator=(MatrixSymmetric &&matrix) = default;
      ~MatrixSymmetric() override = default;
      double operator()(const int &row, const int &column) const override;
      MatrixSymmetric operator+(const MatrixSymmetric &matrix) const;
      MatrixSquare operator+(const MatrixSymmetry &matrix) const;
      virtual void addBy(const MatrixSymmetric &matrix);
      MatrixSymmetric operator-(const MatrixSymmetric &matrix) const;
      MatrixSquare operator-(const MatrixSymmetry &matrix) const;
      virtual void subtractBy(const MatrixSymmetric &matrix);
      MatrixSymmetric operator*(const double &scalar) const;
      MatrixSquare operator*(const MatrixSymmetric &matrix) const;
      Matrix operator*(const Matrix &matrix) const override;
      Vector operator*(const Vector &vector) const override;
      void multiplyBy(const double &scalar) override;
      void transpose() override{};
      void fillWithRandomValues(const double &min, const double &max) override;

      /**
       * @brief Returns a calculator for the Cholesky Decomposition of this matrix
       *
       * @return DecompositionCholesky Cholesky calculator
       */
      DecompositionCholesky decomposeToCholesky();
};

} // namespace pmat

#endif