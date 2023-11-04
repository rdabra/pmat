#ifndef LLINEAROLS_H
#define LLINEAROLS_H
#pragma once

#include "LAnalyticsBaseTable.h"
#include "LLearningModel.h"
#include "Matrix.h"
#include "Vector.h"

namespace pmat {

/**
 * @brief Calculates Linear Regression coefficients via the Ordinary Least Squares Method (OLS)
 *
 */
class LLinearOLS : public pmat::LLearningModel {
   private:
      pmat::Matrix _analyticCoeffs;

      bool _analyticCalculated{false};
      void calcSolution() override;

   public:
      LLinearOLS(const pmat::LAnalyticsBaseTable &table) : pmat::LLearningModel{table} {}

      /**
       * @brief Calculates the Linear Regression coefficient matrix analytically
       *
       * @return const pmat::Matrix&
       */
      [[nodiscard]] const pmat::Matrix &coefficients();

      [[nodiscard]] pmat::Vector targetOf(const pmat::Vector &feature) override;
};

} // namespace pmat

#endif