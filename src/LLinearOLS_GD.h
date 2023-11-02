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

      void calcGdSolution();

      [[nodiscard]] inline double distance(const pmat::Vector &v1,
                                           const pmat::Vector &v2) override {
         return v1.euclideanDistantFrom(v2);
      };

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
       * @brief Returns the correlation coefficient of the Gradient Descent solution relative to
       * training data
       *
       * @return const double&
       */
      [[nodiscard]] const double &trainingCorrelation() override;

      /**
       * @brief Returns the correlation coefficient of the Gradient Descent solution relative to
       * test data
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
};

} // namespace pmat

#endif