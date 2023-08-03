#include "TOperationManager.h"
#include <mutex>

void pmat::TOperationManager::setValueResult(const double &value, const unsigned &row,
                                             const unsigned &column) {
   std::lock_guard<std::mutex> lg(mtx);
   _result.setValue(value, row, column);
}
