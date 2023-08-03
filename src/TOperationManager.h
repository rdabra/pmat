#ifndef TOPERATIONMANAGER_H
#define TOPERATIONMANAGER_H
#include <mutex>
#pragma once

#include "Matrix.h"
#include <utility>

namespace pmat {

class TOperationManager {
   private:
      const Matrix *_operandFirst{nullptr};
      const Matrix *_operandSecond{nullptr};
      Matrix _result{};
      std::mutex mtx;

   public:
      TOperationManager(const Matrix &operandFirst, const Matrix &operandSecond, Matrix &result)
          : _operandFirst{&operandFirst}, _operandSecond{&operandSecond} {}
      TOperationManager(const TOperationManager &) = delete;
      TOperationManager(TOperationManager &&) = delete;
      TOperationManager &operator=(const TOperationManager &) = delete;
      TOperationManager &operator=(TOperationManager &&) = delete;
      ~TOperationManager() = default;

      [[nodiscard]] const Matrix &operandFirst() const { return *_operandFirst; }
      [[nodiscard]] const Matrix &operandSecond() const { return *_operandSecond; }
      void setValueResult(unsigned row, unsigned column);
};

} // namespace pmat

#endif