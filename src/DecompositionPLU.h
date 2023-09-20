#ifndef DecompositionPLU_H
#define DecompositionPLU_H
#pragma once

#include "MatrixLowerTriangular.h"
#include "MatrixSquare.h"
#include "MatrixUpperTriangular.h"

namespace pmat {

/**
 * @brief Computes the LU or the PLU decomposition, where P is a permutation matrix, L is unit lower
 * triangular, U is upper triangular
 *
 */
class DecompositionPLU {
   private:
      const MatrixSquare *_matrix;
      bool _strictLUMode{false};
      MatrixSquare _matP{};
      MatrixLowerTriangular _matL{};
      MatrixUpperTriangular _matU{};
      std::vector<std::pair<unsigned, unsigned>> _swappedRows;
      bool _changeSignForDet{false};
      bool _calculated{false};

      void swapRowsBellow(MatrixSquare &matU, const unsigned &idxPivot);
      void nullifyElementBellow(MatrixSquare &matU, const unsigned &idxPivot);
      void calculate();

   public:
      DecompositionPLU(const MatrixSquare &matrix);

      /**
       * @brief Construct a new Decomposition PLU calculator
       *
       * @param matrix Associated matrix
       * @param strictLUMode specifies if the decomposition is LU or PLU
       */
      DecompositionPLU(const MatrixSquare &matrix, bool strictLUMode);

      DecompositionPLU(const DecompositionPLU &plu) = default;
      DecompositionPLU(DecompositionPLU &&plu) = default;
      DecompositionPLU &operator=(const DecompositionPLU &plu) = default;
      DecompositionPLU &operator=(DecompositionPLU &&plu) = default;
      ~DecompositionPLU() = default;

      /**
       * @brief Calculates the permutation matrix \f$ P\f$ of the PLU Decomposition
       *
       * @return const MatrixSquare& Permutation matrix
       */
      [[nodiscard]] const MatrixSquare &matP();

      /**
       * @brief Calculates the lower triangular matrix \f$ L\f$ of the PLU Decomposition
       *
       * @return const MatrixLowerTriangular& Lower triangular matrix
       */
      [[nodiscard]] const MatrixLowerTriangular &matL();

      /**
       * @brief Calculates the upper triangular matrix \f$ U\f$ of the PLU Decomposition
       *
       * @return const MatrixUpperTriangular& Upper triangular matrix
       */
      [[nodiscard]] const MatrixUpperTriangular &matU();

      /**
       * @brief Generates a list of the rows swapped in order to calculate de PLU decomposition
       *
       * @return const std::vector<std::pair<unsigned, unsigned>>& List of swapped rows
       */
      [[nodiscard]] const std::vector<std::pair<unsigned, unsigned>> &swappedRows() const;

      /**
       * @brief Calculates the determinant
       *
       * @return double Determinant
       */
      [[nodiscard]] double determinant();

      /**
       * @brief Verifies whether the associated matrix is LU decomposable or not
       *
       * @return true The associated matrix is LU decomposable
       * @return false The associated matrix is not LU decomposable
       */
      bool isStrictLUDecomposable();

      /**
       * @brief Verifies whether the associated matrix is invertible or not
       *
       * @return true The associated matrix is invertible
       * @return false The associated matrix is singular
       */
      bool isInvertible();

      /**
       * @brief Calculates the inverse of the associated matrix, if possible
       * @details If the associated matrix \f$ A\f$ is invertible, its inverse is obtained from \f$
       * A^{-1}=U^{-1}L^{-1}P\f$

       * @return MatrixSquare The inverse of the associated matrix
       * @exception std::logic_error Matrix is singular
       */
      MatrixSquare inverse();

      /**
       * @brief Verifies whether the associated matrix is positive definite or not
       ** @details Considering the PLU decomposition, a matrix is considered to be positive definite
       *if every diagonal element of U is positive
       * @see "Matrix Computations", Golub & Van Loan, ISBN  9789380250755, p. 161.
       *
       * @return true The associated matrix is positive definite
       * @return false The associated matrix is not positive definite
       */
      bool isPositiveDefinite();

      /**
       * @brief Verifies whether the associated matrix is orthogonal or not
       * @details A matrix is orthogonal if its inverse equals its transpose

       * @return true The associated matrix is orthogonal
       * @return false The associated matrix is not orthogonal
       */
      bool isOrthogonal();

      /**
       * @brief Finds the solution of the linear system in which the associated matrix in on the
       * left hand side
       *
       * @param rhs The right hand side of the linear system
       * @return Vector Solution of the linear system
       * @exception std::invalid_argument Vector not compatible
       * @exception std::logic_error The associated matrix is singular
       */
      Vector linearSolve(const Vector &rhs);

      /**
       * @brief Verifies whether the associated matrix is orthogonal or not
       *
       * @return true The associated matrix is orthogonal
       * @return false The associated matrix is not orthogonal
       */
      [[nodiscard]] bool isStrictLUMode() const { return _strictLUMode; }

      /**
       * @brief Specifies if the decomposition is LU ou PLU
       *
       */
      void setStrictLUMode();
};

} // namespace pmat
#endif