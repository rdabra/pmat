#include "MatrixSymmetry.h"

unsigned pmat::MatrixSymmetry::vectorIndex(const unsigned &i, const unsigned &j) const {
   return (i * (i + 1)) / 2 + j;
}

pmat::MatrixSymmetry::MatrixSymmetry(const MatrixSymmetry &matrix) {
   this->copyMembers(matrix);
}

unsigned pmat::MatrixSymmetry::length() const {
   return (this->size() * this->size() + this->size()) / 2;
}
