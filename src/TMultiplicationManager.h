#ifndef TOPERATIONMANAGER_H
#define TOPERATIONMANAGER_H
#include <memory>
#include <mutex>
#pragma once

#include "Matrix.h"
#include "TMultiplicationPerformer.h"
#include <utility>

namespace pmat {

class TMultiplicationManager {
   private:
      const Matrix *_operandFirst{nullptr};
      const Matrix *_operandSecond{nullptr};
      Matrix *_result{nullptr};
      std::mutex mtx1, mtx2;
      unsigned _lastRow{0};
      unsigned _lastColumn{0};
      std::vector<std::shared_ptr<TMultiplicationPerformer>> _performers{};

   public:
      TMultiplicationManager(const Matrix &operandFirst, const Matrix &operandSecond,
                             Matrix &result);
      TMultiplicationManager(const TMultiplicationManager &) = delete;
      TMultiplicationManager(TMultiplicationManager &&) = delete;
      TMultiplicationManager &operator=(const TMultiplicationManager &) = delete;
      TMultiplicationManager &operator=(TMultiplicationManager &&) = delete;
      ~TMultiplicationManager() = default;

      [[nodiscard]] const Matrix &operandFirst() const { return *_operandFirst; }
      [[nodiscard]] const Matrix &operandSecond() const { return *_operandSecond; }
      void setResultValue(const double &value, const unsigned &row, const unsigned &column);
      bool getNextRowColumn(unsigned id);
      void multiply(int nThreads);
};

} // namespace pmat

#endif