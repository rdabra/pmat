#include "Vector.h"
#include "Matrix.h"
#include "Messages.h"
#include "pmatUtils.h"
#include <random>
#include <stdexcept>
#include <utility>

pmat::Vector::Vector(const Vector &vector) : _vector{vector._vector} {
}

void pmat::Vector::resize(const int &size) {
   _vector.clear();
   _vector.resize(size);
}

void pmat::Vector::pushBack(const double &value) {
   _vector.pushBack(value);
}

void pmat::Vector::assign(const double &value, const int &index) {
   if (index >= this->size())
      throw std::invalid_argument(pmat::messages::INDEX_OUT);

   _vector.set(index, value);
}

double pmat::Vector::at(const int &index) const {
   if (index >= this->size())
      throw std::invalid_argument(pmat::messages::INDEX_OUT);

   return _vector(index);
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
   bool resp = this->length() == vector.length();
   if (resp) {
      for (int i = 0; i < this->length(); i++) {
         resp = pmat::utils::areEqual((*this)(i), vector(i));
         if (!resp)
            break;
      }
   }
   return resp;
}

pmat::Vector pmat::Vector::operator+(const Vector &vector) const {
   if (vector.size() != this->size())
      throw std::invalid_argument(pmat::messages::NONCOMPT_SIZE_ARG);

   pmat::Vector resp{};
   for (int i{0}; i < vector.length(); i++)
      resp.pushBack((*this)(i) + vector(i));

   return resp;
}

void pmat::Vector::addBy(const Vector &vector) {
   if (vector.size() != this->size())
      throw std::invalid_argument(pmat::messages::NONCOMPT_SIZE_ARG);

   for (int i{0}; i < vector.length(); i++)
      (*this)(i) = (*this)(i) + vector(i);
}

pmat::Vector pmat::Vector::operator-(const Vector &vector) const {
   if (vector.size() != this->size())
      throw std::invalid_argument(pmat::messages::NONCOMPT_SIZE_ARG);

   pmat::Vector resp{};
   for (int i{0}; i < vector.length(); i++)
      resp.pushBack((*this)(i)-vector(i));

   return resp;
}

void pmat::Vector::subtractBy(const Vector &vector) {
   if (vector.size() != this->size())
      throw std::invalid_argument(pmat::messages::NONCOMPT_SIZE_ARG);

   for (int i{0}; i < vector.length(); i++)
      (*this)(i) = (*this)(i)-vector(i);
}

pmat::Vector pmat::Vector::operator*(const double &scalar) const {
   pmat::Vector resp{};
   for (int i{0}; i < this->length(); i++)
      resp.pushBack((*this)(i)*scalar);

   return resp;
}

void pmat::Vector::multiplyBy(const double &scalar) {
   for (int i{0}; i < this->length(); i++)
      (*this)(i) = (*this)(i)*scalar;
}

double pmat::Vector::dotProduct(const Vector &vector) const {
   if (vector.size() != this->size())
      throw std::invalid_argument(pmat::messages::NONCOMPT_SIZE_ARG);

   double resp = pmat::utils::ZERO;
   for (int i = 0; i < vector.length(); i++)
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

int pmat::Vector::occurrences(const double &value) const {
   int res{0};
   for (int i = 0; i < this->length(); i++)
      if (pmat::utils::areEqual((*this)(i), value))
         res++;

   return res;
}

void pmat::Vector::fillWith(const double &value) {
   for (int i = 0; i < this->length(); i++)
      (*this)(i) = value;
}

void pmat::Vector::fillWithRandomValues(const double &min, const double &max) {
   std::uniform_real_distribution<double> dist(min, max);
   std::mt19937 rng(std::random_device{}());

   for (int i = 0; i < this->length(); i++)
      (*this)(i) = dist(rng);
}

void pmat::Vector::swapElements(const int &elmIndexA, const int &elmIndexB) {
   if (elmIndexA >= this->size() || elmIndexB >= this->size())
      throw std::invalid_argument(pmat::messages::INDEX_OUT);

   _vector.exchange(elmIndexA, elmIndexB);
}

void pmat::Vector::ascendingSort() {
   _vector.ascendingSort();
}

void pmat::Vector::descendingSort() {
   _vector.descendingSort();
}

pmat::Matrix pmat::Vector::toColumnMatrix() const {
   Matrix res{this->length(), 1};
   for (int i = 0; i < this->length(); i++)
      res(i, 0) = _vector(i);

   return res;
}

pmat::Matrix pmat::Vector::toRowMatrix() const {
   Matrix res{1, this->length()};
   for (int i = 0; i < this->length(); i++)
      res(0, i) = _vector(i);

   return res;
}

double pmat::Vector::euclideanDistantFrom(const Vector &vector) const {
   return ((*this) - vector).frobeniusNorm();
}

std::string pmat::Vector::formattedString() const {
   std::string res{"\n"};
   for (int i{0}; i < this->size(); i++)
      res += std::to_string((*this)(i)) + " ";
   res += "\n";

   return res;
}
