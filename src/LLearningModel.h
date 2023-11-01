#ifndef LNEARESTNEIGHBOR_H
#define LNEARESTNEIGHBOR_H
#pragma once

#include "LAnalyticsBaseTable.h"
#include "Matrix.h"

namespace pmat {

class LLearningModel {
   private:
      const pmat::Matrix *_trainFeature{nullptr};
      const pmat::Matrix *_trainTarget{nullptr};
      const pmat::Matrix *_testFeature{nullptr};
      const pmat::Matrix *_testTarget{nullptr};

   public:
      LLearningModel(const pmat::LAnalyticsBaseTable &table)
          : _trainFeature{&table.featureTrainingData()}, _trainTarget{&table.targetTrainingData()},
            _testFeature{&table.featureTestData()}, _testTarget{&table.targetTestData()} {}
};

} // namespace pmat

#endif