#include "MatrixTriangular.h"
#include "utils.h"
#include <stdexcept>

pmat::MatrixTriangular::MatrixTriangular(const MatrixTriangular &matrix) {
   this->copyMembers(matrix);
}

unsigned pmat::MatrixTriangular::length() const {
   return (this->size() * this->size() + this->size()) / 2;
}

pmat::MatrixSquare pmat::MatrixTriangular::operator*(const MatrixTriangular &matrix) const {
   return MatrixSquare{};
}

pmat::MatrixSquare pmat::MatrixTriangular::getSwappedByRows(const unsigned &rowIndexA,
                                                            const unsigned &rowIndexB) const {
   if (rowIndexA >= this->size() || rowIndexB >= this->size())
      throw std::invalid_argument(pmat::messages::INDEX_OUT);

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

   if (columnIndexA >= this->size() || columnIndexB >= this->size())
      throw std::invalid_argument(pmat::messages::INDEX_OUT);

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

double pmat::MatrixTriangular::determinant() {
   double resp = pmat::utils::ONE;
   for (unsigned i = 0; i < this->size(); i++)
      resp *= (*this)(i, i);

   return resp;
}

bool pmat::MatrixTriangular::isInvertible() {
   for (unsigned i = 0; i < this->size(); i++)
      if (pmat::utils::isZero((*this)(i, i)))
         return false;

   return true;
}

pmat::Vector pmat::MatrixTriangular::linearSolve(const Vector &rhs) {
   if (rhs.size() != this->size())
      throw std::invalid_argument(messages::NONCOMPT_SIZE_ARG);
   if (!this->isInvertible())
      throw std::logic_error(messages::MATRIX_SINGULAR);

   return MatrixTriangular::findSolutionByBackSubstitution(*this, rhs);
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
