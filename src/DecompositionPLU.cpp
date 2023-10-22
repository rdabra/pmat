#include "DecompositionPLU.h"
#include "Messages.h"
#include "utils.h"
#include <stdexcept>

void pmat::DecompositionPLU::swapRowsBellow(MatrixSquare &matU, const int &idxPivot) {
   int idxMax = idxPivot;
   double valMax = std::abs(matU(idxPivot, idxPivot));
   for (int i = idxPivot + 1; i < matU.size(); i++)
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

void pmat::DecompositionPLU::nullifyElementBellow(MatrixSquare &matU, const int &idxPivot) {
   for (int i = idxPivot + 1; i < matU.size(); i++) {
      _matL.setValue(matU(i, idxPivot) / matU(idxPivot, idxPivot), i, idxPivot);
      for (int j = idxPivot; j < matU.size(); j++)
         matU.setValue(matU(i, j) - matU(idxPivot, j) * _matL(i, idxPivot), i, j);
   }
}

void pmat::DecompositionPLU::calculate() {
   if (!_calculated) {
      if (_strictLUMode) {
         MatrixSquare matU(*_matrix);
         for (int idxPivot = 0; idxPivot < matU.size() - 1; idxPivot++) {
            if (pmat::utils::isZero(matU(idxPivot, idxPivot))) {
               throw std::logic_error(messages::MATRIX_NOT_LU);
            }
            this->nullifyElementBellow(matU, idxPivot);
         }
         for (int i = 0; i < matU.size(); ++i)
            for (int j = i; j < matU.size(); ++j)
               _matU.setValue(matU(i, j), i, j);
      } else {
         MatrixSquare matU(*_matrix);
         for (int idxPivot = 0; idxPivot < matU.size() - 1; idxPivot++) {
            this->swapRowsBellow(matU, idxPivot);
            if (!pmat::utils::isZero(matU(idxPivot, idxPivot)))
               this->nullifyElementBellow(matU, idxPivot);
         }

         for (int i = 0; i < matU.size(); ++i)
            for (int j = i; j < matU.size(); ++j)
               _matU.setValue(matU(i, j), i, j);
      }

      _calculated = true;
   }
}

pmat::DecompositionPLU::DecompositionPLU(const MatrixSquare &matrix)
    : _matrix{&matrix}, _matP{matrix.size()}, _matL{matrix.size()}, _matU{matrix.size()} {
   for (int j = 0; j < _matrix->size(); j++) {
      _matL.setValue(pmat::utils::ONE, j, j);
      _matP.setValue(pmat::utils::ONE, j, j);
   }
}

pmat::DecompositionPLU::DecompositionPLU(const MatrixSquare &matrix, bool calculateStrictLU)
    : _matrix{&matrix}, _matP{matrix.size()}, _matL{matrix.size()}, _matU{matrix.size()},
      _strictLUMode{calculateStrictLU} {
   for (int j = 0; j < _matrix->size(); j++) {
      _matL.setValue(pmat::utils::ONE, j, j);
      _matP.setValue(pmat::utils::ONE, j, j);
   }
}

const pmat::MatrixSquare &pmat::DecompositionPLU::matP() {
   this->calculate();
   return _matP;
}

const pmat::MatrixLowerTriangular &pmat::DecompositionPLU::matL() {
   this->calculate();
   return _matL;
}

const pmat::MatrixUpperTriangular &pmat::DecompositionPLU::matU() {
   this->calculate();
   return _matU;
}

double pmat::DecompositionPLU::determinant() {
   this->calculate();
   double resp{pmat::utils::ONE};
   for (int i = 0; i < _matrix->size(); i++)
      resp *= (_matU)(i, i);
   if (_changeSignForDet)
      resp = -resp;

   return resp;
}

bool pmat::DecompositionPLU::isStrictLUDecomposable() {
   if (_strictLUMode) {
      try {
         this->calculate();
      } catch (...) {
         return false;
      }
      return true;
   } else
      throw std::logic_error(pmat::messages::DECOMP_NOT_LU);
}

bool pmat::DecompositionPLU::isInvertible() {
   this->calculate();
   for (int i = 0; i < _matrix->size(); i++)
      if (utils::isZero(_matU(i, i)))
         return false;

   return true;
}

pmat::MatrixSquare pmat::DecompositionPLU::inverse() {
   if (!this->isInvertible())
      throw std::logic_error(messages::MATRIX_SINGULAR);

   MatrixUpperTriangular invU(_matrix->size());
   MatrixTriangular::findInverseByBackSubstitution(_matU, invU);
   MatrixLowerTriangular invL(_matrix->size());
   MatrixTriangular::findInverseByBackSubstitution(_matL, invL);
   MatrixSquare resp(invU * invL);

   // Recovering adequate positions by swapping columns in reverse order of the swapped rows
   for (int i = 1; i <= _swappedRows.size(); ++i) {
      auto &swappedRow = _swappedRows[_swappedRows.size() - i];
      resp.swapColumns(swappedRow.first, swappedRow.second);
   }

   return resp;
}

bool pmat::DecompositionPLU::isPositiveDefinite() {
   if (this->isStrictLUDecomposable())
      for (int i = 0; i < _matrix->size(); i++)
         if (_matU(i, i) <= pmat::utils::ZERO)
            return false;
   return true;
}

bool pmat::DecompositionPLU::isOrthogonal() {
   if (this->isInvertible()) {
      const MatrixSquare inv(this->inverse());
      for (int i = 0; i < _matrix->size(); ++i)
         for (int j = 0; j < _matrix->size(); ++j)
            if (!pmat::utils::areEqual(inv(i, j), (*_matrix)(j, i)))
               return false;
      return true;
   }
   return false;
}

pmat::Vector pmat::DecompositionPLU::linearSolve(const Vector &rhs) {
   if (rhs.size() != _matrix->size())
      throw std::invalid_argument(messages::NONCOMPT_SIZE_ARG);
   if (!this->isInvertible())
      throw std::logic_error(messages::MATRIX_SINGULAR);

   Vector aux(rhs);
   for (auto &swappedRow : _swappedRows)
      aux.swapElements(swappedRow.first, swappedRow.second);
   Vector resp1{MatrixTriangular::findSolutionByBackSubstitution(_matL, aux)};

   return MatrixTriangular::findSolutionByBackSubstitution(_matU, resp1);
}

void pmat::DecompositionPLU::setStrictLUMode() {
   if (_calculated && !_strictLUMode) {
      _matP.resize(_matrix->size());
      _matL.resize(_matrix->size());
      _matU.resize(_matrix->size());
      for (int j = 0; j < _matrix->size(); j++) {
         _matL.setValue(pmat::utils::ONE, j, j);
         _matP.setValue(pmat::utils::ONE, j, j);
      }
   }
   _strictLUMode = true;
}
