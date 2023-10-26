#include "TMultiplicationManager.h"
#include "Messages.h"
#include <future>
#include <memory>
#include <mutex>

pmat::TMultiplicationManager::TMultiplicationManager(const Matrix &operandFirst,
                                                     const Matrix &operandSecond, Matrix &result)
    : _operandFirst{&operandFirst}, _operandSecond{&operandSecond}, _result{&result} {
   if (operandSecond.rowSize() != operandFirst.columnSize() ||
       operandSecond.columnSize() != result.columnSize() ||
       operandFirst.rowSize() != result.rowSize())
      throw std::invalid_argument(pmat::messages::NONCOMPT_SIZE_ARG);
}

void pmat::TMultiplicationManager::setResultValue(const double &value, const int &row,
                                                  const int &column) {
   std::lock_guard<std::mutex> lg(mtx1);
   _result->assign(value, row, column);
}

bool pmat::TMultiplicationManager::getNextRowColumn(int id) {
   std::lock_guard<std::mutex> lg(mtx2);
   if (_lastRow < _operandFirst->rowSize()) {
      _performers[id]->setRowColumn(_lastRow, _lastColumn);
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
   for (int i{0}; i < nThreads; i++) {
      _performers.emplace_back(std::make_shared<TMultiplicationPerformer>(i, *this));
      futures.emplace_back(std::async(&TMultiplicationPerformer::start, _performers.back()));
   }
   for (auto &ftr : futures)
      ftr.wait();
}
