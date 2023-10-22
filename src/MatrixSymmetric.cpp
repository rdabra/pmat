#include "MatrixSymmetric.h"
#include "DecompositionCholesky.h"
#include "Messages.h"
#include <random>
#include <stdexcept>


double pmat::MatrixSymmetric::operator()(const int &row, const int &column) const {
   if (row >= this->size() || column >= this->size())
      throw std::invalid_argument(pmat::messages::INDEX_OUT);

   return column > row ? this->vectorElement(column, row) : this->vectorElement(row, column);
}

pmat::MatrixSymmetric pmat::MatrixSymmetric::operator+(const MatrixSymmetric &matrix) const {
   MatrixSymmetric res{this->size()};
   for (int i = 0; i < this->size(); i++)
      for (int j = 0; j <= i; j++)
         res.setValue((*this)(i, j) + matrix(i, j), i, j);
   return res;
}

pmat::MatrixSquare pmat::MatrixSymmetric::operator+(const MatrixSymmetry &matrix) const {
   return MatrixSquare::operator+(matrix);
}

void pmat::MatrixSymmetric::addBy(const MatrixSymmetric &matrix) {
   for (int i = 0; i < this->size(); i++)
      for (int j = 0; j <= i; j++)
         this->setValue((*this)(i, j) + matrix(i, j), i, j);
}

pmat::MatrixSymmetric pmat::MatrixSymmetric::operator-(const MatrixSymmetric &matrix) const {
   MatrixSymmetric res{this->size()};
   for (int i = 0; i < this->size(); i++)
      for (int j = 0; j <= i; j++)
         res.setValue((*this)(i, j) - matrix(i, j), i, j);
   return res;
}

pmat::MatrixSquare pmat::MatrixSymmetric::operator-(const MatrixSymmetry &matrix) const {
   return MatrixSquare::operator-(matrix);
}

void pmat::MatrixSymmetric::subtractBy(const MatrixSymmetric &matrix) {
   for (int i = 0; i < this->size(); i++)
      for (int j = 0; j <= i; j++)
         this->setValue((*this)(i, j) - matrix(i, j), i, j);
}

pmat::MatrixSymmetric pmat::MatrixSymmetric::operator*(const double &scalar) const {
   MatrixSymmetric res{this->size()};
   for (int i = 0; i < this->size(); i++)
      for (int j = 0; j <= i; j++)
         res.setValue((*this)(i, j) * scalar, i, j);
   return res;
}

pmat::MatrixSquare pmat::MatrixSymmetric::operator*(const MatrixSymmetric &matrix) const {
   return MatrixSquare::operator*(matrix);
}

pmat::Matrix pmat::MatrixSymmetric::operator*(const Matrix &matrix) const {
   return Matrix::operator*(matrix);
}

pmat::Vector pmat::MatrixSymmetric::operator*(const Vector &vector) const {
   return MatrixSquare::operator*(vector);
}

void pmat::MatrixSymmetric::multiplyBy(const double &scalar) {
   for (int i = 0; i < this->size(); i++)
      for (int j = 0; j <= i; j++)
         this->setValue((*this)(i, j) * scalar, i, j);
}

void pmat::MatrixSymmetric::fillWithRandomValues(const double &min, const double &max) {
   std::uniform_real_distribution<double> dist(min, max);
   std::mt19937 rng(std::random_device{}());

   for (int i = 0; i < this->size(); i++)
      for (int j = 0; j <= i; j++)
         this->setValue(dist(rng), i, j);
}

pmat::DecompositionCholesky pmat::MatrixSymmetric::decomposeToCholesky() {
   DecompositionCholesky res{*this};
   return res;
}
