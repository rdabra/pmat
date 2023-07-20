#include "MatrixTriangular.h"

pmat::MatrixSquare pmat::MatrixTriangular::operator*(const MatrixTriangular &matrix) const {
   return MatrixSquare{};
}

pmat::MatrixSquare pmat::MatrixTriangular::getSwappedByRows(const unsigned &rowIndexA,
                                                            const unsigned &rowIndexB) const {
   // TODO this->validateIndex(rowIndexA, 0);
   // this->validateIndex(rowIndexB, 0);

   MatrixSquare resp(this->size());
   for (unsigned i = 0; i < this->size(); ++i) {
      unsigned k = i;
      if (i == rowIndexA)
         k = rowIndexB;
      else if (i == rowIndexB)
         k = rowIndexA;
      for (unsigned j = 0; j < this->size(); ++j)
         resp.setValue((*this)(k, j), i, j);
   }

   return resp;
}

pmat::MatrixSquare pmat::MatrixTriangular::getSwappedByColumns(const unsigned &columnIndexA,
                                                               const unsigned &columnIndexB) const {
   // TODO this->validateIndex(0, columnIndexA);
   // this->validateIndex(0, columnIndexB);

   MatrixSquare resp(this->size());
   for (unsigned j = 0; j < this->size(); ++j) {
      unsigned k = j;
      if (j == columnIndexA)
         k = columnIndexB;
      else if (j == columnIndexB)
         k = columnIndexA;
      for (unsigned i = 0; i < this->size(); ++i)
         resp.setValue((*this)(i, k), i, j);
   }

   return resp;
}
