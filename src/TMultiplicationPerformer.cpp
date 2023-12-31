#include "TMultiplicationPerformer.h"
#include "TMultiplicationManager.h"
#include "pmatUtils.h"

void pmat::TMultiplicationPerformer::start() {
   while (_manager->getNextRowColumn(this->_id)) {
      double res{pmat::utils::ZERO};
      for (int j = 0; j < (*_manager).operandFirst().columnSize(); ++j)
         res += (_manager->operandFirst())(_row, j) * (_manager->operandSecond())(j, _column);
      _manager->setResultValue(res, _row, _column);
   }
}

void pmat::TMultiplicationPerformer::setRowColumn(const int &row, const int &column) {
   _row = row;
   _column = column;
}
