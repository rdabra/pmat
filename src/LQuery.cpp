#include "LQuery.h"

#include "pmatUtils.h"
#include <string>
#include <utility>

int pmat::LQuery::parseHeader(std::stringstream &lineStream) {
   std::string word;
   for (int j{0}; j < _model->table().nFeatures(); j++) {
      if (std::getline(lineStream, word, _separator))
         _header.emplace_back(word);
      else
         return false;
   }
   return true;
}

int pmat::LQuery::parseDataRow(std::stringstream &lineStream, int row) {
   std::string word;
   for (int j{0}; j < _model->table().nFeatures(); j++) {
      if (std::getline(lineStream, word, _separator))
         _data(row, j) = std::stod(word);
      else
         return false;
   }
   return true;
}

pmat::LQuery::LQuery(pmat::LLearningModel &model, std::string fileName, bool hasHeader,
                     char separator)
    : _model{&model}, _fileName{std::move(fileName)}, _hasHeader{hasHeader}, _separator{separator} {
   _nRows = pmat::utils::countFileLines(_fileName);
   _data = pmat::Matrix{_nRows, _model->table().nFeatures()};
}

void pmat::LQuery::readFile() {
   std::ifstream f{_fileName};
   std::string line{""};

   int nRows{0};
   if (f.is_open()) {
      if (_hasHeader) {
         std::getline(f, line);
         std::stringstream lineStream{line};
         if (!this->parseHeader(lineStream)) {
            f.close();
            throw std::runtime_error("Error reading header.");
         }
      }
      for (int i{0}; i < _nRows; i++) {
         std::getline(f, line);
         std::stringstream lineStream{line};
         if (!this->parseDataRow(lineStream, i)) {
            f.close();
            throw std::runtime_error("Error reading data row " + std::to_string(nRows + 1));
         }
      }
   } else
      throw std::runtime_error("Could not open file.");

   f.close();
}

void pmat::LQuery::calculateTarget() {
   if (!_targetCalculated) {
      _target = pmat::Matrix{_nRows, _model->table().nTargets()};
      for (int i{0}; i < _nRows; i++)
         _target.assignToRow(i, _model->targetOf(_data.rowToVector(i)));
      _targetCalculated = true;
   }
}

void pmat::LQuery::setModel(pmat::LLearningModel &model) {
   if (model.table().nFeatures() != _model->table().nFeatures())
      throw std::runtime_error("Model and data have different feature sizes.");

   _model = &model;
   _data.clearAndResize(0, 0);
   _data = pmat::Matrix{_nRows, _model->table().nFeatures()};
   _target.clearAndResize(0, 0);
   _targetCalculated = false;
}
