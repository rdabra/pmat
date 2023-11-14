#ifndef LWEIGHTEDNN_H
#define LWEIGHTEDNN_H
#pragma once

#include "LAnalyticsBaseTable.h"
#include "LLearningModel.h"

namespace pmat {

class LWeightedNN : public pmat::LLearningModel {
   private:
      int _kNeighbors{0};

      void calcSolution() override{};

      void callCalcCorrelation();

   public:
      LWeightedNN(const pmat::LAnalyticsBaseTable &table, int kNeighbors)
          : pmat::LLearningModel{table}, _kNeighbors{kNeighbors} {}

      [[nodiscard]] std::pair<double, double> distanceRelativeRootMeanSquareErrors() override;

      [[nodiscard]] std::pair<pmat::Vector, pmat::Vector> determinationCoefficients() override;

      [[nodiscard]] std::pair<double, double> distanceDeterminationCoefficients() override;

      [[nodiscard]] std::pair<pmat::Vector, pmat::Vector> relativeRootMeanSquareErrors() override;

      [[nodiscard]] std::pair<double, double> distanceMaximumRelativeError() override;

      [[nodiscard]] std::pair<pmat::Vector, pmat::Vector> maximumRelativeError() override;

      std::pair<pmat::Vector, pmat::Vector> meanRelativeError() override;

      [[nodiscard]] std::pair<double, double> distanceMeanRelativeError() override;

      [[nodiscard]] pmat::Vector predict(const pmat::Vector &query) override;

      /**
       * @brief Returns the number of neighbors to be evaluated
       *
       * @return int
       */
      [[nodiscard]] int kNeighbors() const { return _kNeighbors; }

      /**
       * @brief Specifies the number of neighbors to be evaluated
       *
       * @param kNeighbors
       */
      void setKNeighbors(int kNeighbors);
};

} // namespace pmat
#endif