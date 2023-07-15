#include "Vector.h"
#include "Matrix.h"
#include "utils.h"
#include <random>

pmat::Vector::Vector(const Vector &vector) {
   for (auto elm : vector._vector)
      _vector.emplace_back(elm);
}

void pmat::Vector::resize(const unsigned &size) {
   _vector.clear();
   _vector.resize(size);
}

void pmat::Vector::emplaceBack(const double &value) {
   _vector.emplace_back(value);
}

void pmat::Vector::setValue(const double &value, const unsigned &index) {
   // TODO Implementar pre condição
   _vector[index] = value;
}

const double &pmat::Vector::operator()(const unsigned &index) const {
   // TODO Implementar pre condição
   return _vector[index];
}

pmat::Vector &pmat::Vector::operator=(const Vector &vector) {
   if (!(this == &vector)) {
      _vector.clear();
      _vector = vector._vector;
   }

   return *this;
}

pmat::Vector &pmat::Vector::operator=(Vector &&vector) noexcept {
   _vector.clear();
   _vector = std::move(vector._vector);

   return *this;
}

bool pmat::Vector::operator==(const Vector &vector) const {
   bool resp = this->size() == vector.size();
   if (resp) {
      for (unsigned i = 0; i < this->size(); i++) {
         resp = pmat::utils::areEqual((*this)(i), vector(i));
         if (!resp)
            break;
      }
   }
   return resp;
}

pmat::Vector pmat::Vector::operator+(const Vector &vector) const {
   // TODO Implementar pre condição
   pmat::Vector resp{};
   for (int i{0}; i < vector.size(); i++)
      resp.emplaceBack((*this)(i) + vector(i));

   return resp;
}

void pmat::Vector::addBy(const Vector &vector) {
   // TODO Implementar pre condição
   for (int i{0}; i < vector.size(); i++)
      this->setValue((*this)(i) + vector(i), i);
}

pmat::Vector pmat::Vector::operator-(const Vector &vector) const {
   // TODO Implementar pre condição
   pmat::Vector resp{};
   for (int i{0}; i < vector.size(); i++)
      resp.emplaceBack((*this)(i)-vector(i));

   return resp;
}

void pmat::Vector::subtractBy(const Vector &vector) {
   // TODO Implementar pre condição
   for (int i{0}; i < vector.size(); i++)
      this->setValue((*this)(i)-vector(i), i);
}

pmat::Vector pmat::Vector::operator*(const double &scalar) const {
   pmat::Vector resp{};
   for (int i{0}; i < this->size(); i++)
      resp.emplaceBack((*this)(i)*scalar);

   return resp;
}

void pmat::Vector::multiplyBy(const double &scalar) {
   for (int i{0}; i < this->size(); i++)
      this->setValue((*this)(i)*scalar, i);
}

double pmat::Vector::dotProduct(const Vector &vector) const {
   // TODO Implementar pre condição
   double resp = pmat::utils::ZERO;
   for (unsigned i = 0; i < vector.size(); i++)
      resp += (*this)(i)*vector(i);

   return resp;
}

double pmat::Vector::frobeniusNorm() const {
   return sqrt(this->dotProduct(*this));
}

pmat::Vector pmat::Vector::getUnitaryVector() const {
   double norm = pmat::utils::ONE / this->frobeniusNorm();
   pmat::Vector resp{std::move((*this) * norm)};

   return resp;
}

unsigned pmat::Vector::occurrences(const double &value) const {
   unsigned res{0};
   for (unsigned i = 0; i < this->size(); i++)
      if (pmat::utils::areEqual((*this)(i), value))
         res++;

   return res;
}

void pmat::Vector::fillRandomly(const double &min, const double &max) {
   std::uniform_real_distribution<double> dist(min, max);
   std::mt19937 rng(std::random_device{}());

   for (unsigned i = 0; i < this->size(); i++)
      this->setValue(dist(rng), i);
}

void pmat::Vector::swapElements(const unsigned &elmIndexA, const unsigned &elmIndexB) {
   // TODO Implementar pre condição
   _vector[elmIndexB] = std::exchange(_vector[elmIndexA], _vector[elmIndexB]);
}

void pmat::Vector::ascendingSort() {
   std::sort(_vector.begin(), _vector.end());
}

void pmat::Vector::descendingSort() {
   std::sort(_vector.begin(), _vector.end(),
             [](double &left, double &right) -> bool { return left > right; });
}

pmat::Matrix pmat::Vector::toColumnMatrix() const {
   Matrix res{this->size(), 1};
   for (unsigned i = 0; i < this->size(); i++)
      res.setValue(_vector[i], i, 0);
   return res;
}

pmat::Matrix pmat::Vector::toRowMatrix() const {
   Matrix res{1, this->size()};
   for (unsigned i = 0; i < this->size(); i++)
      res.setValue(_vector[i], 0, i);
   return res;
}
