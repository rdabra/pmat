#include "MatrixTriangular.h"
#include "utils.h"

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

void pmat::MatrixTriangular::findInverseByBackSubstitution(const MatrixTriangular &matrix,
                                                           MatrixTriangular &resp) {
   std::vector<unsigned> ids(matrix.size());
   if (matrix.type() == TriangType::LOWER)
      for (unsigned k = 0; k < matrix.size(); k++)
         ids[k] = k;
   else
      for (unsigned k = 0; k < matrix.size(); k++)
         ids[k] = matrix.size() - k - 1;

   for (unsigned idxPivot = 0; idxPivot < matrix.size(); idxPivot++) {
      resp.setValue(pmat::utils::ONE / matrix(ids[idxPivot], ids[idxPivot]), ids[idxPivot],
                    ids[idxPivot]);
      for (unsigned i = idxPivot + 1; i < matrix.size(); i++) {
         double num{pmat::utils::ZERO};
         for (unsigned j = idxPivot; j < i; j++)
            num -= matrix(ids[i], ids[j]) * resp(ids[j], ids[idxPivot]);
         resp.setValue(num / matrix(ids[i], ids[i]), ids[i], ids[idxPivot]);
      }
   }
}

pmat::Vector pmat::MatrixTriangular::findSolutionByBackSubstitution(const MatrixTriangular &matrix,
                                                                    const Vector &rhs) {
   Vector resp(rhs.size());
   std::vector<unsigned> ids(matrix.size());
   if (matrix.type() == TriangType::LOWER)
      for (unsigned k = 0; k < matrix.size(); k++)
         ids[k] = k;
   else
      for (unsigned k = 0; k < matrix.size(); k++)
         ids[k] = matrix.size() - k - 1;

   resp.setValue(rhs(ids[0]) / matrix(ids[0], ids[0]), ids[0]);
   for (unsigned i = 1; i < matrix.size(); i++) {
      double num{rhs(ids[i])};
      for (unsigned j = 0; j < i; j++)
         num -= matrix(ids[i], ids[j]) * resp(ids[j]);
      resp.setValue(num / matrix(ids[i], ids[i]), ids[i]);
   }

   return resp;
}
