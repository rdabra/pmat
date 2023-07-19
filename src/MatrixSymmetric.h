#ifndef MATRIXSYMMETRIC_H
#define MATRIXSYMMETRIC_H
#pragma once

#include "MatrixSymmetry.h"

namespace pmat {

class MatrixSymmetric : public pmat::MatrixSymmetry {

   public:
      MatrixSymmetric() = default;
      explicit MatrixSymmetric(const unsigned &size) : MatrixSymmetry::MatrixSymmetry(size){};
      MatrixSymmetric(const MatrixSquare &matrix);
      MatrixSymmetric(const MatrixSymmetric &matrix)
          : MatrixSymmetry::MatrixSymmetry{std::move(matrix)} {}
      MatrixSymmetric(MatrixSymmetric &&matrix)
          : MatrixSymmetry::MatrixSymmetry{std::move(matrix)} {};
      MatrixSymmetric &operator=(const MatrixSymmetric &matrix) = default;
      MatrixSymmetric &operator=(MatrixSymmetric &&matrix) = default;
      ~MatrixSymmetric() override = default;
      double operator()(const unsigned &row, const unsigned &column) const override;
      [[nodiscard]] double dotProduct(const Matrix &matrix) const override;
      MatrixSymmetric operator+(const MatrixSymmetric &matrix) const;
      virtual void addBy(const MatrixSymmetric &matrix);
      MatrixSymmetric operator-(const MatrixSymmetric &matrix) const;
      virtual void subtractBy(const MatrixSymmetric &matrix);
      MatrixSymmetric operator*(const double &scalar) const;
      MatrixSymmetric operator*(const MatrixSymmetric &matrix) const;
      Vector operator*(const Vector &vector) const override {
         return MatrixSquare::operator*(vector);
      }

      void multiplyBy(const double &scalar) override;
      void transpose() override{};
      void fillRandomly(const double &min, const double &max) override;
};

} // namespace pmat

#endif