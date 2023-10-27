#include "Matrix.h"
#include "Messages.h"
#include "TMultiplicationManager.h"
#include "pmatUtils.h"
#include <fstream>
#include <random>
#include <sstream>
#include <stdexcept>
#include <string>
#include <utility>

double pmat::Matrix::vectorElement(const int &row, const int &column) const {
   return _matrix(this->vectorIndex(row, column));
}

void pmat::Matrix::moveToThis(Matrix &&matrix) {
   Matrix &&aux = std::move(matrix);
   _rowSize = aux.rowSize();
   _columnSize = aux.columnSize();
   _isTransposed = aux._isTransposed;
   _matrix.clear();
   _matrix = std::move(aux._matrix);
   aux.~Matrix();
}

void pmat::Matrix::initializeMembers(int rowSize, int columnSize, bool isTransposed) {
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

pmat::Matrix::Matrix(const int &rowSize, const int &columnSize) {
   this->initializeMembers(rowSize, columnSize, false);
}

pmat::Matrix::Matrix(const std::string &fileName) {
   std::ifstream f{fileName};
   if (f.is_open()) {
      int i{0};
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

pmat::Matrix::Matrix(double data[], const int &rowSize, const int &columnSize)
    : _rowSize(rowSize), _columnSize(columnSize) {
   _matrix = pmat::Container1d{data, this->length()};
}

void pmat::Matrix::clearAndResize(const int &rowSize, const int &columnSize) {
   this->initializeMembers(rowSize, columnSize, false);
}

void pmat::Matrix::clear() {
   _matrix.clear();
   _rowSize = 0;
   _columnSize = 0;
}

void pmat::Matrix::assign(const double &value, const int &row, const int &column) {
   if (row >= this->rowSize() || column >= this->columnSize())
      throw std::invalid_argument(pmat::messages::INDEX_OUT);

   _matrix(this->vectorIndex(row, column)) = value;
}

void pmat::Matrix::assignNoCheck(const double &value, const int &row, const int &column) {
   _matrix(this->vectorIndex(row, column)) = value;
}

double pmat::Matrix::at(const int &row, const int &column) const {
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
      for (int i = 0; i < this->rowSize(); i++)
         for (int j = 0; j < this->columnSize(); j++)
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
   for (int i = 0; i < this->rowSize(); i++)
      for (int j = 0; j < this->columnSize(); j++)
         resp += (*this)(i, j) * matrix(i, j);

   return resp;
}

pmat::Matrix pmat::Matrix::operator+(const Matrix &matrix) const {
   if (matrix.rowSize() != this->rowSize() || matrix.columnSize() != this->columnSize())
      throw std::invalid_argument(pmat::messages::NONCOMPT_SIZE_ARG);

   Matrix resp{this->rowSize(), this->columnSize()};
   for (int i = 0; i < this->rowSize(); i++)
      for (int j = 0; j < this->columnSize(); j++)
         resp(i, j) = (*this)(i, j) + matrix(i, j);

   return resp;
}

void pmat::Matrix::addBy(const Matrix &matrix) {
   if (matrix.rowSize() != this->rowSize() || matrix.columnSize() != this->columnSize())
      throw std::invalid_argument(pmat::messages::NONCOMPT_SIZE_ARG);

   for (int i = 0; i < this->rowSize(); i++)
      for (int j = 0; j < this->columnSize(); j++)
         (*this)(i, j) = (*this)(i, j) + matrix(i, j);
}

pmat::Matrix pmat::Matrix::operator-(const Matrix &matrix) const {
   if (matrix.rowSize() != this->rowSize() || matrix.columnSize() != this->columnSize())
      throw std::invalid_argument(pmat::messages::NONCOMPT_SIZE_ARG);

   Matrix resp{this->rowSize(), this->columnSize()};
   for (int i = 0; i < this->rowSize(); i++)
      for (int j = 0; j < this->columnSize(); j++)
         resp(i, j) = (*this)(i, j) - matrix(i, j);

   return resp;
}

void pmat::Matrix::subtractBy(const Matrix &matrix) {
   if (matrix.rowSize() != this->rowSize() || matrix.columnSize() != this->columnSize())
      throw std::invalid_argument(pmat::messages::NONCOMPT_SIZE_ARG);

   for (int i = 0; i < this->rowSize(); i++)
      for (int j = 0; j < this->columnSize(); j++)
         (*this)(i, j) = (*this)(i, j) - matrix(i, j);
}

pmat::Matrix pmat::Matrix::operator*(const Matrix &matrix) const {
   if (matrix.rowSize() != this->columnSize())
      throw std::invalid_argument(pmat::messages::NONCOMPT_SIZE_ARG);

   Matrix resp{this->rowSize(), matrix.columnSize()};
   for (int i = 0; i < this->rowSize(); i++)
      for (int j = 0; j < matrix.columnSize(); j++) {
         double aux = pmat::utils::ZERO;
         for (int k = 0; k < this->columnSize(); k++)
            aux += (*this)(i, k) * matrix(k, j);
         resp(i, j) = aux;
      }

   return resp;
}

pmat::Vector pmat::Matrix::operator*(const Vector &vector) const {
   if (vector.size() != this->columnSize())
      throw std::invalid_argument(pmat::messages::NONCOMPT_SIZE_ARG);

   Vector resp{};
   for (int i = 0; i < this->rowSize(); i++) {
      double aux = 0.0;
      for (int k = 0; k < this->columnSize(); k++)
         aux += (*this)(i, k) * vector(k);
      resp.pushBack(aux);
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

pmat::Matrix pmat::Matrix::multiply(const Matrix &matrix, int nThreads) {
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
   for (int i = 0; i < resp.rowSize(); i++)
      for (int j = 0; j < resp.columnSize(); j++)
         resp(i, j) = (*this)(i, j) * matrix(i, j);

   return resp;
}

void pmat::Matrix::multiplyRowBy(const int &row, const double &scalar) {
   if (row >= this->rowSize())
      throw std::invalid_argument(pmat::messages::INDEX_OUT);

   for (int j = 0; j < this->columnSize(); j++)
      (*this)(row, j) = (*this)(row, j) * scalar;
}

void pmat::Matrix::multiplyColumnBy(const int &column, const double &scalar) {
   if (column >= this->columnSize())
      throw std::invalid_argument(pmat::messages::INDEX_OUT);

   for (int i = 0; i < this->rowSize(); i++)
      (*this)(i, column) = (*this)(i, column) * scalar;
}

void pmat::Matrix::swapRows(const int &rowA, const int &rowB, const int &startColumn,
                            const int &endColumn) {
   if (startColumn > endColumn || rowA >= this->rowSize() || rowB >= this->rowSize())
      throw std::invalid_argument(pmat::messages::INDEX_OUT);

   for (int j = startColumn; j <= endColumn; j++)
      _matrix.exchange(this->vectorIndex(rowA, j), this->vectorIndex(rowB, j));
}

void pmat::Matrix::swapRows(const int &rowA, const int &rowB) {
   this->swapRows(rowA, rowB, 0, this->columnSize() - 1);
}

void pmat::Matrix::swapColumns(const int &columnA, const int &columnB, const int &startRow,
                               const int &endRow) {
   if (startRow > endRow || columnA >= this->columnSize() || columnB >= this->columnSize())
      throw std::invalid_argument(pmat::messages::INDEX_OUT);

   for (int i = startRow; i <= endRow; i++)
      _matrix.exchange(this->vectorIndex(i, columnA), this->vectorIndex(i, columnB));
}

void pmat::Matrix::swapColumns(const int &columnA, const int &columnB) {
   this->swapColumns(columnA, columnB, 0, this->rowSize() - 1);
}

void pmat::Matrix::transpose() {
   _isTransposed = !_isTransposed;
   std::swap(_rowSize, _columnSize);
}

double pmat::Matrix::getFrobeniusNorm() const {
   return sqrt(this->dotProduct(*this));
}

void pmat::Matrix::fillWith(const double &value) {
   for (int i = 0; i < this->rowSize(); i++)
      for (int j = 0; j < this->columnSize(); j++)
         (*this)(i, j) = value;
}

void pmat::Matrix::fillWithRandomValues(const double &min, const double &max) {
   // Type of random number distribution
   std::uniform_real_distribution<double> dist(min, max);

   // Mersenne Twister: Good quality random number generator initialized with non-deterministic
   // seeds
   std::mt19937 rng(std::random_device{}());

   for (int i = 0; i < this->rowSize(); i++)
      for (int j = 0; j < this->columnSize(); j++)
         (*this)(i, j) = dist(rng);
}

pmat::Vector pmat::Matrix::rowToVector(const int &row) const {
   if (row >= this->rowSize())
      throw std::invalid_argument(pmat::messages::INDEX_OUT);

   Vector resp{};
   for (int j = 0; j < this->columnSize(); j++)
      resp.pushBack((*this)(row, j));

   return resp;
}

std::vector<pmat::Vector> pmat::Matrix::rowsToVectors() const {
   std::vector<pmat::Vector> resp;
   for (int i = 0; i < this->rowSize(); i++)
      resp.emplace_back(this->rowToVector(i));

   return resp;
}

pmat::Vector pmat::Matrix::columnToVector(const int &column) const {
   if (column >= this->columnSize())
      throw std::invalid_argument(pmat::messages::INDEX_OUT);

   Vector resp{};
   for (int i = 0; i < this->rowSize(); i++)
      resp.pushBack((*this)(i, column));

   return resp;
}

std::vector<pmat::Vector> pmat::Matrix::columnsToVectors() const {
   std::vector<pmat::Vector> resp;
   for (int j = 0; j < this->columnSize(); j++)
      resp.emplace_back(this->columnToVector(j));

   return resp;
}

int pmat::Matrix::occurrences(const double &value) const {
   int res{0};
   for (int i = 0; i < this->length(); i++)
      if (pmat::utils::areEqual(_matrix(i), value))
         res++;

   return res;
}

int pmat::Matrix::occurrencesInRow(const int row, const double &value) const {
   if (row >= this->rowSize())
      throw std::invalid_argument(pmat::messages::INDEX_OUT);

   int res{0};
   for (int j = 0; j < this->columnSize(); j++)
      if (pmat::utils::areEqual((*this)(row, j), value))
         res++;

   return res;
}

int pmat::Matrix::occurrencesInColumn(const int column, const double &value) const {
   if (column >= this->columnSize())
      throw std::invalid_argument(pmat::messages::INDEX_OUT);

   int res{0};
   for (int i = 0; i < this->rowSize(); i++)
      if (pmat::utils::areEqual((*this)(i, column), value))
         res++;

   return res;
}

std::string pmat::Matrix::formattedString() const {
   std::string res{""};
   for (int i{0}; i < this->rowSize(); i++) {
      for (int j{0}; j < this->columnSize(); j++) {
         std::stringstream stream;
         stream.setf(std::ios::fixed);
         stream.precision(pmat::utils::PRECISION + 1);
         stream << (*this)(i, j);
         res += stream.str() + " ";
      }
      res += "\n";
   }

   return res;
}

void pmat::Matrix::insertRow(const int &row, const double &value) {
   int initialPosition{0};
   if (row < 0)
      initialPosition = -1;
   else
      initialPosition = row >= this->rowSize()
                            ? this->vectorIndex(this->rowSize() - 1, this->columnSize() - 1)
                            : this->vectorIndex(row, this->columnSize() - 1);

   _matrix.insertValues(initialPosition, value, this->columnSize());
   _rowSize++;
}

void pmat::Matrix::insertColumn(const int &col, const double &value) {
   int initialPosition{0};
   if (col < 0)
      initialPosition =
          this->vectorIndex(this->rowSize() - 1, this->columnSize() - 1) - this->columnSize();
   else
      initialPosition = col >= this->columnSize()
                            ? this->vectorIndex(this->rowSize() - 1, this->columnSize() - 1)
                            : this->vectorIndex(this->rowSize() - 1, col);

   _matrix.pushBack(initialPosition, this->columnSize(), value);
   _columnSize++;
}
