#ifndef DPQR_MATRIXSQUARE_H
#define DPQR_MATRIXSQUARE_H
#pragma once

#include "MatrixSquare.h"
#include "MatrixUpperTriangular.h"

namespace pmat {

class DPQR_MatrixSquare {
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
      DPQR_MatrixSquare(const MatrixSquare &matrix);
      DPQR_MatrixSquare(const DPQR_MatrixSquare &pqr) = default;
      DPQR_MatrixSquare(DPQR_MatrixSquare &&pqr) = default;
      DPQR_MatrixSquare &operator=(const DPQR_MatrixSquare &pqr) = default;
      DPQR_MatrixSquare &operator=(DPQR_MatrixSquare &&pqr) = default;
      ~DPQR_MatrixSquare() = default;
      const MatrixSquare &matP();
      const MatrixSquare &matQ();
      const MatrixUpperTriangular &matR();
      const unsigned &rank();
      MatrixSquare inverse();
};
} // namespace pmat
#endif