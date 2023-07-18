#include "MatrixSkewSymmetric.h"
#include "utils.h"
#include <random>

pmat::MatrixSkewSymmetric::MatrixSkewSymmetric(const MatrixSquare &matrix) {
   this->initializeMembers(matrix.size(), matrix.size());
   for (unsigned i = 0; i < this->size(); i++)
      for (unsigned j = 0; j <= i; j++)
         this->setValue(matrix(i, j), i, j);
}

double pmat::MatrixSkewSymmetric::operator()(const unsigned &row, const unsigned &column) const {
   // TODO	validateIndex(rowIndex, columnIndex);
   return column > row ? pmat::utils::MINUS_ONE * this->vectorElement(column, row)
                       : this->vectorElement(row, column);
}

double pmat::MatrixSkewSymmetric::dotProduct(const Matrix &matrix) const {
   // TODO this->validateOperands(matrix);
   double resp = 0.0;
   for (unsigned i = 0; i < this->size(); i++)
      for (unsigned j = 0; j <= i; j++)
         resp += (*this)(i, j) * matrix(i, j);

   return resp;
}

pmat::MatrixSkewSymmetric
pmat::MatrixSkewSymmetric::operator+(const MatrixSkewSymmetric &matrix) const {
   MatrixSkewSymmetric res{this->size()};
   for (unsigned i = 0; i < this->size(); i++)
      for (unsigned j = 0; j <= i; j++)
         res.setValue((*this)(i, j) + matrix(i, j), i, j);
   return res;
}

void pmat::MatrixSkewSymmetric::addBy(const MatrixSkewSymmetric &matrix) {
   for (unsigned i = 0; i < this->size(); i++)
      for (unsigned j = 0; j <= i; j++)
         this->setValue((*this)(i, j) + matrix(i, j), i, j);
}

pmat::MatrixSkewSymmetric
pmat::MatrixSkewSymmetric::operator-(const MatrixSkewSymmetric &matrix) const {
   MatrixSkewSymmetric res{this->size()};
   for (unsigned i = 0; i < this->size(); i++)
      for (unsigned j = 0; j <= i; j++)
         res.setValue((*this)(i, j) - matrix(i, j), i, j);
   return res;
}

void pmat::MatrixSkewSymmetric::subtractBy(const MatrixSkewSymmetric &matrix) {
   for (unsigned i = 0; i < this->size(); i++)
      for (unsigned j = 0; j <= i; j++)
         this->setValue((*this)(i, j) - matrix(i, j), i, j);
}

pmat::MatrixSkewSymmetric pmat::MatrixSkewSymmetric::operator*(const double &scalar) const {
   MatrixSkewSymmetric res{this->size()};
   for (unsigned i = 0; i < this->size(); i++)
      for (unsigned j = 0; j <= i; j++)
         res.setValue((*this)(i, j) * scalar, i, j);
   return res;
}

void pmat::MatrixSkewSymmetric::multiplyBy(const double &scalar) {
   for (unsigned i = 0; i < this->size(); i++)
      for (unsigned j = 0; j <= i; j++)
         this->setValue((*this)(i, j) * scalar, i, j);
}

void pmat::MatrixSkewSymmetric::fillRandomly(const double &min, const double &max) {
   std::uniform_real_distribution<double> dist(min, max);
   std::mt19937 rng(std::random_device{}());

   for (unsigned i = 0; i < this->size(); i++)
      for (unsigned j = 0; j <= i; j++)
         this->setValue(dist(rng), i, j);
}
