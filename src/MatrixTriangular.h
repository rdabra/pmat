#include "MatrixSquare.h"

#ifndef MATRIXTRIANGULAR_H
#define MATRIXTRIANGULAR_H
#pragma once

namespace pmat {

enum class TriangType { UPPER, LOWER };

class MatrixTriangular : public pmat::MatrixSquare {
   private:
      void transpose() override {}
      inline double &operator()(const int &row, const int &column) override {
         return MatrixSquare::operator()(row, column);
      };

   protected:
      [[nodiscard]] int vectorIndex(const int &i, const int &j) const override = 0;

   public:
      MatrixTriangular() = default;
      MatrixTriangular(const MatrixTriangular &matrix);
      MatrixTriangular(MatrixTriangular &&matrix) = default;
      explicit MatrixTriangular(const int &size) { this->initializeMembers(size, size, false); };
      ~MatrixTriangular() override = default;
      MatrixTriangular &operator=(const MatrixTriangular &) = default;
      MatrixTriangular &operator=(MatrixTriangular &&) = default;
      [[nodiscard]] int length() const override;
      inline double operator()(const int &row, const int &column) const override = 0;
      [[nodiscard]] double dotProduct(const Matrix &matrix) const override = 0;
      MatrixSquare operator*(const MatrixTriangular &matrix) const;
      [[nodiscard]] MatrixSquare getSwappedByRows(const int &rowIndexA, const int &rowIndexB) const;
      [[nodiscard]] MatrixSquare getSwappedByColumns(const int &columnIndexA,
                                                     const int &columnIndexB) const;
      void fillWithRandomValues(const double &min, const double &max) override = 0;
      void swapRows(const int &rowA, const int &rowB, const int &startColumn,
                    const int &endColumn) override = 0;
      void swapColumns(const int &columnA, const int &columnB, const int &startRow,
                       const int &endRow) override = 0;
      [[nodiscard]] virtual TriangType type() const = 0;

      /**
       * @brief Calculates the determinant of this matrix through its diagonal
       *
       * @return double Determinant of this matrix
       */
      double determinant();

      /**
       * @brief Informs if this matrix is invertible by inspecting its diagonal
       *
       * @return true Matrix is invertible
       * @return false Matrix is not invertible
       */
      virtual bool isInvertible();

      /**
       * @brief Calculates the solution of a linear system by back substitution
       *
       * @param rhs Right hand side of the linear system
       * @return Vector Solution of the linear system
       */
      Vector linearSolve(const Vector &rhs);

      /**
       * @brief Independent function for finding inverse by back substitution
       *
       * @param matrix Matrix to be inverted
       * @param resp Inverse of the first argument
       */
      static void findInverseByBackSubstitution(const MatrixTriangular &matrix,
                                                MatrixTriangular &resp);

      /**
       * @brief Independent function for find the solution of a linear system by back substitution
       *
       * @param matrix Known matrix of the linear system
       * @param rhs
       * @return pmat::Vector Solution of the linear system
       */
      static pmat::Vector findSolutionByBackSubstitution(const MatrixTriangular &matrix,
                                                         const Vector &rhs);
};

} // namespace pmat
#endif