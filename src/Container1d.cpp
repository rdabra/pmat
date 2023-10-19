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

pmat::Container1d::Container1d(const unsigned &size, const double &value)
    : _ptrVector{std::make_unique<blitz::Array<double, 1>>(size)} {
   *_ptrVector = value;
}

void pmat::Container1d::resize(const unsigned &size) {

   unsigned oldSize = this->size();
   // Caution: narrowing from unsigned to int
   _ptrVector->resizeAndPreserve((int)size);

   if (size > oldSize)
      for (unsigned i{oldSize}; i < size; i++)
         (*_ptrVector)((int)i) = utils::ZERO;
}

void pmat::Container1d::pushBack(const double &value) {
   // Caution: narrowing from unsigned to int
   auto size{_ptrVector->size()};
   _ptrVector->resizeAndPreserve((int)size + 1);
   (*_ptrVector)((int)size) = value;
}

void pmat::Container1d::pushBack(const unsigned &initialPosition, const unsigned &step,
                                 const double &value) {
   unsigned oldSize = this->size();
   unsigned inc = std::floor(oldSize / step);
   unsigned newSize = oldSize + inc;
   unsigned i = oldSize - 1;
   unsigned j = newSize - 1;
   unsigned k = initialPosition + inc;
   unsigned newStep = step + inc - 1;
   this->resize(newSize);

   unsigned n{0};
   while (n < inc) {
      if (k == j) {
         this->set(j--, value);
         k -= newStep;
         n++;
      } else
         this->set(j--, (*this)(i--));
   }
}

void pmat::Container1d::exchange(const unsigned &indexA, const unsigned &indexB) {
   // Caution: narrowing from unsigned to int
   (*_ptrVector)((int)indexB) =
       std::exchange((*_ptrVector)((int)indexA), (*_ptrVector)((int)indexB));
}

void pmat::Container1d::ascendingSort() {
   double *data = _ptrVector->data();
   unsigned size = _ptrVector->size();
   std::sort(data, data + size);
   (*_ptrVector) = blitz::Array<double, 1>(data, (int)size);
}

void pmat::Container1d::descendingSort() {
   double *data = _ptrVector->data();
   unsigned size = _ptrVector->size();
   std::sort(data, data + size, [](double &left, double &right) -> bool { return left > right; });
   (*_ptrVector) = blitz::Array<double, 1>(data, (int)size);
}

void pmat::Container1d::insertValues(const int &initialPosition, const double &value,
                                     const int &nRepetitions) {
   int oldSize = (int)this->size();
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
