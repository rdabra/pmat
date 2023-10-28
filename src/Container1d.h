#ifndef CONTAINER1D_H
#define CONTAINER1D_H
#pragma once

namespace pmat {

/**
 * @brief One-dimensional container used by the arrays of the lib
 *
 */
class Container1d {
   private:
      double *_ptrVector{nullptr};
      int _size{0};

      void manageSize(const int &newSize);

   public:
      Container1d() = default;
      Container1d(const Container1d &container);
      Container1d(Container1d &&container) noexcept;
      Container1d &operator=(const Container1d &container);
      Container1d &operator=(Container1d &&container) noexcept;
      ~Container1d();

      /**
       * @brief Construct a new Container 1d object
       *
       * @param size Container size
       */
      Container1d(const int &size);

      /**
       * @brief Construct a new Container 1d object
       *
       * @param size Container size
       * @param value Value to be set for all elements
       */
      Container1d(const int &size, const double &value);

      /**
       * @brief Construct a new Container 1d object from a raw array of values
       *
       * @param data Raw array of values
       * @param size Size of the raw array
       */
      Container1d(double data[], const int &size);

      /**
       * @brief Returns the value at the specified index
       *
       * @param index
       * @return double
       */
      inline double operator()(const int &index) const { return _ptrVector[index]; };

      /**
       * @brief Returns a reference for the element at the specified index
       *
       * @param index
       * @return double&
       */
      inline double &operator()(const int &index) { return _ptrVector[index]; };

      /**
       * @brief Sets the specified value at the specified index
       *
       * @param index
       * @param value
       */
      inline void set(const int &index, const double &value) { _ptrVector[index] = value; };

      /**
       * @brief Returns the size of the container
       *
       * @return int
       */
      [[nodiscard]] inline const int &size() const { return _size; };

      /**
       * @brief Resize the container. If the new size is greater than the old size, the new elements
       * are initialized to zero
       *
       * @param size
       */
      void resize(const int &size);

      /**
       * @brief Clears the container and sets its size to zero
       *
       */
      void clear();

      /**
       * @brief Inserts one element at the end of the container and sets it to the specified value
       *
       * @param value
       */
      void pushBack(const double &value);

      /**
       * @brief Include values after initial position jumping steps backwards until first element is
       * reached
       *
       * @param initialPosition
       * @param step
       * @param value
       */
      void pushBack(const int &initialPosition, const int &step, const double &value);

      /**
       * @brief Exchanges the values of indexA and indexB of the container
       *
       * @param indexA
       * @param indexB
       */
      void exchange(const int &indexA, const int &indexB);

      /**
       * @brief Sorts the container in ascending order
       *
       */
      void ascendingSort();

      /**
       * @brief Sorts the container in descending order
       *
       */
      void descendingSort();

      /**
       * @brief Insert contiguous repeated values after the specified initial position
       *
       * @param initialPosition If the initial position is negative then values are inserted
       * starting from index zero
       * @param value
       * @param nRepetitions
       */
      void insertValues(const int &initialPosition, const double &value, const int &nRepetitions);
};

} // namespace pmat

#endif