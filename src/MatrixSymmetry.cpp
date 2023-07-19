#include "MatrixSymmetry.h"

pmat::MatrixSquare pmat::MatrixSymmetry::operator+(const MatrixSquare &matrix) const {
   return matrix + (*this);
}

pmat::MatrixSquare pmat::MatrixSymmetry::operator-(const MatrixSquare &matrix) const {
   MatrixSquare res(this->size());
   for (unsigned i = 0; i < this->size(); ++i) {
      for (unsigned j = 0; j < this->size(); ++j)
         res.setValue((*this)(i, j) - matrix(i, j), i, j);
   }

   return res;
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

pmat::MatrixSquare pmat::MatrixSymmetry::operator*(const MatrixSquare &matrix) const {
   return MatrixSquare{MatrixSquare::operator*(matrix)};
}

pmat::MatrixSquare pmat::MatrixSymmetry::operator*(const MatrixSymmetry &matrix) const {
   return MatrixSquare{MatrixSquare::operator*(matrix)};
}

pmat::Vector pmat::MatrixSymmetry::linearSolve(const Vector &rhs) {
   // TODO Implement linear solve
   return Vector{2};
}
