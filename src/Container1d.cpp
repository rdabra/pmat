#include "Container1d.h"

pmat::Container1d &pmat::Container1d::operator=(const pmat::Container1d &container) {
   _ptrVector->resize(0);
   _ptrVector = std::make_unique<blitz::Array<double, 1>>(*container._ptrVector);

   return *this;
}

pmat::Container1d &pmat::Container1d::operator=(pmat::Container1d &&container) noexcept {
   _ptrVector->resize(0);
   _ptrVector = std::move(container._ptrVector);

   return *this;
}

pmat::Container1d::~Container1d() {
   _ptrVector->free();
}

pmat::Container1d::Container1d(const unsigned &size, const double &value)
    : _ptrVector{std::make_unique<blitz::Array<double, 1>>(size)} {
   *_ptrVector = value;
}

void pmat::Container1d::push_back(const double &value) {
   // Caution: narrowing from unsigned to int
   _ptrVector->resizeAndPreserve(_ptrVector->size() + 1);
   (*_ptrVector)(_ptrVector->size()) = value;
}

void pmat::Container1d::exchange(const unsigned &indexA, const unsigned &indexB) {
   // Caution: narrowing from unsigned to int
   (*_ptrVector)(indexB) = std::exchange((*_ptrVector)(indexA), (*_ptrVector)(indexB));
}

void pmat::Container1d::ascendingSort() {
   double *data = _ptrVector->data();
   unsigned size = _ptrVector->size();
   std::sort(data, data + size);
   (*_ptrVector) = blitz::Array<double, 1>(data, size);
}

void pmat::Container1d::descendingSort() {
   double *data = _ptrVector->data();
   unsigned size = _ptrVector->size();
   std::sort(data, data + size, [](double &left, double &right) -> bool { return left > right; });
   (*_ptrVector) = blitz::Array<double, 1>(data, size);
}
