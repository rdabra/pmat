#include "AnalyticsBaseTable.h"
#include "Matrix.h"
#include "Vector.h"
#include "pmatUtils.h"
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

int AnalyticsBaseTable::parseHeader(std::stringstream &lineStream, int nWords,
                                    std::vector<std::string> &headerType) {
   std::string word;
   for (int j{0}; j < nWords; j++) {
      if (std::getline(lineStream, word, _separator))
         headerType.emplace_back(word);
      else
         return false;
   }
   return true;
}

int AnalyticsBaseTable::parseDataRow(std::stringstream &lineStream, int nWords, int row,
                                     pmat::Matrix &matrix) {
   std::string word;
   for (int j{0}; j < nWords; j++) {
      if (std::getline(lineStream, word, _separator))
         matrix(row, j) = std::stod(word);
      else
         return false;
   }
   return true;
}

AnalyticsBaseTable::AnalyticsBaseTable(int nFeatures, int nTargets, int pctTrainSize,
                                       std::string fileName, bool hasHeader, char separator)
    : _nFeatures{nFeatures}, _nTargets{nTargets}, _fileName{fileName}, _hasHeader{hasHeader},
      _separator(separator) {
   int nLines{pmat::utils::countFileLines(fileName)};
   if (hasHeader)
      nLines--;
   _pctTrainSize = pctTrainSize > 100 ? 100 : pctTrainSize;
   _trainSize = nLines * _pctTrainSize / 100;
   _testSize = nLines - _trainSize;
   _trainFeatureData = pmat::Matrix{_trainSize, nFeatures};
   _trainTargetData = pmat::Matrix{_trainSize, nTargets};
   _testFeatureData = pmat::Matrix{_testSize, nFeatures};
   _testTargetData = pmat::Matrix{_testSize, nTargets};
}

void AnalyticsBaseTable::readFile() {
   std::ifstream f{_fileName};
   std::string line{""};

   int nRows{0};
   if (f.is_open()) {
      if (_hasHeader) {
         std::getline(f, line);
         std::stringstream lineStream{line};
         if (!(this->parseHeader(lineStream, _nFeatures, _featureHeader) &&
               this->parseHeader(lineStream, _nTargets, _targetHeader))) {
            f.close();
            throw std::runtime_error("Error reading header.");
         }
      }
      for (int i{0}; i < _trainSize; i++) {
         std::getline(f, line);
         std::stringstream lineStream{line};
         if (!(this->parseDataRow(lineStream, _nFeatures, i, _trainFeatureData) &&
               this->parseDataRow(lineStream, _nTargets, i, _trainTargetData))) {
            f.close();
            throw std::runtime_error("Error reading data row " + std::to_string(nRows + 1));
         }
      }
      for (int i{0}; i < _testSize; i++) {
         std::getline(f, line);
         std::stringstream lineStream{line};
         if (!(this->parseDataRow(lineStream, _nFeatures, i, _testFeatureData) &&
               this->parseDataRow(lineStream, _nTargets, i, _testTargetData))) {
            f.close();
            throw std::runtime_error("Error reading data row " + std::to_string(nRows + 1));
         }
      }
   } else
      throw std::runtime_error("Could not open file.");

   f.close();
}
