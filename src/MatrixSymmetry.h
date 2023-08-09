#ifndef MATRIXSIMMETRY_H
#define MATRIXSIMMETRY_H
#pragma once

#include "MatrixSquare.h"

namespace pmat {

class MatrixSymmetry : public MatrixSquare {
   private:
      // The following functions are not valid for matrices with symmetry
      void swapRows(const unsigned &rowA, const unsigned &rowB, const unsigned &startColumn,
                    const unsigned &endColumn) override{};
      void swapColumns(const unsigned &columnA, const unsigned &columnB, const unsigned &startRow,
                       const unsigned &endRow) override{};

   protected:
      [[nodiscard]] unsigned vectorIndex(const unsigned &i, const unsigned &j) const override;

   public:
      MatrixSymmetry() = default;
      MatrixSymmetry(const MatrixSymmetry &matrix);
      MatrixSymmetry(MatrixSymmetry &&matrix) = default;
      explicit MatrixSymmetry(const unsigned &size) { this->initializeMembers(size, size, false); };
      ~MatrixSymmetry() override = default;
      MatrixSymmetry &operator=(const MatrixSymmetry &) = default;
      MatrixSymmetry &operator=(MatrixSymmetry &&) = default;
      [[nodiscard]] unsigned length() const override;
      double operator()(const unsigned &row, const unsigned &column) const override = 0;
      void transpose() override = 0;
      void fillWithRandomValues(const double &min, const double &max) override = 0;
};

} // namespace pmat

#endif