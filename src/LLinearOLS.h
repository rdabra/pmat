#ifndef LLINEAROLS_H
#define LLINEAROLS_H
#pragma once

#include "LAnalyticsBaseTable.h"
#include "LLearningModel.h"
#include "Matrix.h"
#include "Vector.h"

namespace pmat {

/**
 * @brief Calculates Linear Regression coefficients via the Ordinary Least Squares Method
 *
 */
class LLinearOLS : public pmat::LLearningModel {
   private:
      pmat::Matrix _analyticCoeffs;
      bool _analyticCalculated{false};
      double _analyticCorrTrainData{0};
      double _analyticCorrTestData{0};

      void calcAnalyticSolution();

      [[nodiscard]] inline double distance(const pmat::Vector &v1,
                                           const pmat::Vector &v2) override {
         return v1.euclideanDistantFrom(v2);
      };

   public:
      LLinearOLS(const pmat::LAnalyticsBaseTable &table) : pmat::LLearningModel{table} {}

      /**
       * @brief Calculates the Linear Regression coefficient matrix analytically
       *
       * @return const pmat::Matrix&
       */
      [[nodiscard]] const pmat::Matrix &coefficients();

      /**
       * @brief Returns the correlation coefficient of the analytic solution relative to training
       * data
       *
       * @return const double&
       */
      [[nodiscard]] const double &trainingCorrelation() override;

      /**
       * @brief Returns the correlation coefficient of the analytic solution relative to test
       * data
       *
       * @return const double&
       */
      [[nodiscard]] const double &testCorrelation() override;

      /**
       * @brief Returns the target of the specified feature calculated by the analytic solution
       *
       * @param feature
       * @return pmat::Vector
       */
      [[nodiscard]] pmat::Vector targetOf(const pmat::Vector &feature) override;
};

} // namespace pmat

#endif