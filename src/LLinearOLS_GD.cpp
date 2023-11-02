#include "LLinearOLS_GD.h"
#include "Matrix.h"
#include "MatrixSymmetric.h"
#include "Vector.h"
#include "pmatUtils.h"
#include <cmath>
#include <utility>

void pmat::LLinearOLS_GD::calcGdSolution() {
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
         _gdCalculated = true;
         _gdCorrTrainData = calcCorrCoeffs(*_trainFeature, *_trainTarget);
         if (_testFeature->rowSize() >= 2) {
            _gdCorrTestData = calcCorrCoeffs(*_testFeature, *_testTarget);
         }
      } else
         throw std::logic_error("Insufficent training data.");
   }
}

const pmat::Matrix &pmat::LLinearOLS_GD::coefficients() {
   this->calcGdSolution();
   return _gdCoeffs;
}

void pmat::LLinearOLS_GD::setTolerance(const double &tolerance) {
   _tolerance = tolerance;
   _gdCalculated = false;
}

const double &pmat::LLinearOLS_GD::trainingCorrelation() {
   this->calcGdSolution();

   return _gdCorrTrainData;
}

const double &pmat::LLinearOLS_GD::testCorrelation() {
   this->calcGdSolution();

   return _gdCorrTestData;
}

pmat::Vector pmat::LLinearOLS_GD::targetOf(const pmat::Vector &feature) {
   pmat::Vector aux{feature};
   aux.pushBack(pmat::utils::ONE);
   this->calcGdSolution();
   pmat::Vector resp{_gdCoeffs * aux};

   return resp;
}
