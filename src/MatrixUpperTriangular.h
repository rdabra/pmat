#ifndef MATRIXUPPERTRIANGULAR_H
#define MATRIXUPPERTRIANGULAR_H
#pragma once

#include "MatrixLowerTriangular.h"
#include "MatrixTriangular.h"

namespace pmat {

class MatrixUpperTriangular : public pmat::MatrixTriangular {

   protected:
      [[nodiscard]] inline int vectorIndex(const int &i, const int &j) const override {
         return (j * (j + 1)) / 2 + i;
      };

   public:
      MatrixUpperTriangular() = default;
      MatrixUpperTriangular(const MatrixUpperTriangular &matrix) = default;
      MatrixUpperTriangular(MatrixUpperTriangular &&matrix) = default;
      explicit MatrixUpperTriangular(const int &size) : MatrixTriangular::MatrixTriangular(size){};
      ~MatrixUpperTriangular() override = default;
      MatrixUpperTriangular &operator=(const MatrixUpperTriangular &matrix) = default;
      MatrixUpperTriangular &operator=(MatrixUpperTriangular &&matrix) = default;
      inline double operator()(const int &row, const int &column) const override {
         return column < row ? pmat::utils::ZERO : this->vectorElement(row, column);
      }
      [[nodiscard]] double at(const int &row, const int &column) const override;
      [[nodiscard]] double dotProduct(const Matrix &matrix) const override;
      MatrixUpperTriangular operator+(const MatrixUpperTriangular &matrix) const;
      virtual void operator+=(const MatrixUpperTriangular &matrix);
      virtual void addBy(const MatrixUpperTriangular &matrix);
      MatrixUpperTriangular operator-(const MatrixUpperTriangular &matrix) const;
      virtual void operator-=(const MatrixUpperTriangular &matrix);
      virtual void subtractBy(const MatrixUpperTriangular &matrix);
      MatrixUpperTriangular operator*(const double &scalar) const;
      MatrixSquare operator*(const MatrixSquare &matrix) const;
      void operator*=(const double &scalar) override;
      MatrixSquare operator+(const MatrixSquare &matrix) const;
      MatrixSquare operator-(const MatrixSquare &matrix) const;
      Vector operator*(const Vector &vector) const override;
      MatrixUpperTriangular operator*(const MatrixUpperTriangular &matrix) const;
      MatrixSquare operator*(const MatrixTriangular &matrix) const;

      /**
       * @brief Gets the transposed matrix of this lower triangular matrix
       *
       * @return MatrixUpperTriangular Transposed matrix
       */
      [[nodiscard]] MatrixLowerTriangular getTranspose() const;

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
         return pmat::utils::TriangType::UPPER;
      };

      /**
       * @brief Calculates the inverse of this matrix through back substitution
       *
       * @return MatrixUpperTriangular The inverse of this matrix
       * @exception throw std::logic_error Singular matrix
       */
      MatrixUpperTriangular inverse();
};

} // namespace pmat

#endif