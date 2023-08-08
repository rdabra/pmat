#pragma once

namespace pmat {

namespace utils {

// Tolerance for relational operators with doubles
static inline const double DIF_TOLERANCE = 0.0000000001;

static inline const double ZERO = 0.0000000000;

static inline const double ONE = 1.0000000000;

static inline const double TWO = 2.0000000000;

static inline const double MINUS_ONE = -1.0000000000;

static inline const double ONE_HALF = 0.5000000000;

static inline const unsigned NUM_THREADS = 5;

static inline const double &max(const double &a, const double &b) {
   return a > b ? a : b;
};

static inline double abs(const double &a) {
   return a > ZERO ? a : -a;
};

static inline bool areEqual(const double &a, const double &b) {
   const double m = max(abs(a), abs(b));
   return m < DIF_TOLERANCE ? true : (abs(a - b) / m) < DIF_TOLERANCE;
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

} // namespace utils
} // namespace pmat
