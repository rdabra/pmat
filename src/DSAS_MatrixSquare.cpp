#include "DSAS_MatrixSquare.h"
#include "utils.h"

void pmat::DSAS_MatrixSquare::calculate() {
   if (!_calculated) {
      for (unsigned i = 0; i < _matrix->size(); ++i)
         for (unsigned j = 0; j <= i; ++j) {
            _matS.setValue(pmat::utils::ONE_HALF * ((*_matrix)(i, j) + (*_matrix)(j, i)), i, j);
            _matAS.setValue(pmat::utils::ONE_HALF * ((*_matrix)(i, j) - (*_matrix)(j, i)), i, j);
         }
      _calculated = true;
   }
}

pmat::DSAS_MatrixSquare::DSAS_MatrixSquare(const MatrixSquare &matrix)
    : _matrix{&matrix}, _matAS{matrix.size()}, _matS{matrix.size()} {
}

const pmat::MatrixSymmetric &pmat::DSAS_MatrixSquare::matS() {
   this->calculate();
   return _matS;
}

const pmat::MatrixSkewSymmetric &pmat::DSAS_MatrixSquare::matAS() {
   this->calculate();
   return _matAS;
}
