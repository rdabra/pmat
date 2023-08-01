#include "MatrixSymmetric.h"
#include <random>

double pmat::MatrixSymmetric::operator()(const unsigned &row, const unsigned &column) const {
   // TODO	validateIndex(rowIndex, columnIndex);
   return column > row ? this->vectorElement(column, row) : this->vectorElement(row, column);
}

pmat::MatrixSymmetric pmat::MatrixSymmetric::operator+(const MatrixSymmetric &matrix) const {
   MatrixSymmetric res{this->size()};
   for (unsigned i = 0; i < this->size(); i++)
      for (unsigned j = 0; j <= i; j++)
         res.setValue((*this)(i, j) + matrix(i, j), i, j);
   return res;
}

void pmat::MatrixSymmetric::addBy(const MatrixSymmetric &matrix) {
   for (unsigned i = 0; i < this->size(); i++)
      for (unsigned j = 0; j <= i; j++)
         this->setValue((*this)(i, j) + matrix(i, j), i, j);
}

pmat::MatrixSymmetric pmat::MatrixSymmetric::operator-(const MatrixSymmetric &matrix) const {
   MatrixSymmetric res{this->size()};
   for (unsigned i = 0; i < this->size(); i++)
      for (unsigned j = 0; j <= i; j++)
         res.setValue((*this)(i, j) - matrix(i, j), i, j);
   return res;
}

void pmat::MatrixSymmetric::subtractBy(const MatrixSymmetric &matrix) {
   for (unsigned i = 0; i < this->size(); i++)
      for (unsigned j = 0; j <= i; j++)
         this->setValue((*this)(i, j) - matrix(i, j), i, j);
}

pmat::MatrixSymmetric pmat::MatrixSymmetric::operator*(const double &scalar) const {
   MatrixSymmetric res{this->size()};
   for (unsigned i = 0; i < this->size(); i++)
      for (unsigned j = 0; j <= i; j++)
         res.setValue((*this)(i, j) * scalar, i, j);
   return res;
}

pmat::MatrixSquare pmat::MatrixSymmetric::operator*(const MatrixSymmetric &matrix) const {
   return MatrixSquare::operator*(matrix);
}

void pmat::MatrixSymmetric::multiplyBy(const double &scalar) {
   for (unsigned i = 0; i < this->size(); i++)
      for (unsigned j = 0; j <= i; j++)
         this->setValue((*this)(i, j) * scalar, i, j);
}

void pmat::MatrixSymmetric::fillRandomly(const double &min, const double &max) {
   std::uniform_real_distribution<double> dist(min, max);
   std::mt19937 rng(std::random_device{}());

   for (unsigned i = 0; i < this->size(); i++)
      for (unsigned j = 0; j <= i; j++)
         this->setValue(dist(rng), i, j);
}
