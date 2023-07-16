#include "MatrixSquare.h"
#include "utils.h"

pmat::MatrixSquare::MatrixSquare(Matrix &&matrix) {
   if (matrix.rowSize() == matrix.columnSize()) {
      Matrix{std::move(matrix)};
   } // TODO else throw alguma excecao
}

unsigned pmat::MatrixSquare::size() const {
   return this->rowSize();
}

pmat::MatrixSquare &pmat::MatrixSquare::operator=(const MatrixSquare &matrix) {
   if (this != &matrix) {
      Matrix::operator=(matrix);
   }

   return (*this);
}

pmat::MatrixSquare &pmat::MatrixSquare::operator=(MatrixSquare &&matrix) noexcept {
   Matrix::operator=(std::move(matrix));

   return (*this);
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

   // TODO	if (matrix.size() < this->size()) throw
   // std::logic_error(messages::NONCOMPT_ARG);

   MatrixSquare resp(matrix.size());

   const unsigned dif{matrix.size() - this->size()};
   const unsigned limInf{pos == SubMatrixPos::lower ? dif : 0};
   const unsigned limSup{pos == SubMatrixPos::lower ? matrix.size() : this->size()};

   for (unsigned i = 0; i < matrix.size(); ++i)
      for (unsigned j = 0; j < matrix.size(); ++j) {
         if (i < limInf || i >= limSup)
            resp.setValue(matrix(i, j), i, j);
         else {
            double aux{pmat::utils::ZERO};
            for (unsigned k = limInf; k < limSup; ++k)
               aux += (*this)(i - limInf, k - limInf) * matrix(k, j);
            resp.setValue(aux, i, j);
         }
      }

   return resp;
}

pmat::MatrixSquare pmat::MatrixSquare::operator*(const double &scalar) const {
   MatrixSquare res{Matrix::operator*(scalar)};

   return res;
}

double pmat::MatrixSquare::trace() const {
   double resp = pmat::utils::ZERO;
   for (unsigned i = 0; i < this->size(); i++)
      resp += (*this)(i, i);
   return resp;
}

void pmat::MatrixSquare::fillDiagonalWith(const double &value) {
   for (unsigned i = 0; i < this->size(); ++i)
      this->setValue(value, i, i);
}
