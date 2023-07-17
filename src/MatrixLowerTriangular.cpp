#include "MatrixLowerTriangular.h"
#include "MatrixUpperTriangular.h"
#include "utils.h"
#include <random>

pmat::MatrixLowerTriangular::MatrixLowerTriangular(const unsigned &size) {
   _columnSize = size;
   _rowSize = size;
   _matrix.resize(this->length());
}

pmat::MatrixLowerTriangular::MatrixLowerTriangular(const MatrixSquare &matrix) {
   _columnSize = matrix.size();
   _rowSize = matrix.size();
   _matrix.resize(this->length());
   for (unsigned i = 0; i < this->size(); i++)
      for (unsigned j = 0; j <= i; j++)
         this->setValue(matrix(i, j), i, j);
}

pmat::MatrixLowerTriangular &
pmat::MatrixLowerTriangular::operator=(const MatrixLowerTriangular &matrix) {
   if (this != &matrix) {
      _rowSize = matrix.rowSize();
      _columnSize = matrix.columnSize();
      _matrix.clear();
      _matrix = matrix._matrix;
   }

   return *this;
}

pmat::MatrixLowerTriangular &
pmat::MatrixLowerTriangular::operator=(MatrixLowerTriangular &&matrix) {
   _rowSize = matrix.rowSize();
   _columnSize = matrix.columnSize();
   _matrix.clear();
   _matrix = std::move(matrix._matrix);
   matrix.~MatrixLowerTriangular();

   return *this;
}

double pmat::MatrixLowerTriangular::operator()(const unsigned &row, const unsigned &column) const {
   // TODO	validateIndex(rowIndex, columnIndex);

   return column > row ? pmat::utils::ZERO : _matrix[this->vectorIndex(row, column)];
}

void pmat::MatrixLowerTriangular::resize(const unsigned &size) {
   _matrix.clear();
   _columnSize = size;
   _rowSize = size;
   _matrix.resize(this->length());
}

double pmat::MatrixLowerTriangular::dotProduct(const Matrix &matrix) const {
   // TODO this->validateOperands(matrix);
   double resp = 0.0;
   for (unsigned i = 0; i < this->size(); i++)
      for (unsigned j = 0; j <= i; j++)
         resp += (*this)(i, j) * matrix(i, j);

   return resp;
}

pmat::MatrixLowerTriangular
pmat::MatrixLowerTriangular::operator+(const MatrixLowerTriangular &matrix) const {
   MatrixLowerTriangular res{this->size()};
   for (unsigned i = 0; i < this->size(); i++)
      for (unsigned j = 0; j <= i; j++)
         res.setValue((*this)(i, j) + matrix(i, j), i, j);
   return res;
}

void pmat::MatrixLowerTriangular::addBy(const MatrixLowerTriangular &matrix) {
   for (unsigned i = 0; i < this->size(); i++)
      for (unsigned j = 0; j <= i; j++)
         this->setValue((*this)(i, j) + matrix(i, j), i, j);
}

pmat::MatrixLowerTriangular
pmat::MatrixLowerTriangular::operator-(const MatrixLowerTriangular &matrix) const {
   MatrixLowerTriangular res{this->size()};
   for (unsigned i = 0; i < this->size(); i++)
      for (unsigned j = 0; j <= i; j++)
         res.setValue((*this)(i, j) - matrix(i, j), i, j);
   return res;
}

void pmat::MatrixLowerTriangular::subtractBy(const MatrixLowerTriangular &matrix) {
   for (unsigned i = 0; i < this->size(); i++)
      for (unsigned j = 0; j <= i; j++)
         this->setValue((*this)(i, j) - matrix(i, j), i, j);
}

pmat::MatrixLowerTriangular pmat::MatrixLowerTriangular::operator*(const double &scalar) const {
   MatrixLowerTriangular res{this->size()};
   for (unsigned i = 0; i < this->size(); i++)
      for (unsigned j = 0; j <= i; j++)
         res.setValue((*this)(i, j) * scalar, i, j);
   return res;
}

void pmat::MatrixLowerTriangular::multiplyBy(const double &scalar) {
   for (unsigned i = 0; i < this->size(); i++)
      for (unsigned j = 0; j <= i; j++)
         this->setValue((*this)(i, j) * scalar, i, j);
}

pmat::MatrixUpperTriangular pmat::MatrixLowerTriangular::getTranspose() const {
   MatrixUpperTriangular resp(this->size());
   for (unsigned i = 0; i < this->size(); i++)
      for (unsigned j = i; j < this->size(); j++)
         resp.setValue((*this)(j, i), i, j);
   return resp;
}

void pmat::MatrixLowerTriangular::swapRows(const unsigned &rowA, const unsigned &rowB,
                                           const unsigned &startColumn, const unsigned &endColumn) {

   // TODO if (endColumn > rowIndexA || endColumn > rowIndexB)
   // 	throw std::out_of_range(messages::INDEX_OUT);
   Matrix::swapRows(rowA, rowB, startColumn, endColumn);
}

void pmat::MatrixLowerTriangular::swapColumns(const unsigned &colA, const unsigned &colB,
                                              const unsigned &startRow, const unsigned &endRow) {
   // TODO if (columnIndexA > startRow || columnIndexB > startRow)
   // 	throw std::out_of_range(messages::INDEX_OUT);

   Matrix::swapColumns(colA, colB, startRow, endRow);
}
void pmat::MatrixLowerTriangular::fillRandomly(const double &min, const double &max) {
   std::uniform_real_distribution<double> dist(min, max);
   std::mt19937 rng(std::random_device{}());

   for (unsigned i = 0; i < this->size(); i++)
      for (unsigned j = 0; j <= i; j++)
         this->setValue(dist(rng), i, j);
}
