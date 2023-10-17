#include "Matrix.h"
#include "Messages.h"
#include "TMultiplicationManager.h"
#include "utils.h"
#include <fstream>
#include <random>
#include <sstream>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>

unsigned pmat::Matrix::vectorIndex(const unsigned &row, const unsigned &column) const {
   return _isTransposed ? row + column * _rowSize : column + row * _columnSize;
}

double pmat::Matrix::vectorElement(const unsigned &row, const unsigned &column) const {
   return _matrix(this->vectorIndex(row, column));
}

void pmat::Matrix::moveToThis(Matrix &&matrix) {
   _rowSize = matrix.rowSize();
   _columnSize = matrix.columnSize();
   _isTransposed = matrix._isTransposed;
   _matrix.clear();
   _matrix = std::move(matrix._matrix);
   matrix.~Matrix();
}

void pmat::Matrix::initializeMembers(unsigned rowSize, unsigned columnSize, bool isTransposed) {
   _matrix.clear();
   _rowSize = rowSize;
   _columnSize = columnSize;
   _isTransposed = isTransposed;
   _matrix.resize(this->length());
}

void pmat::Matrix::copyMembers(const Matrix &matrix) {
   _matrix = matrix._matrix;
   _rowSize = matrix.rowSize();
   _columnSize = matrix.columnSize();
   _isTransposed = matrix.isTransposed();
}

pmat::Matrix::Matrix(const unsigned &rowSize, const unsigned &columnSize) {
   this->initializeMembers(rowSize, columnSize, false);
}

pmat::Matrix::Matrix(const std::string &fileName) {
   std::ifstream f{fileName};
   if (f.is_open()) {
      unsigned i{0};
      std::string line;
      while (std::getline(f, line)) {
         std::stringstream lineStream{line};
         std::string element;
         while (std::getline(lineStream, element, ','))
            _matrix.pushBack(std::stod(element));
         i++;
      }
      f.close();
      _rowSize = i;
      if (_matrix.size() % i == 0)
         _columnSize = _matrix.size() / i;
      else
         throw std::runtime_error(pmat::messages::DATA_NOT_READ);
   } else
      throw std::runtime_error(pmat::messages::FILE_NOT_OPEN);
}

void pmat::Matrix::clearAndResize(const unsigned &rowSize, const unsigned &columnSize) {
   this->initializeMembers(rowSize, columnSize, false);
}

void pmat::Matrix::clear() {
   _matrix.clear();
   _rowSize = 0;
   _columnSize = 0;
}

void pmat::Matrix::setValue(const double &value, const unsigned &row, const unsigned &column) {
   if (row >= this->rowSize() || column >= this->columnSize())
      throw std::invalid_argument(pmat::messages::INDEX_OUT);

   _matrix.set(this->vectorIndex(row, column), value);
}

double pmat::Matrix::operator()(const unsigned &row, const unsigned &column) const {
   if (row >= this->rowSize() || column >= this->columnSize())
      throw std::invalid_argument(pmat::messages::INDEX_OUT);

   return _matrix(this->vectorIndex(row, column));
}

pmat::Matrix &pmat::Matrix::operator=(const Matrix &matrix) {
   if (this != &matrix) {
      _rowSize = matrix.rowSize();
      _columnSize = matrix.columnSize();
      _matrix.clear();
      _matrix = matrix._matrix;
      _isTransposed = matrix._isTransposed;
   }

   return *this;
}

pmat::Matrix &pmat::Matrix::operator=(Matrix &&matrix) noexcept {
   this->moveToThis(std::move(matrix));

   return *this;
}

bool pmat::Matrix::operator==(const Matrix &matrix) const {
   if (this->rowSize() == matrix.rowSize() && this->columnSize() == matrix.columnSize()) {
      for (unsigned i = 0; i < this->rowSize(); i++)
         for (unsigned j = 0; j < this->columnSize(); j++)
            if (!pmat::utils::areEqual((*this)(i, j), matrix(i, j)))
               return false;

   } else
      return false;

   return true;
}

double pmat::Matrix::dotProduct(const Matrix &matrix) const {
   if (matrix.rowSize() != this->rowSize() || matrix.columnSize() != this->columnSize())
      throw std::invalid_argument(pmat::messages::NONCOMPT_SIZE_ARG);

   double resp = pmat::utils::ZERO;
   for (unsigned i = 0; i < this->rowSize(); i++)
      for (unsigned j = 0; j < this->columnSize(); j++)
         resp += (*this)(i, j) * matrix(i, j);

   return resp;
}

pmat::Matrix pmat::Matrix::operator+(const Matrix &matrix) const {
   if (matrix.rowSize() != this->rowSize() || matrix.columnSize() != this->columnSize())
      throw std::invalid_argument(pmat::messages::NONCOMPT_SIZE_ARG);

   Matrix resp{this->rowSize(), this->columnSize()};
   for (unsigned i = 0; i < this->rowSize(); i++)
      for (unsigned j = 0; j < this->columnSize(); j++)
         resp.setValue((*this)(i, j) + matrix(i, j), i, j);

   return resp;
}

void pmat::Matrix::addBy(const Matrix &matrix) {
   if (matrix.rowSize() != this->rowSize() || matrix.columnSize() != this->columnSize())
      throw std::invalid_argument(pmat::messages::NONCOMPT_SIZE_ARG);

   for (unsigned i = 0; i < this->rowSize(); i++)
      for (unsigned j = 0; j < this->columnSize(); j++)
         this->setValue((*this)(i, j) + matrix(i, j), i, j);
}

pmat::Matrix pmat::Matrix::operator-(const Matrix &matrix) const {
   if (matrix.rowSize() != this->rowSize() || matrix.columnSize() != this->columnSize())
      throw std::invalid_argument(pmat::messages::NONCOMPT_SIZE_ARG);

   Matrix resp{this->rowSize(), this->columnSize()};
   for (unsigned i = 0; i < this->rowSize(); i++)
      for (unsigned j = 0; j < this->columnSize(); j++)
         resp.setValue((*this)(i, j) - matrix(i, j), i, j);

   return resp;
}

void pmat::Matrix::subtractBy(const Matrix &matrix) {
   if (matrix.rowSize() != this->rowSize() || matrix.columnSize() != this->columnSize())
      throw std::invalid_argument(pmat::messages::NONCOMPT_SIZE_ARG);

   for (unsigned i = 0; i < this->rowSize(); i++)
      for (unsigned j = 0; j < this->columnSize(); j++)
         this->setValue((*this)(i, j) - matrix(i, j), i, j);
}

pmat::Matrix pmat::Matrix::operator*(const Matrix &matrix) const {
   if (matrix.rowSize() != this->columnSize())
      throw std::invalid_argument(pmat::messages::NONCOMPT_SIZE_ARG);

   Matrix resp{this->rowSize(), matrix.columnSize()};
   for (unsigned i = 0; i < this->rowSize(); i++)
      for (unsigned j = 0; j < matrix.columnSize(); j++) {
         double aux = pmat::utils::ZERO;
         for (unsigned k = 0; k < this->columnSize(); k++)
            aux += (*this)(i, k) * matrix(k, j);
         resp.setValue(aux, i, j);
      }

   return resp;
}

pmat::Vector pmat::Matrix::operator*(const Vector &vector) const {
   if (vector.size() != this->columnSize())
      throw std::invalid_argument(pmat::messages::NONCOMPT_SIZE_ARG);

   Vector resp{};
   for (unsigned i = 0; i < this->rowSize(); i++) {
      double aux = 0.0;
      for (unsigned k = 0; k < this->columnSize(); k++)
         aux += (*this)(i, k) * vector(k);
      resp.emplaceBack(aux);
   }

   return resp;
}

pmat::Matrix pmat::Matrix::operator*(const double &scalar) const {
   Matrix resp{};
   resp._columnSize = this->columnSize();
   resp._rowSize = this->rowSize();
   for (long i = 0; i < resp.length(); i++)
      resp._matrix.pushBack(scalar * _matrix(i));

   return resp;
}

void pmat::Matrix::multiplyBy(const double &scalar) {
   for (long i = 0; i < this->length(); i++)
      _matrix.set(i, _matrix(i) * scalar);
}

pmat::Matrix pmat::Matrix::multiply(const Matrix &matrix, unsigned nThreads) {
   if (matrix.rowSize() != this->columnSize())
      throw std::invalid_argument(pmat::messages::NONCOMPT_SIZE_ARG);

   Matrix res{this->rowSize(), matrix.columnSize()};
   TMultiplicationManager mgr{*this, matrix, res};
   mgr.multiply(nThreads);

   return res;
}

pmat::Matrix pmat::Matrix::multiplyHadamardBy(const Matrix &matrix) const {
   if (matrix.rowSize() != this->rowSize() || matrix.columnSize() != this->columnSize())
      throw std::invalid_argument(pmat::messages::NONCOMPT_SIZE_ARG);

   Matrix resp{matrix.rowSize(), matrix.columnSize()};
   for (unsigned i = 0; i < resp.rowSize(); i++)
      for (unsigned j = 0; j < resp.columnSize(); j++)
         resp.setValue((*this)(i, j) * matrix(i, j), i, j);

   return resp;
}

void pmat::Matrix::multiplyRowBy(const unsigned &row, const double &scalar) {
   if (row >= this->rowSize())
      throw std::invalid_argument(pmat::messages::INDEX_OUT);

   for (unsigned j = 0; j < this->columnSize(); j++)
      this->setValue((*this)(row, j) * scalar, row, j);
}

void pmat::Matrix::multiplyColumnBy(const unsigned &column, const double &scalar) {
   if (column >= this->columnSize())
      throw std::invalid_argument(pmat::messages::INDEX_OUT);

   for (unsigned i = 0; i < this->rowSize(); i++)
      this->setValue((*this)(i, column) * scalar, i, column);
}

void pmat::Matrix::swapRows(const unsigned &rowA, const unsigned &rowB, const unsigned &startColumn,
                            const unsigned &endColumn) {
   if (startColumn > endColumn || rowA >= this->rowSize() || rowB >= this->rowSize())
      throw std::invalid_argument(pmat::messages::INDEX_OUT);

   for (unsigned j = startColumn; j <= endColumn; j++)
      _matrix.exchange(this->vectorIndex(rowA, j), this->vectorIndex(rowB, j));
}

void pmat::Matrix::swapRows(const unsigned &rowA, const unsigned &rowB) {
   this->swapRows(rowA, rowB, 0, this->columnSize() - 1);
}

void pmat::Matrix::swapColumns(const unsigned &columnA, const unsigned &columnB,
                               const unsigned &startRow, const unsigned &endRow) {
   if (startRow > endRow || columnA >= this->columnSize() || columnB >= this->columnSize())
      throw std::invalid_argument(pmat::messages::INDEX_OUT);

   for (unsigned i = startRow; i <= endRow; i++)
      _matrix.exchange(this->vectorIndex(i, columnA), this->vectorIndex(i, columnB));
}

void pmat::Matrix::swapColumns(const unsigned &columnA, const unsigned &columnB) {
   this->swapColumns(columnA, columnB, 0, this->rowSize() - 1);
}

void pmat::Matrix::transpose() {
   _isTransposed = !_isTransposed;
   std::swap(_rowSize, _columnSize);
}

double pmat::Matrix::getFrobeniusNorm() const {
   return sqrt(this->dotProduct(*this));
}

void pmat::Matrix::fillWithRandomValues(const double &min, const double &max) {
   // Type of random number distribution
   std::uniform_real_distribution<double> dist(min, max);

   // Mersenne Twister: Good quality random number generator initialized with non-deterministic
   // seeds
   std::mt19937 rng(std::random_device{}());

   for (unsigned i = 0; i < this->rowSize(); i++)
      for (unsigned j = 0; j < this->columnSize(); j++)
         this->setValue(dist(rng), i, j);
}

pmat::Vector pmat::Matrix::rowToVector(const unsigned &row) const {
   if (row >= this->rowSize())
      throw std::invalid_argument(pmat::messages::INDEX_OUT);

   Vector resp{};
   for (unsigned j = 0; j < this->columnSize(); j++)
      resp.emplaceBack((*this)(row, j));

   return resp;
}

pmat::Vector pmat::Matrix::columnToVector(const unsigned &column) const {
   if (column >= this->columnSize())
      throw std::invalid_argument(pmat::messages::INDEX_OUT);

   Vector resp{};
   for (unsigned i = 0; i < this->rowSize(); i++)
      resp.emplaceBack((*this)(i, column));

   return resp;
}

unsigned pmat::Matrix::occurrences(const double &value) const {
   unsigned res{0};
   for (unsigned i = 0; i < this->length(); i++)
      if (pmat::utils::areEqual(_matrix(i), value))
         res++;

   return res;
}

unsigned pmat::Matrix::occurrencesInRow(const unsigned row, const double &value) const {
   if (row >= this->rowSize())
      throw std::invalid_argument(pmat::messages::INDEX_OUT);

   unsigned res{0};
   for (unsigned j = 0; j < this->columnSize(); j++)
      if (pmat::utils::areEqual((*this)(row, j), value))
         res++;

   return res;
}

unsigned pmat::Matrix::occurrencesInColumn(const unsigned column, const double &value) const {
   if (column >= this->columnSize())
      throw std::invalid_argument(pmat::messages::INDEX_OUT);

   unsigned res{0};
   for (unsigned i = 0; i < this->rowSize(); i++)
      if (pmat::utils::areEqual((*this)(i, column), value))
         res++;

   return res;
}

std::string pmat::Matrix::formattedString() const {
   std::string res{"\n"};
   for (unsigned i{0}; i < this->rowSize(); i++) {
      for (unsigned j{0}; j < this->columnSize(); j++) {
         res += std::to_string((*this)(i, j)) + " ";
      }
      res += "\n";
   }

   return res;
}

void pmat::Matrix::insertRow(const unsigned &pos, const double &value) {
}
