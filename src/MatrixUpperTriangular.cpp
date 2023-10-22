#include "MatrixUpperTriangular.h"
#include "Messages.h"
#include "utils.h"
#include <random>
#include <stdexcept>

double pmat::MatrixUpperTriangular::operator()(const int &row, const int &column) const {
   if (row >= this->size() || column >= this->size())
      throw std::invalid_argument(pmat::messages::INDEX_OUT);

   return column < row ? pmat::utils::ZERO : this->vectorElement(row, column);
}

double pmat::MatrixUpperTriangular::dotProduct(const Matrix &matrix) const {
   if (matrix.rowSize() != this->size() || matrix.columnSize() != this->size())
      throw std::invalid_argument(pmat::messages::NONCOMPT_SIZE_ARG);

   double res = 0.0;
   for (int i = 0; i < this->size(); i++)
      for (int j = i; j < this->size(); j++)
         res += (*this)(i, j) * matrix(i, j);

   return res;
}

pmat::MatrixUpperTriangular
pmat::MatrixUpperTriangular::operator+(const MatrixUpperTriangular &matrix) const {
   MatrixUpperTriangular res{this->size()};
   for (int i = 0; i < this->size(); i++)
      for (int j = i; j < this->size(); j++)
         res.setValue((*this)(i, j) + matrix(i, j), i, j);

   return res;
}

void pmat::MatrixUpperTriangular::addBy(const MatrixUpperTriangular &matrix) {
   for (int i = 0; i < this->size(); i++)
      for (int j = i; j < this->size(); j++)
         this->setValue((*this)(i, j) + matrix(i, j), i, j);
}

pmat::MatrixUpperTriangular
pmat::MatrixUpperTriangular::operator-(const MatrixUpperTriangular &matrix) const {
   MatrixUpperTriangular res{this->size()};
   for (int i = 0; i < this->size(); i++)
      for (int j = i; j < this->size(); j++)
         res.setValue((*this)(i, j) - matrix(i, j), i, j);

   return res;
}

void pmat::MatrixUpperTriangular::subtractBy(const MatrixUpperTriangular &matrix) {
   for (int i = 0; i < this->size(); i++)
      for (int j = i; j < this->size(); j++)
         this->setValue((*this)(i, j) - matrix(i, j), i, j);
}

pmat::MatrixUpperTriangular pmat::MatrixUpperTriangular::operator*(const double &scalar) const {
   MatrixUpperTriangular res{this->size()};
   for (int i = 0; i < this->size(); i++)
      for (int j = i; j < this->size(); j++)
         res.setValue((*this)(i, j) * scalar, i, j);

   return res;
}

pmat::MatrixSquare pmat::MatrixUpperTriangular::operator*(const MatrixSquare &matrix) const {
   return MatrixSquare::operator*(matrix);
}

void pmat::MatrixUpperTriangular::multiplyBy(const double &scalar) {
   for (int i = 0; i < this->size(); i++)
      for (int j = i; j < this->size(); j++)
         this->setValue((*this)(i, j) * scalar, i, j);
}

pmat::MatrixSquare pmat::MatrixUpperTriangular::operator+(const MatrixSquare &matrix) const {
   return MatrixSquare::operator+(matrix);
}

pmat::MatrixSquare pmat::MatrixUpperTriangular::operator-(const MatrixSquare &matrix) const {
   return MatrixSquare::operator-(matrix);
}

pmat::Vector pmat::MatrixUpperTriangular::operator*(const Vector &vector) const {
   return MatrixSquare::operator*(vector);
}

pmat::MatrixUpperTriangular
pmat::MatrixUpperTriangular::operator*(const MatrixUpperTriangular &matrix) const {
   if (matrix.size() != this->size())
      throw std::invalid_argument(pmat::messages::NONCOMPT_SIZE_ARG);

   MatrixUpperTriangular resp{this->size()};
   for (int i = 0; i < this->size(); i++)
      for (int j = i; j < matrix.columnSize(); j++) {
         double aux = pmat::utils::ZERO;
         for (int k = i; k < this->columnSize(); k++)
            aux += (*this)(i, k) * matrix(k, j);
         resp.setValue(aux, i, j);
      }

   return resp;
}

pmat::MatrixSquare pmat::MatrixUpperTriangular::operator*(const MatrixTriangular &matrix) const {
   return MatrixSquare{MatrixSquare::operator*(matrix)};
}

pmat::MatrixLowerTriangular pmat::MatrixUpperTriangular::getTranspose() const {
   MatrixLowerTriangular resp(this->size());
   for (int i = 0; i < this->size(); i++)
      for (int j = 0; j <= i; j++)
         resp.setValue((*this)(j, i), i, j);

   return resp;
}

void pmat::MatrixUpperTriangular::swapRows(const int &rowA, const int &rowB, const int &startColumn,
                                           const int &endColumn) {
   if (startColumn < rowA || startColumn < rowB)
      throw std::out_of_range(messages::INDEX_OUT);

   Matrix::swapRows(rowA, rowB, startColumn, endColumn);
}

void pmat::MatrixUpperTriangular::swapColumns(const int &colA, const int &colB, const int &startRow,
                                              const int &endRow) {
   if (endRow > colA || endRow > colB)
      throw std::out_of_range(messages::INDEX_OUT);

   Matrix::swapColumns(colA, colB, startRow, endRow);
}

void pmat::MatrixUpperTriangular::fillWithRandomValues(const double &min, const double &max) {
   std::uniform_real_distribution<double> dist(min, max);
   std::mt19937 rng(std::random_device{}());

   for (int i = 0; i < this->size(); i++)
      for (int j = i; j < this->size(); j++)
         this->setValue(dist(rng), i, j);
}

pmat::MatrixUpperTriangular pmat::MatrixUpperTriangular::inverse() {
   if (!this->isInvertible())
      throw std::logic_error(messages::MATRIX_SINGULAR);

   MatrixUpperTriangular resp(this->size());
   this->findInverseByBackSubstitution(*this, resp);

   return resp;
}
