#ifndef TOPERATIONPERFORMER_H
#define TOPERATIONPERFORMER_H

#pragma once

#include "TOperationManager.h"

namespace pmat {

class TOperationPerformer {
   private:
      const TOperationManager *_manager{nullptr};
      const Matrix *_result{nullptr};
      bool _idle{true};

   public:
      TOperationPerformer(const TOperationManager &manager, const Matrix &result)
          : _manager{&manager}, _result{&result} {}
      TOperationPerformer(const TOperationPerformer &) = default;
      TOperationPerformer(TOperationPerformer &&) = default;
      TOperationPerformer &operator=(const TOperationPerformer &) = default;
      TOperationPerformer &operator=(TOperationPerformer &&) = default;
      ~TOperationPerformer();

      void multiply(unsigned row, unsigned column);
};

} // namespace pmat

#endif