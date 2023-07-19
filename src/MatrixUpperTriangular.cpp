#include "MatrixUpperTriangular.h"
#include "MatrixLowerTriangular.h"
#include "utils.h"
#include <random>

pmat::MatrixUpperTriangular::MatrixUpperTriangular(const MatrixSquare &matrix) {
   this->initializeMembers(matrix.size(), matrix.size());
   for (unsigned i = 0; i < this->size(); i++)
      for (unsigned j = i; j < this->size(); j++)
         this->setValue(matrix(i, j), i, j);
}

double pmat::MatrixUpperTriangular::operator()(const unsigned &row, const unsigned &column) const {
   // TODO validateIndex(rowIndex, columnIndex);

   return column < row ? pmat::utils::ZERO : this->vectorElement(row, column);
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

pmat::MatrixSquare pmat::MatrixUpperTriangular::toMatrixSquare() const {
   MatrixSquare res(this->size());
   for (unsigned i = 0; i < this->size(); i++)
      for (unsigned j = i; j < this->size(); j++)
         res.setValue((*this)(i, j), i, j);

   return res;
}

pmat::MatrixSquare pmat::MatrixUpperTriangular::operator+(const MatrixSquare &matrix) const {
   MatrixSquare res{this->size()};
   for (unsigned i = 0; i < this->size(); i++)
      for (unsigned j = i; j < this->size(); j++)
         res.setValue((*this)(i, j) + matrix(i, j), i, j);

   return res;
}

pmat::MatrixSquare pmat::MatrixUpperTriangular::operator-(const MatrixSquare &matrix) const {
   MatrixSquare res{this->size()};
   for (unsigned i = 0; i < this->size(); i++)
      for (unsigned j = i; j < this->size(); j++)
         res.setValue((*this)(i, j) - matrix(i, j), i, j);

   return res;
}

pmat::MatrixUpperTriangular
pmat::MatrixUpperTriangular::operator*(const MatrixUpperTriangular &matrix) const {
   // TODO O numero de colunas desta matriz deve ser igual ao numero de linhas da outra
   MatrixUpperTriangular resp{this->size()};
   for (unsigned i = 0; i < this->size(); i++)
      for (unsigned j = i; j < matrix.columnSize(); j++) {
         double aux = pmat::utils::ZERO;
         for (unsigned k = i; k < this->columnSize(); k++)
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
