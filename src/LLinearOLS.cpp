#include "LLinearOLS.h"
#include "DecompositionPLU.h"
#include "Matrix.h"
#include "MatrixSquare.h"
#include "MatrixSymmetric.h"
#include "Vector.h"
#include "pmatUtils.h"
#include <utility>

void pmat::LLinearOLS::calcAnalyticSolution() {
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
            _analyticCorrTrainData = calcCorrCoeffs(*_trainFeature, *_trainTarget);
            if (_testFeature->rowSize() >= 2) {
               _analyticCorrTestData = calcCorrCoeffs(*_testFeature, *_testTarget);
            }
         } else {
            _analyticCalculated = false;
            throw std::logic_error("Coefficients cannot be obtained analytically.");
         }
      } else
         throw std::logic_error("Insufficent training data.");
   }
}

const pmat::Matrix &pmat::LLinearOLS::coefficients() {
   this->calcAnalyticSolution();
   return _analyticCoeffs;
}

const double &pmat::LLinearOLS::trainingCorrelation() {
   this->calcAnalyticSolution();
   return _analyticCorrTrainData;
}

const double &pmat::LLinearOLS::testCorrelation() {
   this->calcAnalyticSolution();
   return _analyticCorrTestData;
}

pmat::Vector pmat::LLinearOLS::targetOf(const pmat::Vector &feature) {
   pmat::Vector aux{feature};
   aux.pushBack(pmat::utils::ONE);
   this->calcAnalyticSolution();
   pmat::Vector resp{_analyticCoeffs * aux};

   return resp;
}
