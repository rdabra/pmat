#include "LLinearOLS.h"
#include "DecompositionPLU.h"
#include "Matrix.h"
#include "MatrixSquare.h"
#include "MatrixSymmetric.h"
#include "Vector.h"
#include "pmatUtils.h"
#include <utility>

void pmat::LLinearOLS::calcSolution() {
   if (!_analyticCalculated) {
      auto featTrainData = _table->featureTrainingData();
      auto targTrainData = _table->targetTrainingData();

      if (featTrainData.rowSize() >= 2) {
         pmat::Matrix X{featTrainData};
         X.insertColumn(featTrainData.columnSize() - 1, pmat::utils::ONE);
         pmat::MatrixSymmetric Z{pmat::MatrixSymmetric::gramMatrix(X)};
         pmat::DecompositionPLU decomp{Z};

         if (decomp.isInvertible()) {
            pmat::Matrix Y{targTrainData};
            Y.transpose();

            _analyticCoeffs = std::move(Y * X * decomp.inverse());
            _analyticCalculated = true;
         } else {
            _analyticCalculated = false;
            throw std::logic_error("Coefficients cannot be obtained analytically.");
         }
      } else
         throw std::logic_error("Insufficent training data.");
   }
}

const pmat::Matrix &pmat::LLinearOLS::coefficients() {
   this->calcSolution();
   return _analyticCoeffs;
}

pmat::Vector pmat::LLinearOLS::predict(const pmat::Vector &query) {
   pmat::Vector aux{query};
   aux.pushBack(pmat::utils::ONE);
   this->calcSolution();
   pmat::Vector resp{_analyticCoeffs * aux};

   return resp;
}
