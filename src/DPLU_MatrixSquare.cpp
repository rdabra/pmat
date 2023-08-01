#include "DPLU_MatrixSquare.h"
#include "utils.h"
#include <stdexcept>

void pmat::DPLU_MatrixSquare::swapRowsBellow(MatrixSquare &matU, const unsigned &idxPivot) {
   unsigned idxMax = idxPivot;
   double valMax = std::abs(matU(idxPivot, idxPivot));
   for (unsigned i = idxPivot + 1; i < matU.size(); i++)
      if (std::abs(matU(i, idxPivot)) > valMax) {
         valMax = std::abs(matU(i, idxPivot));
         idxMax = i;
      }

   if (idxMax != idxPivot) {
      matU.swapRows(idxMax, idxPivot);
      _matP.swapRows(idxMax, idxPivot);
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
      if (_strictLUMode) {
         MatrixSquare matU(*_matrix);
         for (unsigned idxPivot = 0; idxPivot < matU.size() - 1; idxPivot++) {
            if (pmat::utils::isZero(matU(idxPivot, idxPivot))) {
               throw std::logic_error(messages::MATRIX_NOT_LU);
            }
            this->nullifyElementBellow(matU, idxPivot);
         }
         for (unsigned i = 0; i < matU.size(); ++i)
            for (unsigned j = i; j < matU.size(); ++j)
               _matU.setValue(matU(i, j), i, j);
      } else {
         MatrixSquare matU(*_matrix);
         for (unsigned idxPivot = 0; idxPivot < matU.size() - 1; idxPivot++) {
            this->swapRowsBellow(matU, idxPivot);
            if (!pmat::utils::isZero(matU(idxPivot, idxPivot)))
               this->nullifyElementBellow(matU, idxPivot);
         }

         for (unsigned i = 0; i < matU.size(); ++i)
            for (unsigned j = i; j < matU.size(); ++j)
               _matU.setValue(matU(i, j), i, j);
      }

      _calculated = true;
   }
}

pmat::DPLU_MatrixSquare::DPLU_MatrixSquare(const MatrixSquare &matrix)
    : _matrix{&matrix}, _matP{matrix.size()}, _matL{matrix.size()}, _matU{matrix.size()} {
   for (unsigned j = 0; j < _matrix->size(); j++) {
      _matL.setValue(pmat::utils::ONE, j, j);
      _matP.setValue(pmat::utils::ONE, j, j);
   }
}

pmat::DPLU_MatrixSquare::DPLU_MatrixSquare(const MatrixSquare &matrix, bool calculateStrictLU)
    : _matrix{&matrix}, _matP{matrix.size()}, _matL{matrix.size()}, _matU{matrix.size()},
      _strictLUMode{calculateStrictLU} {
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
   if (_strictLUMode) {
      try {
         this->calculate();
      } catch (...) {
         return false;
      }
      return true;
   } else
      throw std::logic_error(
          "Calculation Mode is not Strict LU"); // TODO Calculation Mode is not Strict LU
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
   MatrixTriangular::findInverseByBackSubstitution(_matU, invU);
   MatrixLowerTriangular invL(_matrix->size());
   MatrixTriangular::findInverseByBackSubstitution(_matL, invL);
   MatrixSquare resp(invU * invL);

   // Recovering adequate positions by swapping columns in reverse order of the swapped rows
   for (unsigned i = 1; i <= _swappedRows.size(); ++i) {
      auto &swappedRow = _swappedRows[_swappedRows.size() - i];
      resp.swapColumns(swappedRow.first, swappedRow.second);
   }

   return resp;
}

bool pmat::DPLU_MatrixSquare::isPositiveDefinite() {
   if (this->isStrictLUDecomposable())
      for (unsigned i = 0; i < _matrix->size(); i++)
         if (_matU(i, i) <= pmat::utils::ZERO)
            return false;
   return true;
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

pmat::Vector pmat::DPLU_MatrixSquare::linearSolve(const Vector &rhs) {
   return Vector{}; // TODO Linear solve
}

void pmat::DPLU_MatrixSquare::setStrictLUMode() {
   if (_calculated && !_strictLUMode) {
      _matP.resize(_matrix->size());
      _matL.resize(_matrix->size());
      _matU.resize(_matrix->size());
      for (unsigned j = 0; j < _matrix->size(); j++) {
         _matL.setValue(pmat::utils::ONE, j, j);
         _matP.setValue(pmat::utils::ONE, j, j);
      }
   }
   _strictLUMode = true;
}
