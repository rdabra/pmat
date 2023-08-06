#ifndef DecompositionCholesky_H
#define DecompositionCholesky_H
#pragma once

#include "DecompositionPLU.h"
#include "MatrixLowerTriangular.h"
#include "MatrixSymmetric.h"

namespace pmat {

// class MatrixSymmetric;

class DecompositionCholesky {
   private:
      const MatrixSymmetric *_matrix;
      MatrixLowerTriangular _factor{};
      bool _calculated{false};
      DecompositionPLU _plu;
      void calculate();

   public:
      DecompositionCholesky(const MatrixSymmetric &matrix);
      DecompositionCholesky(const DecompositionCholesky &chk) = default;
      DecompositionCholesky(DecompositionCholesky &&chk) = default;
      DecompositionCholesky &operator=(const DecompositionCholesky &chk) = default;
      DecompositionCholesky &operator=(DecompositionCholesky &&chk) = default;
      ~DecompositionCholesky() = default;

      /**
       * @brief Calculates the Cholesky factor of the associated matrix, if possible
       * @details The Cholesky Factor of positive-define matrix \f$ A\f$ is a lower-triangular
       *matrix \f$ L\f$ where \f[ A=LL^T \f]
       *
       * @return const MatrixLowerTriangular& Cholesky Factor
       * @exception std::logic_error Matrix not positive definite
       */
      const MatrixLowerTriangular &choleskyFactor();

      /**
       * @brief Calculates the determinant
       *
       * @return double Determinant
       */
      double determinant();

      /**
       * @brief Verifies whether the associated matrix is invertible or not
       *
       * @return true The associated matrix is invertible
       * @return false The associated matrix is singular
       */
      bool isInvertible();

      /**
       * @brief Calculates the inverse of the associated matrix, if possible
       * @details If the associated matrix \f$ S\f$ is invertible, its inverse is obtained from \f$
       * S^{-1}=L^{-T}L^{-1}\f$

       * @return MatrixSquare The inverse of the associated matrix
       * @exception std::logic_error Matrix is singular
       */
      MatrixSquare inverse();

      /**
       * @brief Calculates the inverse of the associated matrix, if possible
       *
       * @return MatrixSymmetric The inverse of the associated matrix
       * @exception std::logic_error Matrix is singular
       */
      MatrixSymmetric inverseAsSymmetric();

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
       * @brief Informs if the associated matrix is positive definite
       * @details A symmetric matrix is considered to be positive definite if it is Cholesky
       * decomposable
       * @see "Matrix Computations", Golub & Van Loan, ISBN  9789380250755, p. 164.
       *
       * @return True if this matrix is positive definite
       */

      bool isPositiveDefinite();
};

} // namespace pmat

#endif