#ifndef MATRIXSIMMETRY_H
#define MATRIXSIMMETRY_H
#pragma once

#include "MatrixSquare.h"

namespace pmat {

class MatrixSymmetry : public MatrixSquare {
   private:
      void swapRows(const unsigned &rowA, const unsigned &rowB, const unsigned &startColumn,
                    const unsigned &endColumn) override{};
      void swapColumns(const unsigned &columnA, const unsigned &columnB, const unsigned &startRow,
                       const unsigned &endRow) override{};

   protected:
      [[nodiscard]] unsigned vectorIndex(const unsigned &i, const unsigned &j) const override {
         return (i * (i + 1)) / 2 + j;
      }

   public:
      MatrixSymmetry() = default;
      MatrixSymmetry(const MatrixSymmetry &matrix) = default;
      MatrixSymmetry(MatrixSymmetry &&matrix) = default;
      explicit MatrixSymmetry(const unsigned &size) { this->initializeMembers(size, size); };
      ~MatrixSymmetry() override = default;
      MatrixSymmetry &operator=(const MatrixSymmetry &) = default;
      MatrixSymmetry &operator=(MatrixSymmetry &&) = default;
      [[nodiscard]] unsigned length() const override {
         return (this->size() * this->size() + this->size()) / 2;
      }
      double operator()(const unsigned &row, const unsigned &column) const override = 0;
      void transpose() override = 0;
      MatrixSquare operator+(const MatrixSquare &matrix) const;
      MatrixSquare operator-(const MatrixSquare &matrix) const;
      [[nodiscard]] MatrixSquare toMatrixSquare() const;
      Matrix operator*(const Matrix &matrix) const override;
      void fillRandomly(const double &min, const double &max) override = 0;
};

} // namespace pmat

#endif