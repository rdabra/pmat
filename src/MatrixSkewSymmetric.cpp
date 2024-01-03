#include "MatrixSkewSymmetric.h"
#include "Messages.h"
#include "pmatUtils.h"
#include <random>
#include <stdexcept>

double pmat::MatrixSkewSymmetric::at(const int &row, const int &column) const {
   if (row >= this->rowSize() || column >= this->columnSize())
      throw std::invalid_argument(pmat::messages::INDEX_OUT);

   double aux = this->isTransposed() ? pmat::utils::MINUS_ONE : pmat::utils::ONE;
   double val = column > row ? pmat::utils::MINUS_ONE * this->vectorElement(column, row)
                             : this->vectorElement(row, column);
   return val * aux;
}

pmat::MatrixSkewSymmetric
pmat::MatrixSkewSymmetric::operator+(const MatrixSkewSymmetric &matrix) const {
   MatrixSkewSymmetric res{this->size()};
   for (int i = 0; i < this->size(); i++)
      for (int j = 0; j <= i; j++)
         res.assignNoCheck((*this)(i, j) + matrix(i, j), i, j);
   return res;
}

pmat::MatrixSquare pmat::MatrixSkewSymmetric::operator+(const MatrixSymmetry &matrix) const {
   return MatrixSquare::operator+(matrix);
}

void pmat::MatrixSkewSymmetric::operator+=(const MatrixSkewSymmetric &matrix) {
   for (int i = 0; i < this->size(); i++)
      for (int j = 0; j <= i; j++)
         this->assignNoCheck((*this)(i, j) + matrix(i, j), i, j);
}

void pmat::MatrixSkewSymmetric::addBy(const MatrixSkewSymmetric &matrix) {
   (*this) += matrix;
}

pmat::MatrixSkewSymmetric
pmat::MatrixSkewSymmetric::operator-(const MatrixSkewSymmetric &matrix) const {
   MatrixSkewSymmetric res{this->size()};
   for (int i = 0; i < this->size(); i++)
      for (int j = 0; j <= i; j++)
         res.assignNoCheck((*this)(i, j) - matrix(i, j), i, j);
   return res;
}

pmat::MatrixSquare pmat::MatrixSkewSymmetric::operator-(const MatrixSymmetry &matrix) const {
   return MatrixSquare::operator-(matrix);
}

void pmat::MatrixSkewSymmetric::operator-=(const MatrixSkewSymmetric &matrix) {
   for (int i = 0; i < this->size(); i++)
      for (int j = 0; j <= i; j++)
         this->assignNoCheck((*this)(i, j) - matrix(i, j), i, j);
}

void pmat::MatrixSkewSymmetric::subtractBy(const MatrixSkewSymmetric &matrix) {
   (*this) -= matrix;
}

pmat::MatrixSkewSymmetric pmat::MatrixSkewSymmetric::operator*(const double &scalar) const {
   MatrixSkewSymmetric res{this->size()};
   for (int i = 0; i < this->size(); i++)
      for (int j = 0; j <= i; j++)
         res.assignNoCheck((*this)(i, j) * scalar, i, j);
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

void pmat::MatrixSkewSymmetric::operator*=(const double &scalar) {
   for (int i = 0; i < this->size(); i++)
      for (int j = 0; j <= i; j++)
         this->assignNoCheck((*this)(i, j) * scalar, i, j);
}

void pmat::MatrixSkewSymmetric::transpose() {
   Matrix::transpose();
}

void pmat::MatrixSkewSymmetric::fillWithRandomValues(const double &min, const double &max) {
   std::uniform_real_distribution<double> dist(min, max);
   std::mt19937 rng(std::random_device{}());

   for (int i = 0; i < this->size(); i++)
      for (int j = 0; j <= i; j++)
         this->assignNoCheck(dist(rng), i, j);
}
