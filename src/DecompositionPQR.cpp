#include "DecompositionPQR.h"
#include "Messages.h"
#include "pmatUtils.h"
#include <cmath>
#include <stdexcept>

/**
 * @brief Calculates the Householder matrix by using the opposite sign of the column Frobenius norm
 * @param partialR Partial \f$ R \f$ matrix
 * @param idxPivot Column and row index from which the Householder matrix is calculated
 * @return Householder matrix
 * @see https://en.wikipedia.org/wiki/QR_decomposition
 */
pmat::MatrixSquare
pmat::DecompositionPQR::calculateHouseholderSubMatrix(const MatrixSquare &partialR,
                                                      const int idxPivot) const {

   Vector u(partialR.size() - idxPivot);
   double alpha{pmat::utils::ZERO};
   for (int i = idxPivot; i < partialR.size(); ++i) {
      alpha += partialR(i, idxPivot) * partialR(i, idxPivot);
      u.setValue(partialR(i, idxPivot), i - idxPivot);
   }

   // Using the opposite sign of the Frobenius norm
   alpha = -pmat::utils::ONE * pmat::utils::signOf(partialR(idxPivot, idxPivot)) * std::sqrt(alpha);

   u.setValue(u(0) - alpha, 0);

   const double squareNormU = u.dotProduct(u);
   MatrixSquare resp(u.size());
   for (int i = 0; i < resp.size(); ++i) {
      if (pmat::utils::isZero(squareNormU))
         resp.setValue(pmat::utils::ONE, i, i);
      else
         for (int j = 0; j < resp.size(); ++j) {
            if (i == j)
               resp.setValue(pmat::utils::ONE - pmat::utils::TWO * u(i) * u(j) / squareNormU, i, j);
            else
               resp.setValue(-pmat::utils::TWO * u(i) * u(j) / squareNormU, i, j);
         }
   }

   return resp;
}

void pmat::DecompositionPQR::swapPivotColumn(MatrixSquare &partialR, const int &idxPivot) {
   double normMax{pmat::utils::ZERO};
   int jMax{idxPivot};

   for (int j = idxPivot; j < partialR.size(); ++j) {
      double normAux{pmat::utils::ZERO};
      for (int i = 0; i < partialR.size(); ++i)
         normAux += partialR(i, j) * partialR(i, j);
      if (normAux > normMax) {
         normMax = normAux;
         jMax = j;
      }
   }

   if (jMax != idxPivot) {
      partialR.swapColumns(jMax, idxPivot);
      _matP.swapColumns(jMax, idxPivot);
      _swappedColumns.emplace_back(jMax, idxPivot);
   }
}

void pmat::DecompositionPQR::calculate() {
   if (!_calculated) {
      MatrixSquare A(*_matrix);
      this->swapPivotColumn(A, 0);
      MatrixSquare matQAux(this->calculateHouseholderSubMatrix(A, 0));
      MatrixSquare matR(matQAux * A);
      for (int idxPivot = 1; idxPivot < _matrix->size() - 1; ++idxPivot) {
         this->swapPivotColumn(matR, idxPivot);
         MatrixSquare matHouseholder = this->calculateHouseholderSubMatrix(matR, idxPivot);
         matQAux = matHouseholder.multiplyByBiggerMatrix(matQAux, SubMatrixPos::lower);
         matR = matHouseholder.multiplyByBiggerMatrix(matR, SubMatrixPos::lower);
      }
      for (int i = 0; i < _matrix->size(); ++i) {
         if (!pmat::utils::isZero(matR(i, i)))
            _rank++;
         for (int j = 0; j < _matrix->size(); ++j) {
            _matQ.setValue(matQAux(j, i), i, j);
            if (j >= i)
               _matR.setValue(matR(i, j), i, j);
         }
      }

      _calculated = true;
   }
}

const pmat::MatrixSquare &pmat::DecompositionPQR::matP() {
   this->calculate();
   return _matP;
}

const pmat::MatrixSquare &pmat::DecompositionPQR::matQ() {
   this->calculate();
   return _matQ;
}

const pmat::MatrixUpperTriangular &pmat::DecompositionPQR::matR() {
   this->calculate();
   return _matR;
}

const int &pmat::DecompositionPQR::rank() {
   this->calculate();
   return _rank;
}

bool pmat::DecompositionPQR::isInvertible() {
   this->calculate();
   return _rank == _matrix->size();
}

pmat::MatrixSquare pmat::DecompositionPQR::inverse() {
   if (!this->isInvertible())
      throw std::logic_error(messages::MATRIX_SINGULAR);

   MatrixUpperTriangular invR(_matrix->size());
   MatrixTriangular::findInverseByBackSubstitution(_matR, invR);

   _matQ.transpose();
   MatrixSquare resp{invR * _matQ};
   _matQ.transpose();

   /**
    * Recovering adequate positions by swapping rows in reverse order of the swapped columns
    */
   for (int i = 1; i <= _swappedColumns.size(); ++i) {
      auto &swappedColumn = _swappedColumns[_swappedColumns.size() - i];
      resp.swapRows(swappedColumn.first, swappedColumn.second);
   }

   return resp;
}

pmat::DecompositionPQR::DecompositionPQR(const MatrixSquare &matrix)
    : _matrix{&matrix}, _matP{matrix.size()}, _matQ{matrix.size()}, _matR{matrix.size()} {
   for (int j = 0; j < matrix.size(); j++)
      _matP.setValue(pmat::utils::ONE, j, j);
}
