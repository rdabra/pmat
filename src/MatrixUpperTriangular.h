#ifndef MATRIXUPPERTRIANGULAR_H
#define MATRIXUPPERTRIANGULAR_H
#pragma once

#include "MatrixLowerTriangular.h"
#include "MatrixTriangular.h"

namespace pmat {

class MatrixUpperTriangular : public pmat::MatrixTriangular {

   protected:
      [[nodiscard]] unsigned vectorIndex(const unsigned &i, const unsigned &j) const override {
         return (j * (j + 1)) / 2 + i;
      }

   public:
      MatrixUpperTriangular() = default;
      MatrixUpperTriangular(const MatrixUpperTriangular &matrix) = default;
      MatrixUpperTriangular(MatrixUpperTriangular &&matrix) = default;
      explicit MatrixUpperTriangular(const unsigned &size)
          : MatrixTriangular::MatrixTriangular(size){};
      ~MatrixUpperTriangular() override = default;
      MatrixUpperTriangular &operator=(const MatrixUpperTriangular &matrix) = default;
      MatrixUpperTriangular &operator=(MatrixUpperTriangular &&matrix) = default;
      double operator()(const unsigned &row, const unsigned &column) const override;
      [[nodiscard]] double dotProduct(const Matrix &matrix) const override;
      MatrixUpperTriangular operator+(const MatrixUpperTriangular &matrix) const;
      virtual void addBy(const MatrixUpperTriangular &matrix);
      MatrixUpperTriangular operator-(const MatrixUpperTriangular &matrix) const;
      virtual void subtractBy(const MatrixUpperTriangular &matrix);
      MatrixUpperTriangular operator*(const double &scalar) const;
      MatrixSquare operator*(const MatrixSquare &matrix) const;
      void multiplyBy(const double &scalar) override;
      [[nodiscard]] MatrixSquare toMatrixSquare() const override;
      MatrixSquare operator+(const MatrixSquare &matrix) const;
      MatrixSquare operator-(const MatrixSquare &matrix) const;
      Vector operator*(const Vector &vector) const override {
         return MatrixSquare::operator*(vector);
      }
      MatrixUpperTriangular operator*(const MatrixUpperTriangular &matrix) const;
      MatrixSquare operator*(const MatrixTriangular &matrix) const;
      [[nodiscard]] MatrixLowerTriangular getTranspose() const;
      void swapRows(const unsigned &rowA, const unsigned &rowB, const unsigned &startColumn,
                    const unsigned &endColumn) override;
      void swapColumns(const unsigned &colA, const unsigned &colB, const unsigned &startRow,
                       const unsigned &endRow) override;
      void fillRandomly(const double &min, const double &max) override;
      [[nodiscard]] TriangType type() const override { return TriangType::UPPER; };
      MatrixUpperTriangular inverse();
};

} // namespace pmat

#endif