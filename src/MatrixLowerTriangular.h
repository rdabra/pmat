#ifndef MATRIXLOWERTRIANGULAR_H
#define MATRIXLOWERTRIANGULAR_H
#pragma once

#include "MatrixTriangular.h"

namespace pmat {

class MatrixUpperTriangular;

class MatrixLowerTriangular : public pmat::MatrixTriangular {
   protected:
      [[nodiscard]] unsigned vectorIndex(const unsigned &i, const unsigned &j) const override {
         return (i * (i + 1)) / 2 + j;
      }

   public:
      MatrixLowerTriangular() = default;
      explicit MatrixLowerTriangular(const unsigned &size);
      MatrixLowerTriangular(const MatrixSquare &matrix);
      MatrixLowerTriangular(const MatrixLowerTriangular &matrix)
          : MatrixTriangular::MatrixTriangular{std::move(matrix)} {}
      MatrixLowerTriangular(MatrixLowerTriangular &&matrix)
          : MatrixTriangular::MatrixTriangular{std::move(matrix)} {};
      MatrixLowerTriangular &operator=(const MatrixLowerTriangular &matrix);
      MatrixLowerTriangular &operator=(MatrixLowerTriangular &&matrix);
      ~MatrixLowerTriangular() override = default;
      double operator()(const unsigned &row, const unsigned &column) const override;
      void resize(const unsigned &size) override;
      [[nodiscard]] double dotProduct(const Matrix &matrix) const override;
      MatrixLowerTriangular operator+(const MatrixLowerTriangular &matrix) const;
      virtual void addBy(const MatrixLowerTriangular &matrix);
      MatrixLowerTriangular operator-(const MatrixLowerTriangular &matrix) const;
      virtual void subtractBy(const MatrixLowerTriangular &matrix);
      MatrixLowerTriangular operator*(const double &scalar) const;
      void multiplyBy(const double &scalar) override;
      [[nodiscard]] MatrixUpperTriangular getTranspose() const;
      void swapRows(const unsigned &rowA, const unsigned &rowB, const unsigned &startColumn,
                    const unsigned &endColumn) override;
      void swapColumns(const unsigned &colA, const unsigned &colB, const unsigned &startRow,
                       const unsigned &endRow) override;
      void fillRandomly(const double &min, const double &max) override;
};

} // namespace pmat

#endif