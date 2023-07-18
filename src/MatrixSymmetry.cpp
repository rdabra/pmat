#include "MatrixSymmetry.h"

pmat::MatrixSquare pmat::MatrixSymmetry::toMatrixSquare() const {
   MatrixSquare res(this->size());
   for (unsigned i = 0; i < this->size(); ++i) {
      for (unsigned j = 0; j < this->size(); ++j)
         res.setValue((*this)(i, j), i, j);
   }

   return res;
}

pmat::MatrixSquare pmat::MatrixSymmetry::getSwappedByRows(const unsigned &rowA,
                                                          const unsigned &rowB,
                                                          const unsigned &startColumn,
                                                          const unsigned &endColumn) const {
   MatrixSquare res{this->toMatrixSquare()};
   res.swapRows(rowA, rowB, startColumn, endColumn);

   return res;
}

pmat::MatrixSquare pmat::MatrixSymmetry::getSwappedByColumns(const unsigned &columnA,
                                                             const unsigned &columnB,
                                                             const unsigned &startRow,
                                                             const unsigned &endRow) const {
   MatrixSquare res{this->toMatrixSquare()};
   res.swapColumns(columnA, columnB, startRow, endRow);

   return res;
}

pmat::Vector pmat::MatrixSymmetry::linearSolve(const Vector &rhs) {
   // TODO Implement linear solve
   return Vector{2};
}
