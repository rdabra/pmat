#ifndef LQUERY_H
#define LQUERY_H
#pragma once

#include "LLearningModel.h"
#include "Matrix.h"
#include <string>
#include <vector>

namespace pmat {

class LQuery {
   private:
      pmat::LLearningModel *_model;
      pmat::Matrix _data{};
      pmat::Matrix _target{};
      bool _targetCalculated{false};
      int _nRows{0};
      std::vector<std::string> _header{};
      bool _hasHeader{false};
      std::string _fileName{""};
      char _separator{','};

      int parseHeader(std::stringstream &lineStream);
      int parseDataRow(std::stringstream &lineStream, int row);

   public:
      LQuery(pmat::LLearningModel &model, std::string fileName, bool hasHeader, char separator);

      void readFile();
      void calculateTarget();
      void exportTarget(std::string fileName);
      void exportFeatureTarget(std::string fileName);
      [[nodiscard]] double determinationCoefficients();
      [[nodiscard]] double rootMeanSquareErrors();

      [[nodiscard]] const std::vector<std::string> &header() const { return _header; }

      [[nodiscard]] const pmat::LLearningModel &model() const { return *_model; }
      void setModel(pmat::LLearningModel &model);
};

} // namespace pmat

#endif