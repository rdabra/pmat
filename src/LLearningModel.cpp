#include "LLearningModel.h"
#include "pmatUtils.h"
#include <utility>

double pmat::LLearningModel::calcDeterminationCoeff(const pmat::Matrix feature,
                                                    const pmat::Matrix target) {

   std::vector<pmat::Vector> features{feature.rowsToVectors()};
   std::vector<pmat::Vector> targets{target.rowsToVectors()};

   pmat::Vector mean{targets[0]};
   for (int i{1}; i < targets.size(); i++)
      mean = mean + targets[i];
   mean.multiplyBy(pmat::utils::inv((double)targets.size()));

   double distancesFromMean{pmat::utils::ZERO};
   double distancesFromEstimation{pmat::utils::ZERO};
   for (int i{0}; i < targets.size(); i++) {
      double distFM{this->targDistance(mean, targets[i])};
      distancesFromMean += distFM * distFM;
      double distFE{this->targDistance(targets[i], this->predict(features[i]))};
      distancesFromEstimation += distFE * distFE;
   }

   return pmat::utils::ONE - (distancesFromEstimation / distancesFromMean);
}

double pmat::LLearningModel::calcRootMeanSquareError(const pmat::Matrix feature,
                                                     const pmat::Matrix target) {

   std::vector<pmat::Vector> features{feature.rowsToVectors()};
   std::vector<pmat::Vector> targets{target.rowsToVectors()};

   double distancesFromEstimation{pmat::utils::ZERO};
   for (int i{0}; i < targets.size(); i++) {
      double distFE{this->targDistance(targets[i], this->predict(features[i]))};
      distancesFromEstimation += distFE * distFE;
   }

   return std::sqrt(distancesFromEstimation / (int)targets.size());
}

void pmat::LLearningModel::setStatusFlags(bool status) {
   _DCCalculated = _RMSECalculated = status;
}

std::pair<double, double> pmat::LLearningModel::determinationCoefficients() {
   if (!_DCCalculated) {
      this->calcSolution();
      _trainDC =
          this->calcDeterminationCoeff(_table->featureTrainingData(), _table->targetTrainingData());
      if (_table->featureTestData().rowSize() > 0)
         _testDC =
             this->calcDeterminationCoeff(_table->featureTestData(), _table->targetTestData());
      _DCCalculated = true;
   }
   auto res = std::make_pair(_trainDC, _testDC);

   return res;
}

std::pair<double, double> pmat::LLearningModel::rootMeanSquareErrors() {
   if (!_RMSECalculated) {
      this->calcSolution();
      _trainRMSE = this->calcRootMeanSquareError(_table->featureTrainingData(),
                                                 _table->targetTrainingData());
      if (_table->featureTestData().rowSize() > 0)
         _testRMSE =
             this->calcRootMeanSquareError(_table->featureTestData(), _table->targetTestData());
      _RMSECalculated = true;
   }
   auto res = std::make_pair(_trainRMSE, _testRMSE);

   return res;
}