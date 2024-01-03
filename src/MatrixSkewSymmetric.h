#ifndef MATRIXSKEWSYMMETRIC_H
#define MATRIXSKEWSYMMETRIC_H

#pragma once

#include "MatrixSymmetry.h"
#include "pmatUtils.h"

namespace pmat {

class MatrixSkewSymmetric : public pmat::MatrixSymmetry {

   public:
      MatrixSkewSymmetric() = default;
      explicit MatrixSkewSymmetric(const int &size) : MatrixSymmetry::MatrixSymmetry(size){};
      MatrixSkewSymmetric(const MatrixSkewSymmetric &matrix)
          : MatrixSymmetry::MatrixSymmetry{std::move(matrix)} {}
      MatrixSkewSymmetric(MatrixSkewSymmetric &&matrix) noexcept
          : MatrixSymmetry::MatrixSymmetry{std::move(matrix)} {};
      MatrixSkewSymmetric &operator=(const MatrixSkewSymmetric &matrix) = default;
      MatrixSkewSymmetric &operator=(MatrixSkewSymmetric &&matrix) = default;
      ~MatrixSkewSymmetric() override = default;
      double operator()(const int &row, const int &column) const override {
         return (this->isTransposed() ? pmat::utils::MINUS_ONE : pmat::utils::ONE) *
                (column > row ? pmat::utils::MINUS_ONE * this->vectorElement(column, row)
                              : this->vectorElement(row, column));
      }
      [[nodiscard]] double at(const int &row, const int &column) const override;
      MatrixSkewSymmetric operator+(const MatrixSkewSymmetric &matrix) const;
      MatrixSquare operator+(const MatrixSymmetry &matrix) const;
      virtual void operator+=(const MatrixSkewSymmetric &matrix);
      virtual void addBy(const MatrixSkewSymmetric &matrix);
      MatrixSkewSymmetric operator-(const MatrixSkewSymmetric &matrix) const;
      MatrixSquare operator-(const MatrixSymmetry &matrix) const;
      virtual void operator-=(const MatrixSkewSymmetric &matrix);
      virtual void subtractBy(const MatrixSkewSymmetric &matrix);
      MatrixSkewSymmetric operator*(const double &scalar) const;
      MatrixSquare operator*(const MatrixSkewSymmetric &matrix) const;
      Vector operator*(const Vector &vector) const override;
      Matrix operator*(const Matrix &matrix) const override;
      void operator*=(const double &scalar) override;
      void transpose() override;
      void fillWithRandomValues(const double &min, const double &max) override;
};

} // namespace pmat
#endif