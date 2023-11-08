#ifndef ABSTRACTARRAY_H
#define ABSTRACTARRAY_H
#pragma once

#include <string>

namespace pmat {

/**
 * @brief Abstract entity for arrays of generic dimension
 *
 */
class Array {

   public:
      Array() = default;
      Array(const Array &array) = default;
      Array(Array &&) = default;
      Array &operator=(const Array &) = default;
      Array &operator=(Array &&) = default;
      virtual ~Array() = default;

      /**
       * @brief Informs the number of elements
       *
       * @return int Number of elements
       */
      [[nodiscard]] virtual int length() const = 0;

      /**
       * @brief Informs the dimension of the array
       *
       * @return int Dimension
       */
      [[nodiscard]] virtual int dimension() const = 0;

      /**
       * @brief Removes all elements and sets size zero
       *
       */
      virtual void clear() = 0;

      /**
       * @brief Informes the number of occurrences of a value in the array
       *
       * @param value Value to be searched
       * @return int Number of occurrences
       */
      [[nodiscard]] virtual int occurrences(const double &value) const = 0;

      /**
       * @brief Fills the array with the specified value
       *
       * @param value
       */
      virtual void fillWith(const double &value) = 0;

      /**
       * @brief Fills the array with random values
       *
       * @param min Minimum acceptable value
       * @param max Maximum acceptable value
       */
      virtual void fillWithRandomValues(const double &min, const double &max) = 0;

      /**
       * @brief Generates a string output of the elements of the array
       *
       * @return std::string
       */
      [[nodiscard]] virtual std::string formattedString(const char &separator,
                                                        int precision) const = 0;

      virtual void writeToFile(const std::string &fileName, char separator,
                               int precision) const = 0;
};

} // namespace pmat

#endif // ABSTRACTARRAY_H
