#include "Matrix.h"
#include "utils.h"
#include <random>
#include <vector>

pmat::Matrix::Matrix(const unsigned &rowSize, const unsigned &columnSize)
    : _rowSize{rowSize}, _columnSize{columnSize} {
   _matrix.resize(this->rowSize() * this->columnSize());
}

pmat::Matrix::Matrix(const std::string &fileName) {
   // TODO Implementar este construtor
}

void pmat::Matrix::resize(const unsigned &rowSize, const unsigned &columnSize) {
   _matrix.clear();
   _rowSize = rowSize;
   _columnSize = columnSize;
   _matrix.resize(this->size());
}

void pmat::Matrix::setValue(const double &value, const unsigned &row, const unsigned &column) {
   _matrix[this->getVectorIndex(row, column)] = value;
}

double pmat::Matrix::operator()(const unsigned &row, const unsigned &column) const {
   return _matrix[this->getVectorIndex(row, column)];
}

pmat::Matrix &pmat::Matrix::operator=(const Matrix &matrix) {
   if (this != &matrix) {
      _rowSize = matrix.rowSize();
      _columnSize = matrix.columnSize();
      _matrix.clear();
      _matrix = matrix._matrix;
   }

   return *this;
}

pmat::Matrix &pmat::Matrix::operator=(Matrix &&matrix) noexcept {
   _rowSize = matrix.rowSize();
   _columnSize = matrix.columnSize();
   _matrix.clear();
   _matrix = std::move(matrix._matrix);
   matrix.~Matrix();

   return *this;
}

bool pmat::Matrix::operator==(const Matrix &matrix) const {
   if (this->rowSize() == matrix.rowSize() && this->columnSize() == matrix.columnSize())
      return _matrix == matrix._matrix;

   return false;
}

double pmat::Matrix::dotProduct(const Matrix &matrix) const {
   // TODO Domensões iguais
   double resp = pmat::utils::ZERO;
   for (unsigned i = 0; i < this->rowSize(); i++)
      for (unsigned j = 0; j < this->columnSize(); j++)
         resp += (*this)(i, j) * matrix(i, j);

   return resp;
}

pmat::Matrix pmat::Matrix::operator+(const Matrix &matrix) const {
   // TODO Domensões iguais
   Matrix resp{};
   resp._rowSize = this->rowSize();
   resp._columnSize = this->columnSize();
   for (unsigned i = 0; i < this->rowSize(); i++)
      for (unsigned j = 0; j < this->columnSize(); j++)
         resp.setValue((*this)(i, j) + matrix(i, j), i, j);

   return resp;
}

void pmat::Matrix::addBy(const Matrix &matrix) {
   // TODO Domensões iguais
   for (unsigned i = 0; i < this->rowSize(); i++)
      for (unsigned j = 0; j < this->columnSize(); j++)
         this->setValue((*this)(i, j) + matrix(i, j), i, j);
}

pmat::Matrix pmat::Matrix::operator-(const Matrix &matrix) const {
   // TODO Domensões iguais
   Matrix resp{this->rowSize(), this->columnSize()};
   for (unsigned i = 0; i < this->rowSize(); i++)
      for (unsigned j = 0; j < this->columnSize(); j++)
         resp.setValue((*this)(i, j) - matrix(i, j), i, j);

   return resp;
}

void pmat::Matrix::subtractBy(const Matrix &matrix) {
   // TODO Domensões iguais
   for (unsigned i = 0; i < this->rowSize(); i++)
      for (unsigned j = 0; j < this->columnSize(); j++)
         this->setValue((*this)(i, j) - matrix(i, j), i, j);
}

pmat::Matrix pmat::Matrix::operator*(const Matrix &matrix) const {
   // TODO O numero de colunas desta matriz deve ser igual ao numero de linhas da outra
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
   // TODO O vetor não pode ser maior que o numero de colunas
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
   for (unsigned i = 0; i < resp.size(); i++)
      resp._matrix.emplace_back(scalar * _matrix[i]);

   return resp;
}

void pmat::Matrix::multiplyBy(const double &scalar) {
   for (unsigned i = 0; i < this->size(); i++)
      _matrix.emplace_back(scalar * _matrix[i]);
}

pmat::Matrix pmat::Matrix::multiplyHadamardBy(const Matrix &matrix) const {
   // TODO mesmas dimensoes
   Matrix resp{matrix.rowSize(), matrix.columnSize()};
   for (unsigned i = 0; i < resp.rowSize(); i++)
      for (unsigned j = 0; j < resp.columnSize(); j++)
         resp.setValue((*this)(i, j) * matrix(i, j), i, j);

   return resp;
}

void pmat::Matrix::multiplyRowBy(const unsigned &row, const double &scalar) {
   // TODO indice da linha correto
   for (unsigned j = 0; j < this->columnSize(); j++)
      this->setValue((*this)(row, j) * scalar, row, j);
}

void pmat::Matrix::multiplyColumnBy(const unsigned &column, const double &scalar) {
   // TODO indice da coluna correto
   for (unsigned i = 0; i < this->rowSize(); i++)
      this->setValue((*this)(i, column) * scalar, i, column);
}

void pmat::Matrix::swapRows(const unsigned &rowA, const unsigned &rowB, const unsigned &startColumn,
                            const unsigned &endColumn) {
   // TODO compatibiliar os indices
   for (unsigned j = startColumn; j <= endColumn; j++)
      _matrix[this->getVectorIndex(rowB, j)] = std::exchange(
          _matrix[this->getVectorIndex(rowA, j)], _matrix[this->getVectorIndex(rowB, j)]);
}

void pmat::Matrix::partialSwapColumns(const unsigned &columnA, const unsigned &columnB,
                                      const unsigned &startRow, const unsigned &endRow) {
   // TODO compatibiliar os indices
   for (unsigned i = startRow; i <= endRow; i++)
      _matrix[this->getVectorIndex(i, columnB)] = std::exchange(
          _matrix[this->getVectorIndex(i, columnA)], _matrix[this->getVectorIndex(i, columnB)]);
}

void pmat::Matrix::transpose() {
   _isTransposed = !_isTransposed;
   std::swap(_columnSize, _rowSize);
}

double pmat::Matrix::getFrobeniusNorm() const {
   return sqrt(this->dotProduct(*this));
}

void pmat::Matrix::fillRandomly(const double &min, const double &max) {
   // Type of random number distribution
   std::uniform_real_distribution<double> dist(min, max);

   // Mersenne Twister: Good quality random number generator initialized with non-deterministic
   // seeds
   std::mt19937 rng(std::random_device{}());

   for (unsigned i = 0; i < this->rowSize(); i++)
      for (unsigned j = 0; j < this->columnSize(); j++)
         this->setValue(dist(rng), i, j);
}

pmat::Vector pmat::Matrix::extractRow(const unsigned &row) const {
   // TODO compatibilizar o indice
   Vector resp{};
   for (unsigned j = 0; j < this->columnSize(); j++)
      resp.emplaceBack((*this)(row, j));

   return resp;
}

pmat::Vector pmat::Matrix::extractColumn(const unsigned &column) const {
   Vector resp{};
   for (unsigned i = 0; i < this->rowSize(); i++)
      resp.emplaceBack((*this)(i, column));

   return resp;
}

unsigned pmat::Matrix::occurrences(const double &value) const {
   unsigned res{0};
   for (unsigned i = 0; i < this->size(); i++)
      if (pmat::utils::areEqual(_matrix[i], value))
         res++;

   return res;
}

unsigned pmat::Matrix::occurrencesInRow(const unsigned row, const double &value) const {
   // TODO compatibilizar o indice
   unsigned res{0};
   for (unsigned j = 0; j < this->columnSize(); j++)
      if (pmat::utils::areEqual((*this)(row, j), value))
         res++;

   return res;
}

unsigned pmat::Matrix::occurrencesInColumn(const unsigned column, const double &value) const {
   // TODO compatibilizar o indice
   unsigned res{0};
   for (unsigned i = 0; i < this->rowSize(); i++)
      if (pmat::utils::areEqual((*this)(i, column), value))
         res++;

   return res;
}
