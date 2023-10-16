#ifndef DecompositionPQR_H
#define DecompositionPQR_H
#pragma once

#include "MatrixSquare.h"
#include "MatrixUpperTriangular.h"
#include <vector>

namespace pmat {

class DecompositionPQR {
   private:
      const MatrixSquare *_matrix;
      MatrixSquare _matP;
      MatrixSquare _matQ;
      MatrixUpperTriangular _matR;
      std::vector<std::pair<unsigned, unsigned>> _swappedColumns;
      unsigned _rank{0};
      bool _calculated{false};

      [[nodiscard]] MatrixSquare calculateHouseholderSubMatrix(const MatrixSquare &partialR,
                                                               const unsigned idxPivot) const;
      void swapPivotColumn(MatrixSquare &partialR, const unsigned &idxPivot);

      void calculate();

   public:
      DecompositionPQR(const MatrixSquare &matrix);
      DecompositionPQR(const DecompositionPQR &pqr) = default;
      DecompositionPQR(DecompositionPQR &&pqr) = default;
      DecompositionPQR &operator=(const DecompositionPQR &pqr) = default;
      DecompositionPQR &operator=(DecompositionPQR &&pqr) = default;
      ~DecompositionPQR() = default;

      /**
       * @brief Calculates the permutation matrix \f$ P\f$ of the PQR Decomposition
       *
       * @return const MatrixSquare& Permutation Matrix
       */
      const MatrixSquare &matP();

      /**
       * @brief Calculates the orthonormal matrix \f$ Q\f$ of the PQR Decomposition
       *
       * @return const MatrixSquare& Orthonormal matrix
       */
      const MatrixSquare &matQ();

      /**
       * @brief Calculates the upper triangular matrix \f$ R\f$ of the PQR Decomposition
       *
       * @return const MatrixUpperTriangular& Matrix \f$ R\f$
       */
      const MatrixUpperTriangular &matR();

      /**
       * @brief Calculates the rank ot the associated matrix
       * @details The rank of a matrix is the maximum number of its linearly independent columns
       *
       * @return const unsigned& Rank of the associated matrix
       */
      const unsigned &rank();

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
       A^{-1}=PR^{-1}Q^{-1}\f$

       * @return MatrixSquare The inverse of the associated matrix
       * @exception std::logic_error Matrix is singular
       */
      MatrixSquare inverse();
};
} // namespace pmat
#endif