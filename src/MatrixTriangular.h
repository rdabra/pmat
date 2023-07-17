#include "MatrixSquare.h"
#include "Messages.h"

#ifndef MATRIXTRIANGULAR_H
#define MATRIXTRIANGULAR_H
#pragma once

namespace pmat {

class MatrixTriangular : public pmat::MatrixSquare {
   private:
      void transpose() override { throw std::logic_error(messages::MATRIX_NOT_TRANSP); }

   protected:
      [[nodiscard]] unsigned vectorIndex(const unsigned &i, const unsigned &j) const override = 0;

   public:
      MatrixTriangular() : MatrixSquare::MatrixSquare{} {};
      MatrixTriangular(const MatrixTriangular &matrix) = default;
      MatrixTriangular(const MatrixTriangular &&matrix)
          : MatrixSquare::MatrixSquare{std::move(matrix)} {};
      ~MatrixTriangular() override = default;
      MatrixTriangular &operator=(const MatrixTriangular &) = default;
      MatrixTriangular &operator=(MatrixTriangular &&) = default;
      [[nodiscard]] inline unsigned length() const override {
         return (this->size() * this->size() + this->size()) / 2;
      }
      double operator()(const unsigned &row, const unsigned &column) const override = 0;
      void resize(const unsigned &size) override = 0;
      [[nodiscard]] double dotProduct(const Matrix &matrix) const override = 0;
      [[nodiscard]] MatrixSquare toMatrixSquare() const;
      [[nodiscard]] MatrixSquare getSwappedByRows(const unsigned &rowA, const unsigned &rowB,
                                                  const unsigned &startColumn,
                                                  const unsigned &endColumn) const;
      [[nodiscard]] MatrixSquare getSwappedByColumns(const unsigned &columnA,
                                                     const unsigned &columnB,
                                                     const unsigned &startRow,
                                                     const unsigned &endRow) const;
      void fillRandomly(const double &min, const double &max) override = 0;
      void swapRows(const unsigned &rowA, const unsigned &rowB, const unsigned &startColumn,
                    const unsigned &endColumn) override = 0;
      void swapColumns(const unsigned &columnA, const unsigned &columnB, const unsigned &startRow,
                       const unsigned &endRow) override = 0;
      Vector linearSolve(const Vector &rhs) override;
};

} // namespace pmat
#endif