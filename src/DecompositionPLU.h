#ifndef DecompositionPLU_H
#define DecompositionPLU_H
#pragma once

#include "MatrixLowerTriangular.h"
#include "MatrixSquare.h"
#include "MatrixUpperTriangular.h"

namespace pmat {

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
      DecompositionPLU(const MatrixSquare &matrix, bool strictLUMode);
      DecompositionPLU(const DecompositionPLU &plu) = default;
      DecompositionPLU(DecompositionPLU &&plu) = default;
      DecompositionPLU &operator=(const DecompositionPLU &plu) = default;
      DecompositionPLU &operator=(DecompositionPLU &&plu) = default;
      ~DecompositionPLU() = default;
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