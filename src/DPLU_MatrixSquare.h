#ifndef DPLU_MATRIXSQUARE_H
#define DPLU_MATRIXSQUARE_H
#pragma once

#include "MatrixLowerTriangular.h"
#include "MatrixUpperTriangular.h"

#include "MatrixSquare.h"

namespace pmat {

class DPLU_MatrixSquare {
   private:
      const MatrixSquare *_matrix;
      MatrixSquare _matP{};
      MatrixLowerTriangular _matL{};
      MatrixUpperTriangular _matU{};
      std::vector<std::pair<unsigned, unsigned>> _swappedRows;
      bool _changeSignForDet{false};

      void swapRowsBellow(MatrixSquare &matU, const unsigned &idxPivot);

   public:
      DPLU_MatrixSquare(const MatrixSquare &matrix) : _matrix(&matrix) {}
      DPLU_MatrixSquare(const DPLU_MatrixSquare &plu) = default;
      DPLU_MatrixSquare(DPLU_MatrixSquare &&plu) = default;
      DPLU_MatrixSquare &operator=(const DPLU_MatrixSquare &plu) = default;
      DPLU_MatrixSquare &operator=(DPLU_MatrixSquare &&plu) = default;
      ~DPLU_MatrixSquare();
};

} // namespace pmat
#endif