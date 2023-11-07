#ifndef LLINEAROLS_GD_H
#define LLINEAROLS_GD_H
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
class LLinearOLS_GD : public pmat::LLearningModel {
   private:
      pmat::Matrix _gdCoeffs;
      double _tolerance{0.0001};
      bool _gdCalculated{false};
      int _nIterations{0};
      int _maxIterations{5000};
      double _gdCorrTrainData{0};
      double _gdCorrTestData{0};

      void calcSolution() override;

   public:
      LLinearOLS_GD(const pmat::LAnalyticsBaseTable &table) : pmat::LLearningModel{table} {}

      /**
       * @brief Calculates the Linear Regression coefficient matrix via the Gradient Descent
       * Method (iterative)
       * @details At every iteration the learning rate is calculated according to the
       * Barzilai-Borwein method. Default tolerance is 0.0001
       * @return const pmat::Matrix&
       */
      [[nodiscard]] const pmat::Matrix &coefficients();

      /**
       * @brief Returns the number of iterations of the last Gradient Descent execution
       *
       * @return const int&
       */
      [[nodiscard]] const int &nIterations() const { return _nIterations; }

      /**
       * @brief Returns the specified tolerance
       *
       * @return const double&
       */
      [[nodiscard]] const double &tolerance() const { return _tolerance; }

      /**
       * @brief Sets the tolerance
       *
       * @param tolerance
       */
      void setTolerance(const double &tolerance);

      /**
       * @brief Returns the maximum number of iterations allowed for the Gradient Descent. Default
       * is 5000.
       *
       * @return const int&
       */
      [[nodiscard]] const int &maxIterations() const { return _maxIterations; }

      /**
       * @brief Specifies the maximum number of iterations allowed for the Gradient Descent
       *
       * @param maxIterations
       */
      void setMaxIterations(int maxIterations) { _maxIterations = maxIterations; }

      [[nodiscard]] pmat::Vector predict(const pmat::Vector &qery) override;
};

} // namespace pmat

#endif