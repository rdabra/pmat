#include "TOperationPerformer.h"
#include "utils.h"

void pmat::TOperationPerformer::multiply(unsigned row, unsigned column) {
   double s{pmat::utils::ZERO};
   for (unsigned j = 0; j < (*_manager).operandFirst().columnSize(); ++j)
      s += ((*_manager).operandFirst())(row, j) * ((*_manager).operandSecond())(j, column);
   _result->set(sum, _rowA, _columnB);
}
