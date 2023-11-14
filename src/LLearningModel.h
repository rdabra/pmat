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

      [[nodiscard]] double calcDeterminationCoeff(const pmat::Matrix feature,
                                                  const pmat::Matrix target);

      [[nodiscard]] pmat::Vector calcVetDeterminationCoeff(const pmat::Matrix feature,
                                                           const pmat::Matrix target);

      [[nodiscard]] double calcRootMeanSquareError(const pmat::Matrix feature,
                                                   const pmat::Matrix target);

      [[nodiscard]] pmat::Vector calcVetRootMeanSquareError(const pmat::Matrix feature,
                                                            const pmat::Matrix target);

      [[nodiscard]] double calcMaxRelativeError(const pmat::Matrix feature,
                                                const pmat::Matrix target);

      [[nodiscard]] pmat::Vector calcVetMaxRelativeError(const pmat::Matrix feature,
                                                         const pmat::Matrix target);

      double calcMeanRelativeError(const pmat::Matrix feature, const pmat::Matrix target);

      pmat::Vector calcVetMeanRelativeError(const pmat::Matrix feature, const pmat::Matrix target);

   public:
      LLearningModel(const LLearningModel &) = default;
      LLearningModel(LLearningModel &&) = delete;
      LLearningModel &operator=(const LLearningModel &) = default;
      LLearningModel &operator=(LLearningModel &&) = default;
      virtual ~LLearningModel() = default;

      LLearningModel(const pmat::LAnalyticsBaseTable &table) : _table{&table} {}

      /**
       * @brief Returns respectively the training and test Determination
       * Coefficients for each target dimension
       *
       * @return std::pair<pmat::Vector, pmat::Vector>
       */
      [[nodiscard]] virtual std::pair<pmat::Vector, pmat::Vector> determinationCoefficients();

      /**
       * @brief Returns respectively the training and test Determination Coefficients based on
       * vector distances
       *
       * @return std::pair<double, double>
       */
      [[nodiscard]] virtual std::pair<double, double> distanceDeterminationCoefficients();

      /**
       * @brief Returns respectively the training and test Relative Root Average Mean Square Errors
       * for each target dimension
       *
       * @return std::pair<pmat::Vector, pmat::Vector>
       */
      [[nodiscard]] virtual std::pair<pmat::Vector, pmat::Vector> relativeRootMeanSquareErrors();

      /**
       * @brief Returns respectively the training and test Relative Root Average Mean Square Errors
       *
       * @return std::pair<double, double>
       */
      [[nodiscard]] virtual std::pair<double, double> distanceRelativeRootMeanSquareErrors();

      /**
       * @brief Returns respectively the training and test Maximum Relative Error based on
       * vector distances
       *
       * @return std::pair<double, double>
       */
      [[nodiscard]] virtual std::pair<double, double> distanceMaximumRelativeError();

      /**
       * @brief Returns respectively the training and test Maximum Relative Error for each
       * target dimension
       *
       * @return std::pair<pmat::Vector, pmat::Vector>
       */
      [[nodiscard]] virtual std::pair<pmat::Vector, pmat::Vector> maximumRelativeError();

      /**
       * @brief Returns respectively the training and test Mean Relative Error for each
       * target dimension
       *
       * @return std::pair<pmat::Vector, pmat::Vector>
       */
      [[nodiscard]] virtual std::pair<pmat::Vector, pmat::Vector> meanRelativeError();

      /**
       * @brief Returns respectively the training and test Mean Relative Error based on vector
       * distances
       *
       * @return std::pair<double, double>
       */
      [[nodiscard]] virtual std::pair<double, double> distanceMeanRelativeError();

      /**
       * @brief Returns the model prediction of the specified query
       *
       * @param query
       * @return pmat::Vector
       */
      [[nodiscard]] virtual pmat::Vector predict(const pmat::Vector &query) = 0;

      /**
       * @brief Returns the model predictions to each row of the specified query
       *
       * @param query has a query in each row
       * @return pmat::Matrix shows prediction rows correspondent to query rows
       */
      [[nodiscard]] virtual pmat::Matrix predict(const pmat::Matrix &query);

      /**
       * @brief Returns the predictions of the training features
       *
       * @return pmat::Matrix
       */
      [[nodiscard]] virtual pmat::Matrix predictTraining();

      /**
       * @brief Returns the predictions of the test features
       *
       * @return pmat::Matrix
       */
      [[nodiscard]] virtual pmat::Matrix predictTest();

      /**
       * @brief Returns the Analytics Base Table related to this model
       *
       * @return const pmat::LAnalyticsBaseTable&
       */
      [[nodiscard]] const pmat::LAnalyticsBaseTable &table() const { return *_table; }
};

} // namespace pmat

#endif