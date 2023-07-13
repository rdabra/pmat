#include "Vector.h"
#include "utils.h"
#include <random>

pmat::Vector::Vector(const Vector &vector) {
   for (auto elm : vector._vector)
      _vector.emplace_back(elm);
}

unsigned pmat::Vector::size() const {
   return _vector.size();
}

unsigned pmat::Vector::dimension() const {
   return 1;
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
   _vector.clear();
   for (auto elm : vector._vector)
      _vector.emplace_back(elm);

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
         resp = pmat::utils::areEqual(_vector[i], vector(i));
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
      resp.emplaceBack(_vector[i] + vector(i));

   return resp;
}

void pmat::Vector::addBy(const Vector &vector) {
   // TODO Implementar pre condição
   for (int i{0}; i < vector.size(); i++)
      this->setValue(_vector[i] + vector(i), i);
}

pmat::Vector pmat::Vector::operator-(const Vector &vector) const {
   // TODO Implementar pre condição
   pmat::Vector resp{};
   for (int i{0}; i < vector.size(); i++)
      resp.emplaceBack(_vector[i] - vector(i));

   return resp;
}

void pmat::Vector::subtractBy(const Vector &vector) {
   // TODO Implementar pre condição
   for (int i{0}; i < vector.size(); i++)
      this->setValue(_vector[i] - vector(i), i);
}

pmat::Vector pmat::Vector::operator*(const double &scalar) const {
   pmat::Vector resp{};
   for (int i{0}; i < this->size(); i++)
      resp.emplaceBack(_vector[i] * scalar);

   return resp;
}

void pmat::Vector::multiplyBy(const double &scalar) {
   for (int i{0}; i < this->size(); i++)
      this->setValue(_vector[i] * scalar, i);
}

double pmat::Vector::dotProduct(const Vector &vector) const {
   // TODO Implementar pre condição
   double resp = 0.0;
   for (unsigned i = 0; i < vector.size(); i++)
      resp += _vector[i] * vector(i);

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

unsigned pmat::Vector::numberOfOccurrences(const double &value) const {
   unsigned res{0};
   for (unsigned i = 0; i < this->size(); i++)
      if (pmat::utils::areEqual(_vector[i], value))
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
