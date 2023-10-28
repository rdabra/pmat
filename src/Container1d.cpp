#include "Container1d.h"
#include "pmatUtils.h"

void pmat::Container1d::manageSize(const int &newSize) {
   if (newSize > 0) {
      if (_size == 0) {
         _ptrVector = (double *)malloc(newSize * sizeof(double));
         for (int i{0}; i < newSize; i++)
            _ptrVector[i] = pmat::utils::ZERO;
      } else {
         _ptrVector = (double *)realloc(_ptrVector, newSize * sizeof(double));
         if (newSize > _size)
            for (int i{_size}; i < newSize; i++)
               _ptrVector[i] = pmat::utils::ZERO;
      }
      _size = newSize;
   } else {
      free(_ptrVector);
      _ptrVector = nullptr;
      _size = 0;
   }
}

pmat::Container1d::Container1d(const Container1d &container) {
   this->manageSize(container.size());
   for (int i{0}; i < _size; i++)
      _ptrVector[i] = container(i);
}

pmat::Container1d::Container1d(Container1d &&container) noexcept
    : _ptrVector{container._ptrVector}, _size{container._size} {
   container._ptrVector = nullptr;
   container._size = 0;
}

pmat::Container1d &pmat::Container1d::operator=(const Container1d &container) {
   this->manageSize(container.size());
   for (int i{0}; i < _size; i++)
      _ptrVector[i] = container(i);

   return (*this);
}

pmat::Container1d &pmat::Container1d::operator=(Container1d &&container) noexcept {
   this->resize(0);
   _ptrVector = container._ptrVector;
   _size = container._size;
   container._ptrVector = nullptr;
   container._size = 0;

   return (*this);
}

pmat::Container1d::Container1d(double data[], const int &size) {
   this->manageSize(size);
   for (int i{0}; i < _size; i++)
      _ptrVector[i] = data[i];
}

pmat::Container1d::Container1d(const int &size) {
   this->resize(size);
}

pmat::Container1d::Container1d(const int &size, const double &value) {
   this->resize(size);
   for (int i{0}; i < _size; i++)
      _ptrVector[i] = value;
}

pmat::Container1d::~Container1d() {
   if (_size > 0) {
      free(_ptrVector);
      _ptrVector = nullptr;
      _size = 0;
   }
}

void pmat::Container1d::resize(const int &size) {
   this->manageSize(size);
}

void pmat::Container1d::clear() {
   this->resize(0);
}

void pmat::Container1d::pushBack(const double &value) {
   this->resize(_size + 1);
   _ptrVector[_size - 1] = value;
}

void pmat::Container1d::pushBack(const int &initialPosition, const int &step, const double &value) {
   int oldSize = this->size();
   int inc = initialPosition < oldSize - 1 ? 1 + ((initialPosition + 1) / step)
                                           : ((initialPosition + 1) / step);
   int newSize = oldSize + inc;
   int i = oldSize - 1;
   int j = newSize - 1;
   int k = initialPosition;
   this->manageSize(newSize);

   int n{0};
   while (n < inc) {
      if (k == i) {
         _ptrVector[j--] = value;
         k -= step;
         n++;
      } else
         _ptrVector[j--] = _ptrVector[i--];
   }
}

void pmat::Container1d::exchange(const int &indexA, const int &indexB) {
   double aux = _ptrVector[indexA];
   _ptrVector[indexA] = _ptrVector[indexB];
   _ptrVector[indexB] = aux;
}

void pmat::Container1d::ascendingSort() {
   std::sort(_ptrVector, _ptrVector + _size);
}

void pmat::Container1d::descendingSort() {
   std::sort(_ptrVector, _ptrVector + _size,
             [](double &left, double &right) -> bool { return left > right; });
}

void pmat::Container1d::insertValues(const int &initialPosition, const double &value,
                                     const int &nRepetitions) {
   int oldSize = _size;
   int newSize = oldSize + nRepetitions;
   int i = oldSize - 1;
   int j = newSize - 1;
   int finalPosition = initialPosition + nRepetitions;
   this->manageSize(newSize);

   while (j > initialPosition)
      if (j > finalPosition)
         _ptrVector[j--] = _ptrVector[i--];
      else
         _ptrVector[j--] = value;
}
