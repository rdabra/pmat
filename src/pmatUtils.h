#pragma once

#include <cmath>
#include <fstream>
#include <sstream>
#include <string>

namespace pmat::utils {

static const int PRECISION = 8;

// Tolerance for relational operators with doubles
static const double TOLERANCE = 0.00000001;

static const double ZERO = 0.00000000;

static const double ONE = 1.00000000;

static const double TWO = 2.00000000;

static const double MINUS_ONE = -1.00000000;

static const double ONE_HALF = 0.50000000;

static const int NUM_THREADS = 5;

enum class TriangType { UPPER, LOWER };

static const double &max(const double &a, const double &b) {
   return a > b ? a : b;
};

static inline double abs(const double &a) {
   return a > ZERO ? a : -a;
};

static inline bool areEqual(const double &a, const double &b) {
   return std::fabs(a - b) < TOLERANCE;
}

static inline bool isZero(const double &a) {
   return areEqual(a, ZERO);
}

static inline bool isOne(const double &a) {
   return areEqual(a, ONE);
}

static inline double signOf(const double &a) {
   return a < 0 ? -ONE : ONE;
}

static inline double inv(const double &a) {
   return ONE / a;
}

static std::string format(const double &a, int precision) {
   std::stringstream stream;
   stream.setf(std::ios::fixed);
   stream.precision(precision + 1);
   stream << a;

   return stream.str();
}

static int countFileLines(std::string fileName) {
   int nRows{0};
   std::ifstream f{fileName};
   std::string line;

   if (f.is_open()) {
      while (std::getline(f, line))
         nRows++;
      f.close();
   }

   return nRows;
}

} // namespace pmat::utils
