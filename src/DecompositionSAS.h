#ifndef DecompositionSAS_H
#define DecompositionSAS_H
#pragma once

#include "MatrixSkewSymmetric.h"
#include "MatrixSquare.h"
#include "MatrixSymmetric.h"

namespace pmat {

class DecompositionSAS {
   private:
      const MatrixSquare *_matrix;
      MatrixSymmetric _matS{};
      MatrixSkewSymmetric _matAS{};
      bool _calculated{false};

      void calculate();

   public:
      DecompositionSAS(const MatrixSquare &matrix);
      DecompositionSAS(const DecompositionSAS &sas) = default;
      DecompositionSAS(DecompositionSAS &&sas) = default;
      DecompositionSAS &operator=(const DecompositionSAS &sas) = default;
      DecompositionSAS &operator=(DecompositionSAS &&sas) = default;
      ~DecompositionSAS() = default;

      const MatrixSymmetric &matS();
      const MatrixSkewSymmetric &matAS();
};

} // namespace pmat
#endif