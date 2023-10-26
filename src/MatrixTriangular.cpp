#include "MatrixTriangular.h"
#include "Messages.h"
#include "pmatUtils.h"
#include <stdexcept>
#include <vector>

pmat::MatrixTriangular::MatrixTriangular(const MatrixTriangular &matrix) {
   this->copyMembers(matrix);
}

int pmat::MatrixTriangular::length() const {
   return (this->size() * this->size() + this->size()) / 2;
}

pmat::MatrixSquare pmat::MatrixTriangular::operator*(const MatrixTriangular &matrix) const {
   return MatrixSquare{};
}

pmat::MatrixSquare pmat::MatrixTriangular::getSwappedByRows(const int &rowIndexA,
                                                            const int &rowIndexB) const {
   if (rowIndexA >= this->size() || rowIndexB >= this->size())
      throw std::invalid_argument(pmat::messages::INDEX_OUT);

   MatrixSquare resp(this->size());
   for (int i = 0; i < this->size(); ++i) {
      int k = i;
      if (i == rowIndexA)
         k = rowIndexB;
      else if (i == rowIndexB)
         k = rowIndexA;
      for (int j = 0; j < this->size(); ++j)
         resp.assignNoCheck((*this)(k, j), i, j);
   }

   return resp;
}

pmat::MatrixSquare pmat::MatrixTriangular::getSwappedByColumns(const int &columnIndexA,
                                                               const int &columnIndexB) const {

   if (columnIndexA >= this->size() || columnIndexB >= this->size())
      throw std::invalid_argument(pmat::messages::INDEX_OUT);

   MatrixSquare resp(this->size());
   for (int j = 0; j < this->size(); ++j) {
      int k = j;
      if (j == columnIndexA)
         k = columnIndexB;
      else if (j == columnIndexB)
         k = columnIndexA;
      for (int i = 0; i < this->size(); ++i)
         resp.assignNoCheck((*this)(i, k), i, j);
   }

   return resp;
}

double pmat::MatrixTriangular::determinant() {
   double resp = pmat::utils::ONE;
   for (int i = 0; i < this->size(); i++)
      resp *= (*this)(i, i);

   return resp;
}

bool pmat::MatrixTriangular::isInvertible() {
   for (int i = 0; i < this->size(); i++)
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
   std::vector<int> ids(matrix.size());
   if (matrix.type() == pmat::utils::TriangType::LOWER)
      for (int k = 0; k < matrix.size(); k++)
         ids[k] = k;
   else
      for (int k = 0; k < matrix.size(); k++)
         ids[k] = matrix.size() - k - 1;

   for (int idxPivot = 0; idxPivot < matrix.size(); idxPivot++) {
      resp.assignNoCheck(pmat::utils::ONE / matrix(ids[idxPivot], ids[idxPivot]), ids[idxPivot],
                         ids[idxPivot]);
      for (int i = idxPivot + 1; i < matrix.size(); i++) {
         double num{pmat::utils::ZERO};
         for (int j = idxPivot; j < i; j++)
            num -= matrix(ids[i], ids[j]) * resp(ids[j], ids[idxPivot]);
         resp.assignNoCheck(num / matrix(ids[i], ids[i]), ids[i], ids[idxPivot]);
      }
   }
}

pmat::Vector pmat::MatrixTriangular::findSolutionByBackSubstitution(const MatrixTriangular &matrix,
                                                                    const Vector &rhs) {
   Vector resp(rhs.size());
   std::vector<int> ids(matrix.size());
   if (matrix.type() == pmat::utils::TriangType::LOWER)
      for (int k = 0; k < matrix.size(); k++)
         ids[k] = k;
   else
      for (int k = 0; k < matrix.size(); k++)
         ids[k] = matrix.size() - k - 1;

   resp(ids[0]) = rhs(ids[0]) / matrix(ids[0], ids[0]);
   for (int i = 1; i < matrix.size(); i++) {
      double num{rhs(ids[i])};
      for (int j = 0; j < i; j++)
         num -= matrix(ids[i], ids[j]) * resp(ids[j]);
      resp(ids[i]) = num / matrix(ids[i], ids[i]);
   }

   return resp;
}
