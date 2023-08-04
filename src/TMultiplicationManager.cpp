#include "TMultiplicationManager.h"
#include <future>
#include <mutex>

void pmat::TMultiplicationManager::setResultValue(const double &value, const unsigned &row,
                                                  const unsigned &column) {
   std::lock_guard<std::mutex> lg(mtx1);
   _result->setValue(value, row, column);
}

bool pmat::TMultiplicationManager::getNextRowColumn(unsigned id) {
   std::lock_guard<std::mutex> lg(mtx2);
   if (_lastRow < _operandFirst->rowSize()) {
      _performers[id].setRowColumn(_lastRow, _lastColumn);
      if (_lastColumn < _operandSecond->columnSize() - 1) {
         _lastColumn++;
      } else {
         _lastRow++;
         _lastColumn = 0;
      }
      return true;
   }

   return false;
}

void pmat::TMultiplicationManager::multiply(int nThreads) {
   std::vector<std::future<void>> futures;
   for (unsigned i{0}; i < nThreads; i++) {
      _performers.emplace_back(i, *this);
      futures.emplace_back(
          std::async(std::launch::async, &TMultiplicationPerformer::start, &_performers.back()));
   }
   for (auto &ftr : futures)
      ftr.wait();
}
