#ifndef DSAS_MATRIXSQUARE_H
#define DSAS_MATRIXSQUARE_H
#pragma once

#include "MatrixSkewSymmetric.h"
#include "MatrixSymmetric.h"

class DSAS_MatrixSquare {
   private:
      MatrixSymmetric matS;
      MatrixSkewSymmetric matAS;

   public:
      DSAS_MatrixSquare();
      ~DSAS_MatrixSquare();

   private:
};

#endif