#include "LWeightedNN.h"
#include "pmatUtils.h"
#include <algorithm>
#include <utility>
#include <vector>

std::pair<double, double> pmat::LWeightedNN::relativeRootMeanSquareErrors() {
   if (!_RMSECalculated) {
      _trainRMSE = pmat::utils::ONE;
      if (_table->featureTestData().rowSize() > 0)
         _testRMSE =
             this->calcRootMeanSquareError(_table->featureTestData(), _table->targetTestData());
      _RMSECalculated = true;
   }
   auto res = std::make_pair(_trainRMSE, _testRMSE);

   return res;
}

pmat::Vector pmat::LWeightedNN::predict(const pmat::Vector &query) {
   auto featTrainData = _table->featureTrainingData();
   auto targTrainData = _table->targetTrainingData();

   if (featTrainData.rowSize() >= _kNeighbors) {
      std::vector<std::pair<int, int>> distances;
      for (int i{0}; i < featTrainData.rowSize(); i++)
         distances.emplace_back(i, this->featDistance(query, featTrainData.rowToVector(i)));
      std::sort(distances.begin(), distances.end(),
                [](std::pair<int, int> left, std::pair<int, int> right) {
                   return left.second < right.second;
                });

      if (!pmat::utils::areEqual(distances[0].second, pmat::utils::ZERO)) {
         double sWeight{pmat::utils::ZERO};
         pmat::Vector sTarget{_table->targetTrainingData().columnSize()};
         for (int i{0}; i < _kNeighbors; i++) {
            double weight{pmat::utils::inv(distances[i].second)};
            sTarget = sTarget + (targTrainData.rowToVector(distances[i].first) * weight);
            sWeight += weight;
         }
         pmat::Vector resp{sTarget * pmat::utils::inv(sWeight)};
         return resp;
      } else {
         pmat::Vector resp{targTrainData.rowToVector(distances[0].first)};
         return resp;
      }
   } else
      throw std::logic_error("Insufficent data.");
}

void pmat::LWeightedNN::setKNeighbors(int kNeighbors) {
   _kNeighbors = kNeighbors;
   this->setStatusFlags(false);
}
