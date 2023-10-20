#include "Container1d.h"
#include "utils.h"
#include <algorithm>
#include <cmath>

pmat::Container1d::Container1d(const Container1d &container)
    : _ptrVector{std::make_unique<blitz::Array<double, 1>>(container._ptrVector->size())} {
   *_ptrVector = (*container._ptrVector);
}

pmat::Container1d &pmat::Container1d::operator=(const pmat::Container1d &container) {
   _ptrVector->resize(0);
   _ptrVector = std::make_unique<blitz::Array<double, 1>>(container._ptrVector->size());
   *_ptrVector = (*container._ptrVector);

   return *this;
}

pmat::Container1d &pmat::Container1d::operator=(pmat::Container1d &&container) noexcept {
   _ptrVector->resize(0);
   _ptrVector = std::move(container._ptrVector);

   return *this;
}

pmat::Container1d::Container1d(const int &size, const double &value)
    : _ptrVector{std::make_unique<blitz::Array<double, 1>>(size)} {
   *_ptrVector = value;
}

void pmat::Container1d::resize(const int &size) {

   int oldSize = this->size();
   _ptrVector->resizeAndPreserve(size);

   if (size > oldSize)
      for (int i{oldSize}; i < size; i++)
         (*_ptrVector)(i) = utils::ZERO;
}

void pmat::Container1d::pushBack(const double &value) {
   auto size{_ptrVector->size()};
   _ptrVector->resizeAndPreserve(size + 1);
   (*_ptrVector)(size) = value;
}

void pmat::Container1d::pushBack(const int &initialPosition, const int &step, const double &value) {
   int oldSize = this->size();
   int inc = initialPosition < oldSize - 1 ? 1 + ((initialPosition + 1) / step)
                                           : ((initialPosition + 1) / step);
   int newSize = oldSize + inc;
   int i = oldSize - 1;
   int j = newSize - 1;
   int k = initialPosition;
   this->resize(newSize);

   int n{0};
   while (n < inc) {
      if (k == i) {
         this->set(j--, value);
         k -= step;
         n++;
      } else
         this->set(j--, (*this)(i--));
   }
}

void pmat::Container1d::exchange(const int &indexA, const int &indexB) {
   (*_ptrVector)(indexB) = std::exchange((*_ptrVector)(indexA), (*_ptrVector)(indexB));
}

void pmat::Container1d::ascendingSort() {
   double *data = _ptrVector->data();
   int size = (int)_ptrVector->size();
   std::sort(data, data + size);
   (*_ptrVector) = blitz::Array<double, 1>(data, size);
}

void pmat::Container1d::descendingSort() {
   double *data = _ptrVector->data();
   int size = (int)_ptrVector->size();
   std::sort(data, data + size, [](double &left, double &right) -> bool { return left > right; });
   (*_ptrVector) = blitz::Array<double, 1>(data, size);
}

void pmat::Container1d::insertValues(const int &initialPosition, const double &value,
                                     const int &nRepetitions) {
   int oldSize = this->size();
   int newSize = oldSize + nRepetitions;
   int i = oldSize - 1;
   int j = newSize - 1;
   int finalPosition = initialPosition + nRepetitions;
   this->resize(newSize);

   while (j > initialPosition)
      if (j > finalPosition)
         this->set(j--, (*this)(i--));
      else
         this->set(j--, value);
}
