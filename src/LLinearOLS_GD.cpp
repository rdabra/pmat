#include "LLinearOLS_GD.h"
#include "Matrix.h"
#include "MatrixSymmetric.h"
#include "Vector.h"
#include "pmatUtils.h"
#include <cmath>
#include <utility>

void pmat::LLinearOLS_GD::calcSolution() {
   if (!_gdCalculated) {
      auto featTrainData = _table->featureTrainingData();
      auto targTrainData = _table->targetTrainingData();

      if (featTrainData.rowSize() >= 2) {
         pmat::Matrix X{featTrainData};
         X.insertColumn(featTrainData.columnSize() - 1, pmat::utils::ONE);
         pmat::MatrixSymmetric Z{pmat::MatrixSymmetric::gramMatrix(X)};
         pmat::Matrix Y{targTrainData};
         Y.transpose();
         pmat::Matrix K{Y * X};

         double invNormX = pmat::utils::inv(X.getFrobeniusNorm());
         pmat::Matrix B0{targTrainData.columnSize(), featTrainData.columnSize() + 1};
         B0.fillWith(Y.getFrobeniusNorm() * invNormX * invNormX);

         pmat::Matrix Bl{B0 * Z};
         Bl.subtractBy(K);
         Bl.multiplyBy(pmat::utils::MINUS_ONE * pmat::utils::ONE_HALF * invNormX * invNormX);
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
      } else
         throw std::logic_error("Insufficent training data.");
   }
}

const pmat::Matrix &pmat::LLinearOLS_GD::coefficients() {
   this->calcSolution();
   return _gdCoeffs;
}

void pmat::LLinearOLS_GD::setTolerance(const double &tolerance) {
   _tolerance = tolerance;
   _gdCalculated = false;
}

pmat::Vector pmat::LLinearOLS_GD::predict(const pmat::Vector &query) {
   pmat::Vector aux{query};
   aux.pushBack(pmat::utils::ONE);
   this->calcSolution();
   pmat::Vector resp{_gdCoeffs * aux};

   return resp;
}
