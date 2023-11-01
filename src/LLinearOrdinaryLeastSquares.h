#ifndef LEASTSQUARES_H
#define LEASTSQUARES_H
#pragma once

#include "LAnalyticsBaseTable.h"
#include "Matrix.h"
#include "Vector.h"

namespace pmat {

/**
 * @brief Calculates Linear Regression coefficients via the Ordinary Least Squares Method
 *
 */
class LLinearOrdinaryLeastSquares {
   private:
      const pmat::Matrix *_trainFeature{nullptr};
      const pmat::Matrix *_trainTarget{nullptr};
      const pmat::Matrix *_testFeature{nullptr};
      const pmat::Matrix *_testTarget{nullptr};
      pmat::Matrix _analyticCoeffs;
      pmat::Matrix _gdCoeffs;
      double _tolerance{0.0001};
      bool _analyticCalculated{false};
      bool _gdCalculated{false};
      int _nIterations{0};
      int _maxIterations{5000};
      double _analyticCorrTrainData{0};
      double _analyticCorrTestData{0};
      double _gdCorrTrainData{0};
      double _gdCorrTestData{0};

      void calcAnalyticSolution();
      void calcGdSolution();
      double calcCorrCoeffs(const pmat::Matrix feature, const pmat::Matrix target,
                            const pmat::Matrix &coeffs);

   public:
      LLinearOrdinaryLeastSquares(const pmat::LAnalyticsBaseTable &table)
          : _trainFeature{&table.featureTrainingData()}, _trainTarget{&table.targetTrainingData()},
            _testFeature{&table.featureTestData()}, _testTarget{&table.targetTestData()} {}

      /**
       * @brief Calculates the Linear Regression coefficient matrix analytically
       *
       * @return const pmat::Matrix&
       */
      [[nodiscard]] const pmat::Matrix &analyticCoefficients();

      /**
       * @brief Calculates the Linear Regression coefficient matrix via the Gradient Descent
       * Method (iterative)
       * @details At every iteration the learning rate is calculated according to the
       * Barzilai-Borwein method. Default tolerance is 0.0001
       * @return const pmat::Matrix&
       */
      [[nodiscard]] const pmat::Matrix &gradientDescentCoefficients();

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
       * @brief Returns the correlation coefficient of the analytic solution relative to training
       * data
       *
       * @return const double&
       */
      [[nodiscard]] const double &analyticTrainingCorrelation();

      /**
       * @brief Returns the correlation coefficient of the analytic solution relative to test
       * data
       *
       * @return const double&
       */
      [[nodiscard]] const double &analyticTestCorrelation();

      /**
       * @brief Returns the correlation coefficient of the Gradient Descent solution relative to
       * training data
       *
       * @return const double&
       */
      [[nodiscard]] const double &gradientDescentTrainingCorrelation();

      /**
       * @brief Returns the correlation coefficient of the Gradient Descent solution relative to
       * test data
       *
       * @return const double&
       */
      [[nodiscard]] const double &gradientDescentTestCorrelation();

      /**
       * @brief Returns the target of the specified feature calculated by the analytic solution
       *
       * @param feature
       * @return pmat::Vector
       */
      [[nodiscard]] pmat::Vector analyticTargetOf(const pmat::Vector &feature);

      /**
       * @brief Returns the target of the specified feature calculated by the Gradient Descent
       * solution
       *
       * @param feature
       * @return pmat::Vector
       */
      [[nodiscard]] pmat::Vector gradientDescentTargetOf(const pmat::Vector &feature);

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