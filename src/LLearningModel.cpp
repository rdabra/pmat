#include "LLearningModel.h"
#include "pmatUtils.h"
#include <cstdlib>
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

pmat::Vector pmat::LLearningModel::calcVetDeterminationCoeff(const pmat::Matrix feature,
                                                             const pmat::Matrix target) {
   std::vector<pmat::Vector> features{feature.rowsToVectors()};
   std::vector<pmat::Vector> targets{target.rowsToVectors()};

   pmat::Vector mean{targets[0]};
   for (int i{1}; i < targets.size(); i++)
      mean = mean + targets[i];
   mean.multiplyBy(pmat::utils::inv((double)targets.size()));

   pmat::Vector diffsFromMean{target.columnSize()};
   pmat::Vector diffsFromEstimation{target.columnSize()};
   for (int i{0}; i < targets.size(); i++) {
      pmat::Vector diffFM{mean - targets[i]};
      diffsFromMean = diffsFromMean + diffFM.multiplyHadamardBy(diffFM);
      pmat::Vector diffFE{targets[i] - this->predict(features[i])};
      diffsFromEstimation = diffsFromEstimation + diffFE.multiplyHadamardBy(diffFE);
   }

   pmat::Vector resp{target.columnSize()};
   resp.fillWith(pmat::utils::ONE);
   diffsFromMean.invertElements();
   resp = resp - diffsFromEstimation.multiplyHadamardBy(diffsFromMean);

   return resp;
}

double pmat::LLearningModel::calcRootMeanSquareError(const pmat::Matrix feature,
                                                     const pmat::Matrix target) {
   std::vector<pmat::Vector> features{feature.rowsToVectors()};
   std::vector<pmat::Vector> targets{target.rowsToVectors()};
   double distancesFromEstimation{pmat::utils::ZERO};
   pmat::Vector sumPred{target.columnSize()};

   for (int i{0}; i < targets.size(); i++) {
      pmat::Vector pred{this->predict(features[i])};
      double distFE{this->targDistance(pred, targets[i])};
      sumPred = sumPred + pred;
      distancesFromEstimation += distFE * distFE;
   }

   double aux = pmat::utils::inv((int)targets.size());
   double average = this->targDistance(sumPred * aux, pmat::Vector{target.columnSize()});

   return std::sqrt(distancesFromEstimation * aux) / average;
}

pmat::Vector pmat::LLearningModel::calcVetRootMeanSquareError(const pmat::Matrix feature,
                                                              const pmat::Matrix target) {
   std::vector<pmat::Vector> features{feature.rowsToVectors()};
   std::vector<pmat::Vector> targets{target.rowsToVectors()};
   pmat::Vector diffsFromEst{target.columnSize()};
   pmat::Vector sumPred{target.columnSize()};

   for (int i{0}; i < targets.size(); i++) {
      pmat::Vector pred{this->predict(features[i])};
      pmat::Vector distFE{pred - targets[i]};
      sumPred = sumPred + pred;
      diffsFromEst = diffsFromEst + distFE.multiplyHadamardBy(distFE);
   }

   double aux{pmat::utils::inv((int)targets.size())};
   pmat::Vector average{sumPred * aux};
   average.invertElements();
   pmat::Vector resp{diffsFromEst * aux};
   resp.squareRootElements();
   resp = resp.multiplyHadamardBy(average);

   return resp;
}

double pmat::LLearningModel::calcMaxRelativeError(const pmat::Matrix feature,
                                                  const pmat::Matrix target) {
   std::vector<pmat::Vector> features{feature.rowsToVectors()};
   std::vector<pmat::Vector> targets{target.rowsToVectors()};

   double resp{pmat::utils::ZERO};
   pmat::Vector zero{target.columnSize()};
   for (int i{0}; i < targets.size(); i++) {
      pmat::Vector pred{this->predict(features[i])};
      double aux{this->targDistance(pred, targets[i]) / this->targDistance(pred, zero)};
      if (aux > resp)
         resp = aux;
   }
   return resp;
}

pmat::Vector pmat::LLearningModel::calcVetMaxRelativeError(const pmat::Matrix feature,
                                                           const pmat::Matrix target) {
   std::vector<pmat::Vector> features{feature.rowsToVectors()};
   std::vector<pmat::Vector> targets{target.rowsToVectors()};

   pmat::Vector resp{target.columnSize()};
   for (int i{0}; i < targets.size(); i++) {
      pmat::Vector pred{this->predict(features[i])};
      pmat::Vector dif{pred - targets[i]};
      pred.invertElements();

      pmat::Vector aux{dif.multiplyHadamardBy(pred)};
      for (int j{0}; j < target.columnSize(); j++)
         if (std::abs(aux(j)) > resp(j))
            resp(j) = std::abs(aux(j));
   }
   return resp;
}

std::pair<double, double> pmat::LLearningModel::distanceDeterminationCoefficients() {
   this->calcSolution();
   double train =
       this->calcDeterminationCoeff(_table->featureTrainingData(), _table->targetTrainingData());
   double test{};
   if (_table->featureTestData().rowSize() > 0)
      test = this->calcDeterminationCoeff(_table->featureTestData(), _table->targetTestData());
   auto res = std::make_pair(train, test);

   return res;
}

std::pair<double, double> pmat::LLearningModel::distanceRelativeRootMeanSquareErrors() {
   this->calcSolution();
   double train =
       this->calcRootMeanSquareError(_table->featureTrainingData(), _table->targetTrainingData());
   double test{};
   if (_table->featureTestData().rowSize() > 0)
      test = this->calcRootMeanSquareError(_table->featureTestData(), _table->targetTestData());
   auto res = std::make_pair(train, test);

   return res;
}

std::pair<double, double> pmat::LLearningModel::distanceMaximumRelativeScalarError() {
   this->calcSolution();
   double train =
       this->calcMaxRelativeError(_table->featureTrainingData(), _table->targetTrainingData());
   double test{};
   if (_table->featureTestData().rowSize() > 0)
      test = this->calcMaxRelativeError(_table->featureTestData(), _table->targetTestData());
   auto res = std::make_pair(train, test);

   return res;
}

std::pair<pmat::Vector, pmat::Vector> pmat::LLearningModel::determinationCoefficients() {
   this->calcSolution();
   pmat::Vector train{this->calcVetDeterminationCoeff(_table->featureTrainingData(),
                                                      _table->targetTrainingData())};
   pmat::Vector test{};
   if (_table->featureTestData().rowSize() > 0)
      test = this->calcVetDeterminationCoeff(_table->featureTestData(), _table->targetTestData());
   auto res = std::make_pair(train, test);

   return res;
}

std::pair<pmat::Vector, pmat::Vector> pmat::LLearningModel::relativeRootMeanSquareErrors() {
   this->calcSolution();
   pmat::Vector train{this->calcVetRootMeanSquareError(_table->featureTrainingData(),
                                                       _table->targetTrainingData())};
   pmat::Vector test{};
   if (_table->featureTestData().rowSize() > 0)
      test = this->calcVetRootMeanSquareError(_table->featureTestData(), _table->targetTestData());
   auto res = std::make_pair(train, test);

   return res;
}

std::pair<pmat::Vector, pmat::Vector> pmat::LLearningModel::maximumRelativeError() {
   this->calcSolution();
   pmat::Vector train{
       this->calcVetMaxRelativeError(_table->featureTrainingData(), _table->targetTrainingData())};
   pmat::Vector test{};
   if (_table->featureTestData().rowSize() > 0)
      test = this->calcVetMaxRelativeError(_table->featureTestData(), _table->targetTestData());
   auto res = std::make_pair(train, test);

   return res;
}

pmat::Matrix pmat::LLearningModel::predict(const pmat::Matrix &query) {
   if (query.columnSize() != this->_table->nFeatures())
      throw std::runtime_error("Query and model have different dimensions.");

   pmat::Matrix resp{query.rowSize(), this->_table->nTargets()};
   for (int i{0}; i < query.rowSize(); i++)
      resp.assignToRow(i, this->predict(query.rowToVector(i)));

   return resp;
}

pmat::Matrix pmat::LLearningModel::predictTraining() {
   pmat::Matrix resp{this->predict(this->_table->featureTrainingData())};

   return resp;
}

pmat::Matrix pmat::LLearningModel::predictTest() {
   pmat::Matrix resp{this->predict(this->_table->featureTestData())};

   return resp;
}
