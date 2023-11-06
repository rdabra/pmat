#ifndef LNEARESTNEIGHBOR_H
#define LNEARESTNEIGHBOR_H
#pragma once

#include "LAnalyticsBaseTable.h"
#include "Matrix.h"
#include <utility>

namespace pmat {

class LLearningModel {
   protected:
      const pmat::LAnalyticsBaseTable *_table;

      virtual void calcSolution() = 0;

      [[nodiscard]] virtual inline double targDistance(const pmat::Vector &v1,
                                                       const pmat::Vector &v2) {
         return _table->targetType() == pmat::DATA_TYPE::CONTINUOUS ? v1.euclideanDistantFrom(v2)
                                                                    : v1.hammingDistantFrom(v2);
      };

      [[nodiscard]] virtual inline double featDistance(const pmat::Vector &v1,
                                                       const pmat::Vector &v2) {
         return _table->featureType() == pmat::DATA_TYPE::CONTINUOUS ? v1.euclideanDistantFrom(v2)
                                                                     : v1.hammingDistantFrom(v2);
      };

      bool _DCCalculated{false};
      double _trainDC{-1};
      double _testDC{-1};
      [[nodiscard]] double calcDeterminationCoeff(const pmat::Matrix feature,
                                                  const pmat::Matrix target);
      bool _RMSECalculated{false};
      double _trainRMSE{-1};
      double _testRMSE{-1};
      [[nodiscard]] double calcRootMeanSquareError(const pmat::Matrix feature,
                                                   const pmat::Matrix target);

      void setStatusFlags(bool status);

   public:
      LLearningModel(const LLearningModel &) = default;
      LLearningModel(LLearningModel &&) = delete;
      LLearningModel &operator=(const LLearningModel &) = default;
      LLearningModel &operator=(LLearningModel &&) = default;
      virtual ~LLearningModel() = default;

      LLearningModel(const pmat::LAnalyticsBaseTable &table) : _table{&table} {}

      [[nodiscard]] virtual std::pair<double, double> determinationCoefficients();
      [[nodiscard]] virtual std::pair<double, double> rootMeanSquareErrors();

      /**
       * @brief Returns the target of the specified feature
       *
       * @param query
       * @return pmat::Vector
       */
      [[nodiscard]] virtual pmat::Vector targetOf(const pmat::Vector &query) = 0;

      [[nodiscard]] const pmat::LAnalyticsBaseTable &table() const { return *_table; }
};

} // namespace pmat

#endif