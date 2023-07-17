#ifndef DPQR_MATRIXSQUARE_H
#define DPQR_MATRIXSQUARE_H
#pragma once

#include "MatrixSquare.h"
#include "MatrixUpperTriangular.h"

namespace pmat {

class DPQR_MatrixSquare {
   private:
      MatrixSquare matP;
      MatrixSquare matQ;
      //      MatrixUpperTriangular matR;
      std::vector<std::pair<unsigned, unsigned>> swappedColumns;
      unsigned rank{0};

   public:
      DPQR_MatrixSquare();
      ~DPQR_MatrixSquare();

   private:
};
} // namespace pmat
#endif