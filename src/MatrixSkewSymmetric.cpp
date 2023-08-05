#include "MatrixSkewSymmetric.h"
#include "utils.h"
#include <random>

double pmat::MatrixSkewSymmetric::operator()(const unsigned &row, const unsigned &column) const {
   // TODO	validateIndex(rowIndex, columnIndex);
   double aux = this->isTransposed() ? pmat::utils::MINUS_ONE : pmat::utils::ONE;
   double val = column > row ? pmat::utils::MINUS_ONE * this->vectorElement(column, row)
                             : this->vectorElement(row, column);
   return val * aux;
}

pmat::MatrixSkewSymmetric
pmat::MatrixSkewSymmetric::operator+(const MatrixSkewSymmetric &matrix) const {
   MatrixSkewSymmetric res{this->size()};
   for (unsigned i = 0; i < this->size(); i++)
      for (unsigned j = 0; j <= i; j++)
         res.setValue((*this)(i, j) + matrix(i, j), i, j);
   return res;
}

pmat::MatrixSquare pmat::MatrixSkewSymmetric::operator+(const MatrixSymmetry &matrix) const {
   return MatrixSquare::operator+(matrix);
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

pmat::MatrixSquare pmat::MatrixSkewSymmetric::operator-(const MatrixSymmetry &matrix) const {
   return MatrixSquare::operator-(matrix);
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

pmat::MatrixSquare pmat::MatrixSkewSymmetric::operator*(const MatrixSkewSymmetric &matrix) const {
   return MatrixSquare::operator*(matrix);
}

pmat::Vector pmat::MatrixSkewSymmetric::operator*(const Vector &vector) const {
   return MatrixSquare::operator*(vector);
}

pmat::Matrix pmat::MatrixSkewSymmetric::operator*(const Matrix &matrix) const {
   return Matrix::operator*(matrix);
}

void pmat::MatrixSkewSymmetric::multiplyBy(const double &scalar) {
   for (unsigned i = 0; i < this->size(); i++)
      for (unsigned j = 0; j <= i; j++)
         this->setValue((*this)(i, j) * scalar, i, j);
}

void pmat::MatrixSkewSymmetric::transpose() {
   Matrix::transpose();
}

void pmat::MatrixSkewSymmetric::fillRandomly(const double &min, const double &max) {
   std::uniform_real_distribution<double> dist(min, max);
   std::mt19937 rng(std::random_device{}());

   for (unsigned i = 0; i < this->size(); i++)
      for (unsigned j = 0; j <= i; j++)
         this->setValue(dist(rng), i, j);
}
