#include "LQuery.h"

#include "pmatUtils.h"
#include <string>
#include <utility>

int pmat::LQuery::parseDataRow(std::stringstream &lineStream, int row) {
   std::string word;
   for (int j{0}; j < _model->table().nFeatures(); j++) {
      if (std::getline(lineStream, word, _separator))
         _query(row, j) = std::stod(word);
      else
         return false;
   }
   return true;
}

pmat::LQuery::LQuery(pmat::LLearningModel &model, std::string fileName, char separator)
    : _model{&model}, _fileName{std::move(fileName)}, _separator{separator} {
   _nRows = pmat::utils::countFileLines(_fileName);
   _query = pmat::Matrix{_nRows, _model->table().nFeatures()};
}

void pmat::LQuery::readFile() {
   std::ifstream f{_fileName};
   std::string line{""};

   int nRows{0};
   if (f.is_open()) {
      for (int i{0}; i < _nRows; i++) {
         std::getline(f, line);
         std::stringstream lineStream{line};
         if (!this->parseDataRow(lineStream, i)) {
            f.close();
            _query.clear();
            throw std::runtime_error("Error reading data row " + std::to_string(nRows + 1));
         }
      }
   } else
      throw std::runtime_error("Could not open file.");

   f.close();
}

void pmat::LQuery::calculateTarget() {
   if (!_targetCalculated) {
      _prediction = pmat::Matrix{_nRows, _model->table().nTargets()};
      for (int i{0}; i < _nRows; i++)
         _prediction.assignToRow(i, _model->predict(_query.rowToVector(i)));
      _targetCalculated = true;
   }
}

void pmat::LQuery::exportPrediction(std::string fileName) {
   this->calculateTarget();
   std::ofstream f{_fileName};
   std::string line;
   if (f.is_open()) {
      if (_model->table().hasHeader()) {
         line = "";
         for (int j{0}; j < _prediction.columnSize(); j++) {
            line += _model->table().targetHeader()[j];
            if (j != _prediction.columnSize() - 1)
               line += _separator;
         }
         f << line << std::endl;
      }
      for (int i{0}; i < _prediction.rowSize(); i++) {
         line = "";
         for (int j{0}; j < _prediction.columnSize(); j++) {
            line += pmat::utils::format(_prediction(i, j));
            if (j != _prediction.columnSize() - 1)
               line += _separator;
         }
         if (i != _prediction.rowSize() - 1)
            line += "\n";
         f << line;
      }
      f.close();
   } else
      throw std::runtime_error("Could not open file.");
}

void pmat::LQuery::exportFeatureTarget(std::string fileName) {
   this->calculateTarget();
   std::ofstream f{_fileName};
   std::string line;
   if (f.is_open()) {
      if (_model->table().hasHeader()) {
         line = "";
         for (int j{0}; j < _query.columnSize(); j++)
            line += _model->table().featureHeader()[j] + _separator;
         for (int j{0}; j < _prediction.columnSize(); j++) {
            line += _model->table().targetHeader()[j];
            if (j != _prediction.columnSize() - 1)
               line += _separator;
         }
         f << line << std::endl;
      }
      for (int i{0}; i < _prediction.rowSize(); i++) {
         line = "";
         for (int j{0}; j < _query.columnSize(); j++)
            line += pmat::utils::format(_query(i, j)) + _separator;
         for (int j{0}; j < _prediction.columnSize(); j++) {
            line += pmat::utils::format(_prediction(i, j));
            if (j != _prediction.columnSize() - 1)
               line += _separator;
         }
         if (i != _prediction.rowSize() - 1)
            line += "\n";
         f << line;
      }
      f.close();
   } else
      throw std::runtime_error("Could not open file.");
}

void pmat::LQuery::setModel(pmat::LLearningModel &model) {
   if (model.table().nFeatures() != _model->table().nFeatures())
      throw std::runtime_error("Model and data have different feature sizes.");

   _model = &model;
   _query.clear();
   _query = pmat::Matrix{_nRows, _model->table().nFeatures()};
   _prediction.clear();
   _targetCalculated = false;
}
