#include "LWeightedNN.h"
#include "pmatUtils.h"
#include <algorithm>
#include <utility>
#include <vector>

std::pair<double, double> pmat::LWeightedNN::distanceRelativeRootMeanSquareErrors() {
   double train = pmat::utils::ZERO;
   double test{};
   if (_table->featureTestData().rowSize() > 0)
      test = this->calcRootMeanSquareError(_table->featureTestData(), _table->targetTestData());
   auto res = std::make_pair(train, test);

   return res;
}

std::pair<double, double> pmat::LWeightedNN::distanceDeterminationCoefficients() {
   double train = pmat::utils::ONE;
   double test{};
   if (_table->featureTestData().rowSize() > 0)
      test = this->calcDeterminationCoeff(_table->featureTestData(), _table->targetTestData());
   auto res = std::make_pair(train, test);

   return res;
}

std::pair<double, double> pmat::LWeightedNN::distanceMaximumRelativeScalarError() {
   double train = pmat::utils::ZERO;
   double test{};
   if (_table->featureTestData().rowSize() > 0)
      test = this->calcMaxRelativeError(_table->featureTestData(), _table->targetTestData());
   auto res = std::make_pair(train, test);

   return res;
}

std::pair<pmat::Vector, pmat::Vector> pmat::LWeightedNN::determinationCoefficients() {
   pmat::Vector train{_table->featureTrainingData().columnSize()};
   train.fillWith(pmat::utils::ONE);
   pmat::Vector test{};
   if (_table->featureTestData().rowSize() > 0)
      test = this->calcVetDeterminationCoeff(_table->featureTestData(), _table->targetTestData());
   auto res = std::make_pair(train, test);

   return res;
}

std::pair<pmat::Vector, pmat::Vector> pmat::LWeightedNN::relativeRootMeanSquareErrors() {
   pmat::Vector train{_table->featureTrainingData().columnSize()};
   train.fillWith(pmat::utils::ZERO);
   pmat::Vector test{};
   if (_table->featureTestData().rowSize() > 0)
      test = this->calcVetRootMeanSquareError(_table->featureTestData(), _table->targetTestData());
   auto res = std::make_pair(train, test);

   return res;
}

std::pair<pmat::Vector, pmat::Vector> pmat::LWeightedNN::maximumRelativeError() {
   pmat::Vector train{_table->featureTrainingData().columnSize()};
   train.fillWith(pmat::utils::ZERO);
   pmat::Vector test{};
   if (_table->featureTestData().rowSize() > 0)
      test = this->calcVetMaxRelativeError(_table->featureTestData(), _table->targetTestData());
   auto res = std::make_pair(train, test);

   return res;
}

std::pair<pmat::Vector, pmat::Vector> pmat::LWeightedNN::meanRelativeError() {
   pmat::Vector train{_table->featureTrainingData().columnSize()};
   train.fillWith(pmat::utils::ZERO);
   pmat::Vector test{};
   if (_table->featureTestData().rowSize() > 0)
      test = this->calcVetMeanRelativeError(_table->featureTestData(), _table->targetTestData());
   auto res = std::make_pair(train, test);

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
}
