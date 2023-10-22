#include "MatrixSymmetry.h"

pmat::MatrixSymmetry::MatrixSymmetry(const MatrixSymmetry &matrix) {
   this->copyMembers(matrix);
}

int pmat::MatrixSymmetry::length() const {
   return (this->size() * this->size() + this->size()) / 2;
}
