#ifndef LQUERY_H
#define LQUERY_H
#pragma once

#include "LLearningModel.h"
#include "Matrix.h"
#include <string>

namespace pmat {

class LQuery {
   private:
      pmat::LLearningModel *_model;
      pmat::Matrix _query{};
      pmat::Matrix _prediction{};
      bool _targetCalculated{false};
      int _nRows{0};
      std::string _fileName{""};
      char _separator{','};

      int parseHeader(std::stringstream &lineStream);
      int parseDataRow(std::stringstream &lineStream, int row);

   public:
      LQuery(pmat::LLearningModel &model, std::string fileName, char separator);

      void readFile();
      void calculateTarget();
      void exportPrediction(std::string fileName);
      void exportFeatureTarget(std::string fileName);

      [[nodiscard]] const pmat::LLearningModel &model() const { return *_model; }
      void setModel(pmat::LLearningModel &model);
};

} // namespace pmat

#endif