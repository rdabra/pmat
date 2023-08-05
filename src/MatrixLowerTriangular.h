#ifndef MATRIXLOWERTRIANGULAR_H
#define MATRIXLOWERTRIANGULAR_H
#pragma once

#include "MatrixTriangular.h"

namespace pmat {

class MatrixUpperTriangular;

class MatrixLowerTriangular : public pmat::MatrixTriangular {
   protected:
      [[nodiscard]] unsigned vectorIndex(const unsigned &i, const unsigned &j) const override;

   public:
      MatrixLowerTriangular() = default;
      explicit MatrixLowerTriangular(const unsigned &size)
          : MatrixTriangular::MatrixTriangular(size){};
      MatrixLowerTriangular(const MatrixLowerTriangular &matrix)
          : MatrixTriangular::MatrixTriangular{std::move(matrix)} {}
      MatrixLowerTriangular(MatrixLowerTriangular &&matrix)
          : MatrixTriangular::MatrixTriangular{std::move(matrix)} {};
      MatrixLowerTriangular &operator=(const MatrixLowerTriangular &matrix) = default;
      MatrixLowerTriangular &operator=(MatrixLowerTriangular &&matrix) = default;
      ~MatrixLowerTriangular() override = default;
      double operator()(const unsigned &row, const unsigned &column) const override;
      [[nodiscard]] double dotProduct(const Matrix &matrix) const override;
      MatrixLowerTriangular operator+(const MatrixLowerTriangular &matrix) const;
      virtual void addBy(const MatrixLowerTriangular &matrix);
      MatrixLowerTriangular operator-(const MatrixLowerTriangular &matrix) const;
      virtual void subtractBy(const MatrixLowerTriangular &matrix);
      MatrixLowerTriangular operator*(const double &scalar) const;
      MatrixSquare operator*(const MatrixSquare &matrix) const;
      void multiplyBy(const double &scalar) override;
      MatrixSquare operator+(const MatrixSquare &matrix) const;
      MatrixSquare operator-(const MatrixSquare &matrix) const;
      MatrixSquare operator*(const MatrixTriangular &matrix) const;
      MatrixLowerTriangular operator*(const MatrixLowerTriangular &matrix) const;
      Vector operator*(const Vector &vector) const override;
      [[nodiscard]] MatrixUpperTriangular getTranspose() const;
      void swapRows(const unsigned &rowA, const unsigned &rowB, const unsigned &startColumn,
                    const unsigned &endColumn) override;
      void swapColumns(const unsigned &colA, const unsigned &colB, const unsigned &startRow,
                       const unsigned &endRow) override;
      void fillRandomly(const double &min, const double &max) override;
      [[nodiscard]] TriangType type() const override { return TriangType::LOWER; };
      MatrixLowerTriangular inverse();
};

} // namespace pmat

#endif