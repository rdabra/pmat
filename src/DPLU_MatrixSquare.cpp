#include "DPLU_MatrixSquare.h"
#include "utils.h"

void pmat::DPLU_MatrixSquare::swapRowsBellow(MatrixSquare &matU, const unsigned &idxPivot) {
   unsigned idxMax = idxPivot;
   double valMax = std::abs(matU(idxPivot, idxPivot));
   for (unsigned i = idxPivot + 1; i < matU.size(); i++)
      if (std::abs(matU(i, idxPivot)) > valMax) {
         valMax = std::abs(matU(i, idxPivot));
         idxMax = i;
      }

   if (idxMax != idxPivot) {
      matU.swapRows(idxMax, idxPivot, 0, _matrix->size());
      _matP.swapRows(idxMax, idxPivot, 0, _matrix->size());
      if (idxPivot > 0)
         _matL.swapRows(idxMax, idxPivot, 0, idxPivot - 1);
      _swappedRows.emplace_back(idxMax, idxPivot);
      _changeSignForDet = !_changeSignForDet;
   }
}

void pmat::DPLU_MatrixSquare::nullifyElementBellow(MatrixSquare &matU, const unsigned &idxPivot) {
   for (unsigned i = idxPivot + 1; i < matU.size(); i++) {
      _matL.setValue(matU(i, idxPivot) / matU(idxPivot, idxPivot), i, idxPivot);
      for (unsigned j = idxPivot; j < matU.size(); j++)
         matU.setValue(matU(i, j) - matU(idxPivot, j) * _matL(i, idxPivot), i, j);
   }
}

void pmat::DPLU_MatrixSquare::calculate() {
   if (!_calculated) {
      MatrixSquare auxMatU{*_matrix}; // CADA MATRIZ PRECISA TER UMA FUNCAO DE ENDERECAMENTO COMO
                                      // ATRIBUTO (VER COMO FAZ)
      for (unsigned idxPivot = 0; idxPivot < auxMatU.size() - 1; idxPivot++) {
         this->swapRowsBellow(auxMatU, idxPivot);
         if (!pmat::utils::isZero(auxMatU(idxPivot, idxPivot)))
            this->nullifyElementBellow(auxMatU, idxPivot);
      }
      for (unsigned i = 0; i < auxMatU.size(); ++i)
         for (unsigned j = i; j < auxMatU.size(); ++j)
            _matU.setValue(auxMatU(i, j), i, j);
      _calculated = true;
   }
}

void pmat::DPLU_MatrixSquare::findInverseByBackSubstitution(const MatrixTriangular &matrix,
                                                            MatrixTriangular &resp) const {
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

pmat::Vector pmat::DPLU_MatrixSquare::findSolutionByBackSubstitution(const MatrixTriangular &matrix,
                                                                     const Vector &rhs) const {
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

pmat::DPLU_MatrixSquare::DPLU_MatrixSquare(const MatrixSquare &matrix)
    : _matrix{&matrix}, _matP{matrix.size()}, _matL{matrix.size()}, _matU{matrix.size()} {
   for (unsigned j = 0; j < _matrix->size(); j++) {
      _matL.setValue(pmat::utils::ONE, j, j);
      _matP.setValue(pmat::utils::ONE, j, j);
   }
}

double pmat::DPLU_MatrixSquare::determinant() {
   this->calculate();
   double resp{pmat::utils::ONE};
   for (unsigned i = 0; i < _matrix->size(); i++)
      resp *= (_matU)(i, i);
   if (_changeSignForDet)
      resp = -resp;

   return resp;
}

bool pmat::DPLU_MatrixSquare::isStrictLUDecomposable() {
   this->calculate();
   for (unsigned i = 0; i < _matrix->size(); i++)
      if (!pmat::utils::isOne(_matP(i, i)))
         return false;

   return true;
}

bool pmat::DPLU_MatrixSquare::isInvertible() {
   this->calculate();
   for (unsigned i = 0; i < _matrix->size(); i++)
      if (utils::isZero(_matU(i, i)))
         return false;

   return true;
}

const pmat::MatrixSquare &pmat::DPLU_MatrixSquare::matP() {
   this->calculate();
   return _matP;
}

const pmat::MatrixLowerTriangular &pmat::DPLU_MatrixSquare::matL() {
   this->calculate();
   return _matL;
}

const pmat::MatrixUpperTriangular &pmat::DPLU_MatrixSquare::matU() {
   this->calculate();
   return _matU;
}

pmat::MatrixSquare pmat::DPLU_MatrixSquare::inverse() {
   if (!this->isInvertible())
      throw std::logic_error(messages::MATRIX_SINGULAR);

   MatrixUpperTriangular invU(_matrix->size());
   this->findInverseByBackSubstitution(_matU, invU);
   MatrixLowerTriangular invL(_matrix->size());
   this->findInverseByBackSubstitution(_matL, invL);
   MatrixSquare resp(invU * invL);

   // Recovering adequate positions by swapping columns in reverse order of the swapped rows
   for (unsigned i = 1; i <= _swappedRows.size(); ++i) {
      auto &swappedRow = _swappedRows[_swappedRows.size() - i];
      resp.swapColumns(swappedRow.first, swappedRow.second, 0, _matrix->size());
   }

   return resp;
}

bool pmat::DPLU_MatrixSquare::isPositiveDefinite() {
   if (this->isStrictLUDecomposable()) {
      for (unsigned i = 0; i < _matrix->size(); i++)
         if (_matU(i, i) <= pmat::utils::ZERO)
            return false;
      return true;
   }

   return false;
}

bool pmat::DPLU_MatrixSquare::isOrthogonal() {
   if (this->isInvertible()) {
      const MatrixSquare inv(this->inverse());
      for (unsigned i = 0; i < _matrix->size(); ++i)
         for (unsigned j = 0; j < _matrix->size(); ++j)
            if (!pmat::utils::areEqual(inv(i, j), (*_matrix)(j, i)))
               return false;
      return true;
   }
   return false;
}
