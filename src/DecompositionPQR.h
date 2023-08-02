#ifndef DecompositionPQR_H
#define DecompositionPQR_H
#pragma once

#include "MatrixSquare.h"
#include "MatrixUpperTriangular.h"

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
      const MatrixSquare &matP();
      const MatrixSquare &matQ();
      const MatrixUpperTriangular &matR();
      const unsigned &rank();
      MatrixSquare inverse();
};
} // namespace pmat
#endif