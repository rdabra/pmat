#ifndef MATRIXLOWERTRIANGULAR_H
#define MATRIXLOWERTRIANGULAR_H
#pragma once

#include "MatrixTriangular.h"

namespace pmat {

class MatrixUpperTriangular;

class MatrixLowerTriangular : public pmat::MatrixTriangular {
   protected:
      [[nodiscard]] inline int vectorIndex(const int &i, const int &j) const override {
         return (i * (i + 1)) / 2 + j;
      }

   public:
      MatrixLowerTriangular() = default;
      explicit MatrixLowerTriangular(const int &size) : MatrixTriangular::MatrixTriangular(size){};
      MatrixLowerTriangular(const MatrixLowerTriangular &matrix)
          : MatrixTriangular::MatrixTriangular{std::move(matrix)} {}
      MatrixLowerTriangular(MatrixLowerTriangular &&matrix) noexcept
          : MatrixTriangular::MatrixTriangular{std::move(matrix)} {};
      MatrixLowerTriangular &operator=(const MatrixLowerTriangular &matrix) = default;
      MatrixLowerTriangular &operator=(MatrixLowerTriangular &&matrix) = default;
      ~MatrixLowerTriangular() override = default;
      double operator()(const int &row, const int &column) const override {
         return column > row ? pmat::utils::ZERO : this->vectorElement(row, column);
      };
      [[nodiscard]] double at(const int &row, const int &column) const override;
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

      /**
       * @brief Gets the transposed matrix of this lower triangular matrix
       *
       * @return MatrixUpperTriangular Transposed matrix
       */
      [[nodiscard]] MatrixUpperTriangular getTranspose() const;

      void swapRows(const int &rowA, const int &rowB, const int &startColumn,
                    const int &endColumn) override;
      void swapColumns(const int &colA, const int &colB, const int &startRow,
                       const int &endRow) override;
      void fillWithRandomValues(const double &min, const double &max) override;

      /**
       * @brief Informs the triangular type of his matrix
       *
       * @return TriangType Triangular type
       */
      [[nodiscard]] pmat::utils::TriangType type() const override {
         return pmat::utils::TriangType::LOWER;
      };

      /**
       * @brief Calculates the inverse of this matrix through back substitution
       *
       * @return MatrixLowerTriangular The inverse of this matrix
       * @exception throw std::logic_error Singular matrix
       */
      MatrixLowerTriangular inverse();
};

} // namespace pmat

#endif