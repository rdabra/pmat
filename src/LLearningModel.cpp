#include "LLearningModel.h"
#include "pmatUtils.h"

double pmat::LLearningModel::calcCorrCoeffs(const pmat::Matrix feature, const pmat::Matrix target) {

   std::vector<pmat::Vector> features{feature.rowsToVectors()};
   std::vector<pmat::Vector> targets{target.rowsToVectors()};

   pmat::Vector mean{targets[0]};
   for (int i{1}; i < targets.size(); i++)
      mean = mean + targets[i];
   mean.multiplyBy(pmat::utils::inv((double)targets.size()));

   double distancesFromMean{pmat::utils::ZERO};
   double distancesFromEstimation{pmat::utils::ZERO};
   for (int i{0}; i < targets.size(); i++) {
      double distFM{this->distance(mean, targets[i])};
      distancesFromMean += distFM * distFM;
      //      features[i].pushBack(pmat::utils::ONE);
      double distFE{this->distance(targets[i], this->targetOf(features[i]))};
      distancesFromEstimation += distFE * distFE;
   }

   return pmat::utils::ONE - (distancesFromEstimation / distancesFromMean);
}
