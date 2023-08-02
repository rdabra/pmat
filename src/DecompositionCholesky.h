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
      DecompositionCholesky(const DecompositionCholesky &sas) = default;
      DecompositionCholesky(DecompositionCholesky &&sas) = default;
      DecompositionCholesky &operator=(const DecompositionCholesky &sas) = default;
      DecompositionCholesky &operator=(DecompositionCholesky &&sas) = default;
      ~DecompositionCholesky() = default;

      const MatrixLowerTriangular &choleskyFactor();
      double determinant();
      bool isInvertible();
      MatrixSquare inverse();
      MatrixSymmetric inverseAsSymmetric();
      Vector linearSolve(const Vector &rhs);
      bool isPositiveDefinite();
};

} // namespace pmat

#endif