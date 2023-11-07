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

      [[nodiscard]] std::pair<double, double> rootMeanSquareErrors() override;

      [[nodiscard]] pmat::Vector predict(const pmat::Vector &query) override;

      [[nodiscard]] int kNeighbors() const { return _kNeighbors; }

      void setKNeighbors(int kNeighbors);
};

} // namespace pmat
#endif