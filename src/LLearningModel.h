#ifndef LNEARESTNEIGHBOR_H
#define LNEARESTNEIGHBOR_H
#pragma once

#include "LAnalyticsBaseTable.h"
#include "Matrix.h"

namespace pmat {

class LLearningModel {
   protected:
      const pmat::Matrix *_trainFeature{nullptr};
      const pmat::Matrix *_trainTarget{nullptr};
      const pmat::Matrix *_testFeature{nullptr};
      const pmat::Matrix *_testTarget{nullptr};
      double _trainCorrelation{-1};
      double _testCorrelation{-1};
      [[nodiscard]] virtual inline double distance(const pmat::Vector &v1,
                                                   const pmat::Vector &v2) = 0;
      [[nodiscard]] double calcCorrCoeffs(const pmat::Matrix feature, const pmat::Matrix target);

   public:
      LLearningModel(const LLearningModel &) = default;
      LLearningModel(LLearningModel &&) = delete;
      LLearningModel &operator=(const LLearningModel &) = default;
      LLearningModel &operator=(LLearningModel &&) = default;
      virtual ~LLearningModel() = default;

      LLearningModel(const pmat::LAnalyticsBaseTable &table)
          : _trainFeature{&table.featureTrainingData()}, _trainTarget{&table.targetTrainingData()},
            _testFeature{&table.featureTestData()}, _testTarget{&table.targetTestData()} {}

      [[nodiscard]] virtual const double &trainingCorrelation() = 0;
      [[nodiscard]] virtual const double &testCorrelation() = 0;
      [[nodiscard]] virtual pmat::Vector targetOf(const pmat::Vector &feature) = 0;
};

} // namespace pmat

#endif