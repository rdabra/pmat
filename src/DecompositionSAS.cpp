#include "DecompositionSAS.h"
#include "utils.h"

void pmat::DecompositionSAS::calculate() {
   if (!_calculated) {
      for (int i = 0; i < _matrix->size(); ++i)
         for (int j = 0; j <= i; ++j) {
            _matS.setValue(pmat::utils::ONE_HALF * ((*_matrix)(i, j) + (*_matrix)(j, i)), i, j);
            _matAS.setValue(pmat::utils::ONE_HALF * ((*_matrix)(i, j) - (*_matrix)(j, i)), i, j);
         }
      _calculated = true;
   }
}

pmat::DecompositionSAS::DecompositionSAS(const MatrixSquare &matrix)
    : _matrix{&matrix}, _matAS{matrix.size()}, _matS{matrix.size()} {
}

const pmat::MatrixSymmetric &pmat::DecompositionSAS::matS() {
   this->calculate();
   return _matS;
}

const pmat::MatrixSkewSymmetric &pmat::DecompositionSAS::matAS() {
   this->calculate();
   return _matAS;
}
