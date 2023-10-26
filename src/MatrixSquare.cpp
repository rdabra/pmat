#include "MatrixSquare.h"
#include "DecompositionPLU.h"
#include "DecompositionPQR.h"
#include "DecompositionSAS.h"
#include "Messages.h"
#include "pmatUtils.h"
#include <stdexcept>

pmat::MatrixSquare::MatrixSquare(Matrix &&matrix) {
   if (matrix.rowSize() == matrix.columnSize()) {
      this->moveToThis(std::move(matrix));
   } else
      throw std::invalid_argument(pmat::messages::NONCOMPT_SIZE_ARG);
}

pmat::MatrixSquare::MatrixSquare(const MatrixSquare &matrix) {
   this->initializeMembers(matrix.size(), matrix.size(), matrix.isTransposed());
   for (int i = 0; i < matrix.size(); ++i)
      for (int j = 0; j < matrix.size(); ++j)
         (*this)(i, j) = matrix(i, j);
}

int pmat::MatrixSquare::size() const {
   return this->rowSize();
}

void pmat::MatrixSquare::resize(const int &size) {
   this->initializeMembers(size, size, false);
}

pmat::MatrixSquare pmat::MatrixSquare::operator+(const MatrixSquare &matrix) const {
   MatrixSquare res{Matrix::operator+(matrix)};

   return res;
}

pmat::MatrixSquare pmat::MatrixSquare::operator-(const MatrixSquare &matrix) const {
   MatrixSquare res{Matrix::operator-(matrix)};

   return res;
}

pmat::MatrixSquare pmat::MatrixSquare::operator*(const MatrixSquare &matrix) const {
   MatrixSquare res{Matrix::operator*(matrix)};

   return res;
}

pmat::MatrixSquare pmat::MatrixSquare::multiplyByBiggerMatrix(const MatrixSquare &matrix,
                                                              SubMatrixPos pos) {
   if (matrix.size() <= this->size())
      throw std::invalid_argument(messages::NONCOMPT_SIZE_ARG);

   MatrixSquare resp(matrix.size());

   const int dif{matrix.size() - this->size()};
   const int limInf{pos == SubMatrixPos::lower ? dif : 0};
   const int limSup{pos == SubMatrixPos::lower ? matrix.size() : this->size()};

   for (int i = 0; i < matrix.size(); ++i)
      for (int j = 0; j < matrix.size(); ++j) {
         if (i < limInf || i >= limSup)
            resp(i, j) = matrix(i, j);
         else {
            double aux{pmat::utils::ZERO};
            for (int k = limInf; k < limSup; ++k)
               aux += (*this)(i - limInf, k - limInf) * matrix(k, j);
            resp(i, j) = aux;
         }
      }

   return resp;
}

pmat::MatrixSquare pmat::MatrixSquare::operator*(const double &scalar) const {
   MatrixSquare res{Matrix::operator*(scalar)};

   return res;
}

pmat::Matrix pmat::MatrixSquare::operator*(const pmat::Matrix &matrix) const {
   return pmat::Matrix::operator*(matrix);
}

pmat::Vector pmat::MatrixSquare::operator*(const Vector &vector) const {
   return Matrix::operator*(vector);
}

double pmat::MatrixSquare::trace() const {
   double res = pmat::utils::ZERO;
   for (int i = 0; i < this->size(); i++)
      res += (*this)(i, i);

   return res;
}

void pmat::MatrixSquare::fillDiagonalWith(const double &value) {
   for (int i = 0; i < this->size(); ++i)
      (*this)(i, i) = value;
}

pmat::DecompositionPLU pmat::MatrixSquare::decomposeToPLU() const {
   DecompositionPLU res{*this};

   return res;
}

pmat::DecompositionSAS pmat::MatrixSquare::decomposeToSAS() const {
   DecompositionSAS res{*this};

   return res;
}

pmat::DecompositionPQR pmat::MatrixSquare::decomposeToPQR() const {
   DecompositionPQR res{*this};

   return res;
}

void pmat::MatrixSquare::insertRowColumn(const int &pos, const double &value) {
   Matrix::insertColumn(pos, value);
   Matrix::insertRow(pos, value);
}

void pmat::MatrixSquare::clearAndResize(const int &size) {
   Matrix::clearAndResize(size, size);
}
