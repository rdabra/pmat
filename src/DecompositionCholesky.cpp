#include "DecompositionCholesky.h"
#include "MatrixSymmetric.h"
#include "Messages.h"
#include "pmatUtils.h"
#include <cmath>
#include <stdexcept>

void pmat::DecompositionCholesky::calculate() {
   if (!_calculated) {
      for (int i = 0; i < _matrix->size(); ++i) {
         double diag = (*_matrix)(i, i);
         for (int k = 0; k < i; ++k)
            diag -= (_factor)(i, k) * (_factor)(i, k);
         if (pmat::utils::isZero(diag) || diag < pmat::utils::ZERO) {
            throw std::logic_error(messages::MATRIX_NOT_L);
         }
         _factor.assign(std::sqrt(diag), i, i);
         for (int j = i + 1; j < _matrix->size(); ++j) {
            double aux = (*_matrix)(i, j);
            for (int k = 0; k < i; ++k)
               aux -= (_factor)(i, k) * (_factor)(j, k);
            _factor.assign(aux / (_factor)(i, i), j, i);
         }
      }
      _calculated = true;
   }
}

pmat::DecompositionCholesky::DecompositionCholesky(const MatrixSymmetric &matrix)
    : _matrix{&matrix}, _factor{matrix.size()}, _plu{matrix.decomposeToPLU()} {
}

const pmat::MatrixLowerTriangular &pmat::DecompositionCholesky::choleskyFactor() {
   this->calculate();
   return _factor;
}

double pmat::DecompositionCholesky::determinant() {
   if (this->isPositiveDefinite()) {
      const double resp = _factor.determinant();
      return resp * resp;
   }

   return _plu.determinant();
}

bool pmat::DecompositionCholesky::isInvertible() {
   if (this->isPositiveDefinite())
      for (int i = 0; i < _matrix->size(); i++)
         if (pmat::utils::isZero(_factor(i, i)))
            return false;

   return _plu.isInvertible();
}

pmat::MatrixSquare pmat::DecompositionCholesky::inverse() {
   if (this->isPositiveDefinite()) {
      return _factor.getTranspose().inverse() * _factor.inverse();
   }
   return _plu.inverse();
}

pmat::Vector pmat::DecompositionCholesky::linearSolve(const Vector &rhs) {
   if (rhs.size() != _matrix->size())
      throw std::invalid_argument(messages::NONCOMPT_SIZE_ARG);

   if (this->isPositiveDefinite()) {

      if (!this->isInvertible())
         throw std::logic_error(messages::MATRIX_SINGULAR);

      const Vector resp1(_factor.linearSolve(rhs));

      return _factor.getTranspose().linearSolve(resp1);
   }

   return _plu.linearSolve(rhs);
}

bool pmat::DecompositionCholesky::isPositiveDefinite() {
   try {
      this->calculate();
      return true;
   } catch (...) {
      return false;
   }
}

pmat::MatrixSymmetric pmat::DecompositionCholesky::inverseAsSymmetric() {
   MatrixSymmetric res{_matrix->size()};
   MatrixSquare aux{this->inverse()};
   for (int i = 0; i < _matrix->size(); ++i)
      for (int j = 0; j <= i; ++j)
         res.assign(aux(i, j), i, j);

   return res;
}
