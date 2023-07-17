#include "MatrixUpperTriangular.h"
#include "MatrixLowerTriangular.h"
#include "utils.h"
#include <random>

pmat::MatrixUpperTriangular::MatrixUpperTriangular(const unsigned &size) {
   _columnSize = size;
   _rowSize = size;
   _matrix.resize(this->length());
}

pmat::MatrixUpperTriangular::MatrixUpperTriangular(const MatrixSquare &matrix) {
   _columnSize = matrix.size();
   _rowSize = matrix.size();
   _matrix.resize(this->length());
   for (unsigned i = 0; i < this->size(); i++)
      for (unsigned j = i; j < this->size(); j++)
         this->setValue(matrix(i, j), i, j);
}

pmat::MatrixUpperTriangular &
pmat::MatrixUpperTriangular::operator=(const MatrixUpperTriangular &matrix) {
   if (this != &matrix) {
      _rowSize = matrix.rowSize();
      _columnSize = matrix.columnSize();
      _matrix.clear();
      _matrix = matrix._matrix;
   }

   return *this;
}

pmat::MatrixUpperTriangular &
pmat::MatrixUpperTriangular::operator=(MatrixUpperTriangular &&matrix) {
   _rowSize = matrix.rowSize();
   _columnSize = matrix.columnSize();
   _matrix.clear();
   _matrix = std::move(matrix._matrix);
   matrix.~MatrixUpperTriangular();

   return *this;
}

double pmat::MatrixUpperTriangular::operator()(const unsigned &row, const unsigned &column) const {
   // TODO validateIndex(rowIndex, columnIndex);

   return column < row ? pmat::utils::ZERO : _matrix[this->vectorIndex(row, column)];
}

void pmat::MatrixUpperTriangular::resize(const unsigned &size) {
   _matrix.clear();
   _columnSize = size;
   _rowSize = size;
   _matrix.resize(this->length());
}

double pmat::MatrixUpperTriangular::dotProduct(const Matrix &matrix) const {
   // TODO this->validateOperands(matrix);
   double res = 0.0;
   for (unsigned i = 0; i < this->size(); i++)
      for (unsigned j = i; j < this->size(); j++)
         res += (*this)(i, j) * matrix(i, j);

   return res;
}

pmat::MatrixUpperTriangular
pmat::MatrixUpperTriangular::operator+(const MatrixUpperTriangular &matrix) const {
   MatrixLowerTriangular res{this->size()};
   for (unsigned i = 0; i < this->size(); i++)
      for (unsigned j = i; j < this->size(); j++)
         res.setValue((*this)(i, j) + matrix(i, j), i, j);

   return res;
}

void pmat::MatrixUpperTriangular::addBy(const MatrixUpperTriangular &matrix) {
   for (unsigned i = 0; i < this->size(); i++)
      for (unsigned j = i; j < this->size(); j++)
         this->setValue((*this)(i, j) + matrix(i, j), i, j);
}

pmat::MatrixUpperTriangular
pmat::MatrixUpperTriangular::operator-(const MatrixUpperTriangular &matrix) const {
   MatrixLowerTriangular res{this->size()};
   for (unsigned i = 0; i < this->size(); i++)
      for (unsigned j = i; j < this->size(); j++)
         res.setValue((*this)(i, j) - matrix(i, j), i, j);

   return res;
}

void pmat::MatrixUpperTriangular::subtractBy(const MatrixUpperTriangular &matrix) {
   for (unsigned i = 0; i < this->size(); i++)
      for (unsigned j = i; j < this->size(); j++)
         this->setValue((*this)(i, j) - matrix(i, j), i, j);
}

pmat::MatrixUpperTriangular pmat::MatrixUpperTriangular::operator*(const double &scalar) const {
   MatrixLowerTriangular res{this->size()};
   for (unsigned i = 0; i < this->size(); i++)
      for (unsigned j = i; j < this->size(); j++)
         res.setValue((*this)(i, j) * scalar, i, j);

   return res;
}

void pmat::MatrixUpperTriangular::multiplyBy(const double &scalar) {
   for (unsigned i = 0; i < this->size(); i++)
      for (unsigned j = i; j < this->size(); j++)
         this->setValue((*this)(i, j) * scalar, i, j);
}

pmat::MatrixLowerTriangular pmat::MatrixUpperTriangular::getTranspose() const {
   MatrixLowerTriangular resp(this->size());
   for (unsigned i = 0; i < this->size(); i++)
      for (unsigned j = 0; j <= i; j++)
         resp.setValue((*this)(j, i), i, j);

   return resp;
}

void pmat::MatrixUpperTriangular::swapRows(const unsigned &rowA, const unsigned &rowB,
                                           const unsigned &startColumn, const unsigned &endColumn) {

   // TODO if (startColumn < rowIndexA || startColumn < rowIndexB)
   //    throw std::out_of_range(messages::INDEX_OUT);
   Matrix::swapRows(rowA, rowB, startColumn, endColumn);
}

void pmat::MatrixUpperTriangular::swapColumns(const unsigned &colA, const unsigned &colB,
                                              const unsigned &startRow, const unsigned &endRow) {
   // TODO if (endRow > colA || endRow > colB)
   //    throw std::out_of_range(messages::INDEX_OUT);

   Matrix::swapColumns(colA, colB, startRow, endRow);
}

void pmat::MatrixUpperTriangular::fillRandomly(const double &min, const double &max) {
   std::uniform_real_distribution<double> dist(min, max);
   std::mt19937 rng(std::random_device{}());

   for (unsigned i = 0; i < this->size(); i++)
      for (unsigned j = i; j < this->size(); j++)
         this->setValue(dist(rng), i, j);
}
