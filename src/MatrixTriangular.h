#include "MatrixSquare.h"
#include "Messages.h"

#ifndef MATRIXTRIANGULAR_H
#define MATRIXTRIANGULAR_H
#pragma once

namespace pmat {

enum class TriangType { UPPER, LOWER };

class MatrixTriangular : public pmat::MatrixSquare {
   private:
      void transpose() override {}

   protected:
      [[nodiscard]] unsigned vectorIndex(const unsigned &i, const unsigned &j) const override = 0;

   public:
      MatrixTriangular() = default;
      MatrixTriangular(const MatrixTriangular &matrix) = default;
      MatrixTriangular(MatrixTriangular &&matrix) = default;
      explicit MatrixTriangular(const unsigned &size) { this->initializeMembers(size, size); };
      ~MatrixTriangular() override = default;
      MatrixTriangular &operator=(const MatrixTriangular &) = default;
      MatrixTriangular &operator=(MatrixTriangular &&) = default;
      [[nodiscard]] inline unsigned length() const override {
         return (this->size() * this->size() + this->size()) / 2;
      }
      double operator()(const unsigned &row, const unsigned &column) const override = 0;
      [[nodiscard]] double dotProduct(const Matrix &matrix) const override = 0;
      [[nodiscard]] virtual MatrixSquare toMatrixSquare() const = 0;
      MatrixSquare operator*(const MatrixTriangular &matrix) const;
      [[nodiscard]] MatrixSquare getSwappedByRows(const unsigned &rowIndexA,
                                                  const unsigned &rowIndexB) const;
      [[nodiscard]] MatrixSquare getSwappedByColumns(const unsigned &columnIndexA,
                                                     const unsigned &columnIndexB) const;
      void fillRandomly(const double &min, const double &max) override = 0;
      void swapRows(const unsigned &rowA, const unsigned &rowB, const unsigned &startColumn,
                    const unsigned &endColumn) override = 0;
      void swapColumns(const unsigned &columnA, const unsigned &columnB, const unsigned &startRow,
                       const unsigned &endRow) override = 0;
      [[nodiscard]] virtual TriangType type() const = 0;

      static void findInverseByBackSubstitution(const MatrixTriangular &matrix,
                                                MatrixTriangular &resp);
      static pmat::Vector findSolutionByBackSubstitution(const MatrixTriangular &matrix,
                                                         const Vector &rhs);
};

} // namespace pmat
#endif