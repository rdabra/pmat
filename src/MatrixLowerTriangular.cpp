#include "MatrixLowerTriangular.h"
#include "MatrixUpperTriangular.h"
#include "Messages.h"
#include "pmatUtils.h"
#include <random>
#include <stdexcept>

double pmat::MatrixLowerTriangular::operator()(const int &row, const int &column) const {
   if (row >= this->size() || column >= this->size())
      throw std::invalid_argument(pmat::messages::INDEX_OUT);

   return column > row ? pmat::utils::ZERO : this->vectorElement(row, column);
}

double pmat::MatrixLowerTriangular::dotProduct(const Matrix &matrix) const {
   if (matrix.rowSize() != this->size() || matrix.columnSize() != this->size())
      throw std::invalid_argument(pmat::messages::NONCOMPT_SIZE_ARG);

   double resp = 0.0;
   for (int i = 0; i < this->size(); i++)
      for (int j = 0; j <= i; j++)
         resp += (*this)(i, j) * matrix(i, j);

   return resp;
}

pmat::MatrixLowerTriangular
pmat::MatrixLowerTriangular::operator+(const MatrixLowerTriangular &matrix) const {
   MatrixLowerTriangular res{this->size()};
   for (int i = 0; i < this->size(); i++)
      for (int j = 0; j <= i; j++)
         res.setValue((*this)(i, j) + matrix(i, j), i, j);
   return res;
}

void pmat::MatrixLowerTriangular::addBy(const MatrixLowerTriangular &matrix) {
   for (int i = 0; i < this->size(); i++)
      for (int j = 0; j <= i; j++)
         this->setValue((*this)(i, j) + matrix(i, j), i, j);
}

pmat::MatrixLowerTriangular
pmat::MatrixLowerTriangular::operator-(const MatrixLowerTriangular &matrix) const {
   MatrixLowerTriangular res{this->size()};
   for (int i = 0; i < this->size(); i++)
      for (int j = 0; j <= i; j++)
         res.setValue((*this)(i, j) - matrix(i, j), i, j);
   return res;
}

void pmat::MatrixLowerTriangular::subtractBy(const MatrixLowerTriangular &matrix) {
   for (int i = 0; i < this->size(); i++)
      for (int j = 0; j <= i; j++)
         this->setValue((*this)(i, j) - matrix(i, j), i, j);
}

pmat::MatrixLowerTriangular pmat::MatrixLowerTriangular::operator*(const double &scalar) const {
   MatrixLowerTriangular res{this->size()};
   for (int i = 0; i < this->size(); i++)
      for (int j = 0; j <= i; j++)
         res.setValue((*this)(i, j) * scalar, i, j);
   return res;
}

pmat::MatrixSquare pmat::MatrixLowerTriangular::operator*(const MatrixSquare &matrix) const {
   return MatrixSquare::operator*(matrix);
}

void pmat::MatrixLowerTriangular::multiplyBy(const double &scalar) {
   for (int i = 0; i < this->size(); i++)
      for (int j = 0; j <= i; j++)
         this->setValue((*this)(i, j) * scalar, i, j);
}

pmat::MatrixSquare pmat::MatrixLowerTriangular::operator+(const MatrixSquare &matrix) const {
   return MatrixSquare::operator+(matrix);
}

pmat::MatrixSquare pmat::MatrixLowerTriangular::operator-(const MatrixSquare &matrix) const {
   return MatrixSquare::operator-(matrix);
}

pmat::MatrixSquare pmat::MatrixLowerTriangular::operator*(const MatrixTriangular &matrix) const {
   return MatrixSquare{MatrixSquare::operator*(matrix)};
}

pmat::MatrixLowerTriangular
pmat::MatrixLowerTriangular::operator*(const MatrixLowerTriangular &matrix) const {
   if (matrix.size() != this->size())
      throw std::invalid_argument(pmat::messages::NONCOMPT_SIZE_ARG);

   MatrixLowerTriangular resp{this->size()};
   for (int i = 0; i < this->size(); i++)
      for (int j = 0; j <= i; j++) {
         double aux = pmat::utils::ZERO;
         for (int k = 0; k <= i; k++)
            aux += (*this)(i, k) * matrix(k, j);
         resp.setValue(aux, i, j);
      }

   return resp;
}

pmat::Vector pmat::MatrixLowerTriangular::operator*(const Vector &vector) const {
   return MatrixSquare::operator*(vector);
}

pmat::MatrixUpperTriangular pmat::MatrixLowerTriangular::getTranspose() const {
   MatrixUpperTriangular resp(this->size());
   for (int i = 0; i < this->size(); i++)
      for (int j = i; j < this->size(); j++)
         resp.setValue((*this)(j, i), i, j);
   return resp;
}

void pmat::MatrixLowerTriangular::swapRows(const int &rowA, const int &rowB, const int &startColumn,
                                           const int &endColumn) {

   if (endColumn > rowA || endColumn > rowB)
      throw std::out_of_range(messages::INDEX_OUT);

   Matrix::swapRows(rowA, rowB, startColumn, endColumn);
}

void pmat::MatrixLowerTriangular::swapColumns(const int &colA, const int &colB, const int &startRow,
                                              const int &endRow) {
   if (colA > startRow || colB > startRow)
      throw std::out_of_range(messages::INDEX_OUT);

   Matrix::swapColumns(colA, colB, startRow, endRow);
}
void pmat::MatrixLowerTriangular::fillWithRandomValues(const double &min, const double &max) {
   std::uniform_real_distribution<double> dist(min, max);
   std::mt19937 rng(std::random_device{}());

   for (int i = 0; i < this->size(); i++)
      for (int j = 0; j <= i; j++)
         this->setValue(dist(rng), i, j);
}

pmat::MatrixLowerTriangular pmat::MatrixLowerTriangular::inverse() {
   if (!this->isInvertible())
      throw std::logic_error(messages::MATRIX_SINGULAR);

   MatrixLowerTriangular resp(this->size());
   this->findInverseByBackSubstitution(*this, resp);

   return resp;
}
