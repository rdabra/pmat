#include "MatrixSymmetry.h"

pmat::MatrixSymmetry::MatrixSymmetry(const MatrixSymmetry &matrix) {
   this->copyMembers(matrix);
}

pmat::MatrixSquare pmat::MatrixSymmetry::operator+(const MatrixSquare &matrix) const {
   return MatrixSquare::operator+(matrix);
}

pmat::MatrixSquare pmat::MatrixSymmetry::operator-(const MatrixSquare &matrix) const {
   return MatrixSquare::operator-(matrix);
   ;
}

pmat::MatrixSquare pmat::MatrixSymmetry::toMatrixSquare() const {
   MatrixSquare res(this->size());
   for (unsigned i = 0; i < this->size(); ++i) {
      for (unsigned j = 0; j < this->size(); ++j)
         res.setValue((*this)(i, j), i, j);
   }

   return res;
}

pmat::Matrix pmat::MatrixSymmetry::operator*(const Matrix &matrix) const {
   return Matrix{Matrix::operator*(matrix)};
}
