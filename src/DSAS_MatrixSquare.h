#ifndef DSAS_MATRIXSQUARE_H
#define DSAS_MATRIXSQUARE_H
#pragma once

#include "MatrixSkewSymmetric.h"
#include "MatrixSymmetric.h"

#include "MatrixSquare.h"

namespace pmat {

class DSAS_MatrixSquare {
   private:
      const MatrixSquare *_matrix;
      MatrixSymmetric _matS{};
      MatrixSkewSymmetric _matAS{};
      bool _calculated{false};

      void calculate();

   public:
      DSAS_MatrixSquare(const MatrixSquare &matrix);
      DSAS_MatrixSquare(const DSAS_MatrixSquare &sas) = default;
      DSAS_MatrixSquare(DSAS_MatrixSquare &&sas) = default;
      DSAS_MatrixSquare &operator=(const DSAS_MatrixSquare &sas) = default;
      DSAS_MatrixSquare &operator=(DSAS_MatrixSquare &&sas) = default;
      ~DSAS_MatrixSquare() = default;

      const MatrixSymmetric &matS();
      const MatrixSkewSymmetric &matAS();
};

} // namespace pmat
#endif