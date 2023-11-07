#ifndef ANALYTICSBASETABLE_H
#define ANALYTICSBASETABLE_H
#pragma once

#include "Matrix.h"
#include <sstream>
#include <string>
#include <vector>

namespace pmat {

enum class DATA_TYPE { DISCRETE, CONTINUOUS };

/**
 * @brief Abstracts the Analytics Base Table (ABT)
 *
 */
class LAnalyticsBaseTable {
   private:
      int _nFeatures{0};
      int _nTargets{0};
      int _trainSize{0};
      int _testSize{0};
      int _pctTrainSize{100};
      std::string _fileName{""};
      bool _hasHeader{false};
      char _separator{','};
      DATA_TYPE _featType{DATA_TYPE::CONTINUOUS};
      DATA_TYPE _targType{DATA_TYPE::CONTINUOUS};

      std::vector<std::string> _featureHeader{};
      std::vector<std::string> _targetHeader{};
      pmat::Matrix _trainFeatureData{};
      pmat::Matrix _trainTargetData{};
      pmat::Matrix _testFeatureData{};
      pmat::Matrix _testTargetData{};

      int parseHeader(std::stringstream &lineStream, int nWords,
                      std::vector<std::string> &headerType);
      int parseDataRow(std::stringstream &lineStream, int nWords, int row, pmat::Matrix &matrix);

   public:
      /**
       * @brief Constructs a new Analytics Base Table (ABT)
       *
       * @param nFeatures Number of features (feature-vector dimension)
       * @param nTargets Number of targets (target-vector dimension)
       * @param pctTrainingSize Percentage of the first data rows to be considered training data.
       * @param fileName file name of the ABT data
       * @param hasHeader specifies if the first of ABT file is a header
       * @param separator separator of values
       * The remaining data rows are considered testing data.
       */
      LAnalyticsBaseTable(int nFeatures, int nTargets, int pctTrainingSize, std::string fileName,
                          bool hasHeader, char separator);

      /**
       * @brief Reads any text file in which every row has feature values in columns followed by
       * target values in columns.
       *
       * @throws std::runtime_error Exposes problems when reading the file
       */
      void readFile();

      /**
       * @brief Returns number of rows of the training data
       *
       * @return int Number of rows of the training data
       */
      [[nodiscard]] int trainingSize() const { return _trainSize; }

      /**
       * @brief Returns number of rows of the test data
       *
       * @return int Number of rows of the test data
       */
      [[nodiscard]] int testSize() const { return _testSize; }

      /**
       * @brief Returns the number of features
       *
       * @return int Number of features
       */
      [[nodiscard]] int nFeatures() const { return _nFeatures; }

      /**
       * @brief Returns the number of targets
       *
       * @return int Number of targets
       */
      [[nodiscard]] int nTargets() const { return _nTargets; }

      /**
       * @brief List of feature column names
       *
       * @return const std::vector<std::string>& Feature column names
       */
      [[nodiscard]] const std::vector<std::string> &featureHeader() const { return _featureHeader; }

      /**
       * @brief List of target column names
       *
       * @return const std::vector<std::string>& Target column names
       */
      [[nodiscard]] const std::vector<std::string> &targetHeader() const { return _targetHeader; }

      /**
       * @brief Features of the training data
       *
       * @return const pmat::Matrix&
       */
      [[nodiscard]] const pmat::Matrix &featureTrainingData() const { return _trainFeatureData; }

      /**
       * @brief Targets of the training data
       *
       * @return const pmat::Matrix&
       */
      [[nodiscard]] const pmat::Matrix &targetTrainingData() const { return _trainTargetData; }

      /**
       * @brief Features of the test data
       *
       * @return const pmat::Matrix&
       */
      [[nodiscard]] const pmat::Matrix &featureTestData() const { return _testFeatureData; }

      /**
       * @brief Targets of the test data
       *
       * @return const pmat::Matrix&
       */
      [[nodiscard]] const pmat::Matrix &targetTestData() const { return _testTargetData; }

      [[nodiscard]] DATA_TYPE featureType() const { return _featType; }
      void setFeatureType(const DATA_TYPE &featType) { _featType = featType; }

      [[nodiscard]] DATA_TYPE targetType() const { return _targType; }
      void setTargetType(const DATA_TYPE &targType) { _targType = targType; }

      [[nodiscard]] const bool &hasHeader() const { return _hasHeader; }
};
} // namespace pmat
#endif