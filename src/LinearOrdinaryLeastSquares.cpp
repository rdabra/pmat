#include "LinearOrdinaryLeastSquares.h"
#include "DecompositionPLU.h"
#include "Matrix.h"
#include "MatrixSquare.h"
#include "MatrixSymmetric.h"
#include "Vector.h"
#include "pmatUtils.h"
#include <cmath>
#include <utility>

void LinearOrdinaryLeastSquares::calcAnalyticSolution() {
   if (!_analyticCalculated) {
      if (_trainFeature->rowSize() >= 2) {
         pmat::Matrix X{*_trainFeature};
         X.insertColumn(_trainFeature->columnSize() - 1, pmat::utils::ONE);
         pmat::MatrixSymmetric Z{pmat::MatrixSymmetric::gramMatrix(X)};
         pmat::DecompositionPLU decomp{Z};

         if (decomp.isInvertible()) {
            pmat::Matrix Y{*_trainTarget};
            Y.transpose();

            _analyticCoeffs = std::move(Y * X * decomp.inverse());
            _analyticCalculated = true;
            _analyticCorrTrainData = calcCorrCoeffs(*_trainFeature, *_trainTarget, _analyticCoeffs);
            if (_testFeature->rowSize() >= 2) {
               _analyticCorrTestData = calcCorrCoeffs(*_testFeature, *_testTarget, _analyticCoeffs);
            }
         } else {
            _analyticCalculated = false;
            throw std::logic_error("Coefficients cannot be obtained analytically.");
         }
      } else
         throw std::logic_error("Insufficent training data.");
   }
}

void LinearOrdinaryLeastSquares::calcGdSolution() {
   if (!_gdCalculated) {
      if (_trainFeature->rowSize() >= 2) {
         pmat::Matrix X{*_trainFeature};
         X.insertColumn(_trainFeature->columnSize() - 1, pmat::utils::ONE);
         pmat::MatrixSymmetric Z{pmat::MatrixSymmetric::gramMatrix(X)};
         pmat::Matrix Y{*_trainTarget};
         Y.transpose();
         pmat::Matrix K{Y * X};

         double invNormX = pmat::utils::inv(X.getFrobeniusNorm());
         pmat::Matrix B0{_trainTarget->columnSize(), _trainFeature->columnSize() + 1};
         B0.fillWith(Y.getFrobeniusNorm() * invNormX);

         pmat::Matrix Bl{B0 * Z};
         Bl.subtractBy(K);
         Bl.multiplyBy(pmat::utils::MINUS_ONE * invNormX * invNormX);
         Bl.addBy(B0);

         pmat::Matrix L{Bl - B0};
         _nIterations = 0;
         while (L.getFrobeniusNorm() > _tolerance && _nIterations < _maxIterations) {
            pmat::Matrix LZ{L * Z};
            pmat::Matrix BlZ{Bl * Z};
            BlZ.subtractBy(K);
            double norm = LZ.getFrobeniusNorm();
            BlZ.multiplyBy(std::fabs(L.dotProduct(LZ)) / (norm * norm));
            pmat::Matrix Bl1{Bl};
            Bl1.subtractBy(BlZ);

            L = Bl1 - Bl;
            Bl = std::move(Bl1);
            _nIterations++;
         };
         _gdCoeffs = std::move(Bl);
         _gdCorrTrainData = calcCorrCoeffs(*_trainFeature, *_trainTarget, _gdCoeffs);
         if (_testFeature->rowSize() >= 2) {
            _gdCorrTestData = calcCorrCoeffs(*_testFeature, *_testTarget, _gdCoeffs);
         }
         _gdCalculated = true;
      } else
         throw std::logic_error("Insufficent training data.");
   }
}

double LinearOrdinaryLeastSquares::calcCorrCoeffs(const pmat::Matrix feature,
                                                  const pmat::Matrix target,
                                                  const pmat::Matrix &coefs) {
   std::vector<pmat::Vector> features{feature.rowsToVectors()};
   std::vector<pmat::Vector> targets{target.rowsToVectors()};

   pmat::Vector mean{targets[0]};
   for (int i{1}; i < targets.size(); i++)
      mean = mean + targets[i];
   mean.multiplyBy(pmat::utils::inv((double)targets.size()));

   double distancesFromMean{pmat::utils::ZERO};
   double distancesFromEstimation{pmat::utils::ZERO};
   for (int i{0}; i < targets.size(); i++) {
      double distFM{mean.euclideanDistantFrom(targets[i])};
      distancesFromMean += distFM * distFM;
      features[i].pushBack(pmat::utils::ONE);
      double distFE{targets[i].euclideanDistantFrom(coefs * features[i])};
      distancesFromEstimation += distFE * distFE;
   }

   return pmat::utils::ONE - (distancesFromEstimation / distancesFromMean);
}

const pmat::Matrix &LinearOrdinaryLeastSquares::analyticCoefficients() {
   this->calcAnalyticSolution();
   return _analyticCoeffs;
}

const pmat::Matrix &LinearOrdinaryLeastSquares::gradientDescentCoefficients() {
   this->calcGdSolution();
   return _gdCoeffs;
}

void LinearOrdinaryLeastSquares::setTolerance(const double &tolerance) {
   _tolerance = tolerance;
   _gdCalculated = false;
}

const double &LinearOrdinaryLeastSquares::analyticTrainingCorrelation() {
   this->calcAnalyticSolution();
   return _analyticCorrTrainData;
}

const double &LinearOrdinaryLeastSquares::analyticTestCorrelation() {
   if (_testFeature->rowSize() < 2)
      throw std::logic_error("Insufficent test data.");
   this->calcAnalyticSolution();
   return _analyticCorrTestData;
}

const double &LinearOrdinaryLeastSquares::gradientDescentTrainingCorrelation() {
   this->calcGdSolution();

   return _gdCorrTrainData;
}

const double &LinearOrdinaryLeastSquares::gradientDescentTestCorrelation() {
   if (_testFeature->rowSize() < 2)
      throw std::logic_error("Insufficent test data.");
   this->calcGdSolution();

   return _gdCorrTestData;
}

pmat::Vector LinearOrdinaryLeastSquares::analyticTargetOf(const pmat::Vector &feature) {
   pmat::Vector aux{feature};
   aux.pushBack(pmat::utils::ONE);
   this->calcAnalyticSolution();
   pmat::Vector resp{_analyticCoeffs * aux};

   return resp;
}

pmat::Vector LinearOrdinaryLeastSquares::gradientDescentTargetOf(const pmat::Vector &feature) {
   pmat::Vector aux{feature};
   aux.pushBack(pmat::utils::ONE);
   this->calcGdSolution();
   pmat::Vector resp{_gdCoeffs * aux};

   return resp;
}
