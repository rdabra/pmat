#ifndef DPLU_MATRIXSQUARE_H
#define DPLU_MATRIXSQUARE_H
#pragma once

#include "MatrixLowerTriangular.h"
#include "MatrixSquare.h"
#include "MatrixUpperTriangular.h"

namespace pmat {

class DPLU_MatrixSquare {
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
      DPLU_MatrixSquare(const MatrixSquare &matrix);
      DPLU_MatrixSquare(const MatrixSquare &matrix, bool strictLUMode);
      DPLU_MatrixSquare(const DPLU_MatrixSquare &plu) = default;
      DPLU_MatrixSquare(DPLU_MatrixSquare &&plu) = default;
      DPLU_MatrixSquare &operator=(const DPLU_MatrixSquare &plu) = default;
      DPLU_MatrixSquare &operator=(DPLU_MatrixSquare &&plu) = default;
      ~DPLU_MatrixSquare() = default;
      [[nodiscard]] const MatrixSquare &matP();
      [[nodiscard]] const MatrixLowerTriangular &matL();
      [[nodiscard]] const MatrixUpperTriangular &matU();
      [[nodiscard]] const std::vector<std::pair<unsigned, unsigned>> &swappedRows() const;
      [[nodiscard]] double determinant();
      bool isStrictLUDecomposable();
      bool isInvertible();
      MatrixSquare inverse();
      bool isPositiveDefinite();
      bool isOrthogonal();
      Vector linearSolve(const Vector &rhs);
      [[nodiscard]] bool isStrictLUMode() const { return _strictLUMode; }
      void setStrictLUMode();
};

} // namespace pmat
#endif