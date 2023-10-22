#ifndef MATRIXSIMMETRY_H
#define MATRIXSIMMETRY_H
#pragma once

#include "MatrixSquare.h"

namespace pmat {

class MatrixSymmetry : public MatrixSquare {
   private:
      // The following functions are not valid for matrices with symmetry
      void swapRows(const int &rowA, const int &rowB, const int &startColumn,
                    const int &endColumn) override{};
      void swapColumns(const int &columnA, const int &columnB, const int &startRow,
                       const int &endRow) override{};
      inline double &operator()(const int &row, const int &column) override {
         return Matrix::operator()(row, column);
      };

   protected:
      [[nodiscard]] inline int vectorIndex(const int &i, const int &j) const override {
         return (i * (i + 1)) / 2 + j;
      };

   public:
      MatrixSymmetry() = default;
      MatrixSymmetry(const MatrixSymmetry &matrix);
      MatrixSymmetry(MatrixSymmetry &&matrix) = default;
      explicit MatrixSymmetry(const int &size) { this->initializeMembers(size, size, false); };
      ~MatrixSymmetry() override = default;
      MatrixSymmetry &operator=(const MatrixSymmetry &) = default;
      MatrixSymmetry &operator=(MatrixSymmetry &&) = default;
      [[nodiscard]] int length() const override;
      inline double operator()(const int &row, const int &column) const override = 0;
      void transpose() override = 0;
      void fillWithRandomValues(const double &min, const double &max) override = 0;
};

} // namespace pmat

#endif