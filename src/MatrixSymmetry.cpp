#include "MatrixSymmetry.h"

int pmat::MatrixSymmetry::vectorIndex(const int &i, const int &j) const {
   return (i * (i + 1)) / 2 + j;
}

pmat::MatrixSymmetry::MatrixSymmetry(const MatrixSymmetry &matrix) {
   this->copyMembers(matrix);
}

int pmat::MatrixSymmetry::length() const {
   return (this->size() * this->size() + this->size()) / 2;
}
