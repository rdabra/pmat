#ifndef MATRIX_H
#define MATRIX_H
#pragma once

#include "Array.h"
#include "Container1d.h"
#include "Vector.h"
#include <string>

namespace pmat {

class Matrix : public pmat::Array {
   private:
      Container1d _matrix{};
      bool _isTransposed{false};
      int _rowSize{0}, _columnSize{0};

   protected:
      [[nodiscard]] virtual int vectorIndex(const int &row, const int &column) const;
      [[nodiscard]] double vectorElement(const int &row, const int &column) const;
      void moveToThis(Matrix &&matrix);

      void initializeMembers(int rowSize, int columnSize, bool isTransposed);
      void copyMembers(const Matrix &matrix);
      [[nodiscard]] bool isTransposed() const { return _isTransposed; }

   public:
      Matrix() = default;
      Matrix(const int &rowSize, const int &columnSize);
      Matrix(const std::string &fileName);
      Matrix(double data[], const int &rowSize, const int &columnSize);
      Matrix(const Matrix &matrix)
          : _matrix{matrix._matrix}, _rowSize{matrix.rowSize()}, _columnSize{matrix.columnSize()},
            _isTransposed{matrix._isTransposed} {};
      Matrix(Matrix &&matrix) noexcept
          : _matrix{std::move(matrix._matrix)}, _rowSize{matrix.rowSize()},
            _columnSize{matrix.columnSize()}, _isTransposed{matrix._isTransposed} {}
      ~Matrix() override = default;

      [[nodiscard]] int length() const override { return _rowSize * _columnSize; }
      [[nodiscard]] inline int dimension() const override { return 2; }

      /**
       * @brief Shrinks this matrix to size zero x zero
       *
       */
      void clear() override;

      /**
       * @brief Clears this matrix and sets a new size
       *
       * @param rowSize New row size
       * @param columnSize New column size
       */
      void clearAndResize(const int &rowSize, const int &columnSize);

      /**
       * @brief Sets the informed value at the informed position
       *
       * @param value Value to be set
       * @param row Row position
       * @param column Column position
       */
      virtual void setValue(const double &value, const int &row, const int &column);

      /**
       * @brief Informs the value at the informed position
       *
       * @param row Row position of the value to be informed
       * @param column Column position of the value to be informed
       * @return double Value at the informed position
       */
      virtual double operator()(const int &row, const int &column) const;

      /**
       * @brief Informs the size of matrix row dimension
       *
       * @return int Row size
       */
      [[nodiscard]] inline int rowSize() const { return _rowSize; }

      /**
       * @brief Informs the size of matrix column dimension
       *
       * @return int Row size
       */
      [[nodiscard]] inline int columnSize() const { return _columnSize; }

      Matrix &operator=(const Matrix &matrix);
      Matrix &operator=(Matrix &&matrix) noexcept;
      virtual bool operator==(const Matrix &matrix) const;

      /**
       * @brief Calculates the dot product of this matrix with the informed matrix
       * @details The dot product of matrices \f$A\f$ and \f$B\f$ is \f[A:B =
       * \sum_{i,j}A_{ij}B_{ij}\f]
       *
       * @param matrix Second operand
       * @return double Dot product result
       * @exception std::invalid_argument Operands are not compatible
       */
      [[nodiscard]] virtual double dotProduct(const Matrix &matrix) const;

      /**
       * @brief Sums this matrix with the informed matrix
       *
       * @param matrix Second operand of the sum
       * @return Matrix Sum result
       * @exception std::invalid_argument Incompatible sizes
       */
      Matrix operator+(const Matrix &matrix) const;

      /**
       * @brief Sums this matrix with the informed matrix, setting the result in this matrix
       *
       * @param matrix Second operand
       * @exception std::invalid_argument Incompatible sizes
       */
      void addBy(const Matrix &matrix);

      /**
       * @brief Subtracts this matrix with the informed matrix
       *
       * @param matrix Second operand of the subtraction
       * @return Matrix Subtraction result
       * @exception std::invalid_argument Incompatible sizes
       */
      Matrix operator-(const Matrix &matrix) const;

      /**
       * @brief Subtracts this matrix with the informed matrix, setting the result in this matrix
       *
       * @param matrix Second operand
       * @exception std::invalid_argument Incompatible sizes
       */
      void subtractBy(const Matrix &matrix);

      /**
       * @brief Multiplies this matrix and the informed matrix
       *
       * @param matrix Right operand
       * @return Matrix Multiplication result
       * @exception std::invalid_argument Incompatible sizes
       */
      virtual Matrix operator*(const Matrix &matrix) const;

      /**
       * @brief Multiplies this matrix and the informed vector, considered as a column matrix
       *
       * @param vector Right operand
       * @return Vector Multiplication result
       * @exception std::invalid_argument Incompatible sizes
       */
      virtual Vector operator*(const Vector &vector) const;

      /**
       * @brief Multiplies this matrix by the informed scalar
       *
       * @param scalar Second operand of the multiplication
       * @return Matrix Multiplication result
       */
      Matrix operator*(const double &scalar) const;

      /**
       * @brief Multiplies this matrix and the informed scalar, setting the result in this matrix
       *
       * @param scalar Second operand of the multiplication
       */
      virtual void multiplyBy(const double &scalar);

      /**
       * @brief Multiplies this matrix by the informed scalar using multiple threads
       *
       * @param matrix Right operand of the multiplication
       * @param nThreads number of threads to be created
       * @return Matrix Multiplication Result
       */
      Matrix multiply(const Matrix &matrix, int nThreads);

      /**
       * @brief Performs the Hadamard multiplication of this matrix and the informed matrix
       * @details The Hadamard multiplication \f(C\f) of matrices \f(A\f) and \f(B\f) is \f[ C_{ij}
       * = A_{ij}B_{ij}\f]
       *
       * @param matrix
       * @return Matrix Multiplication result
       * @exception std::invalid_argument Incompatible sizes
       */
      [[nodiscard]] Matrix multiplyHadamardBy(const Matrix &matrix) const;

      /**
       * @brief Multiplies all the elements of the informed row by the informed scalar
       *
       * @param row Row to be multiplied
       * @param scalar Value to multiply the row
       * @exception std::invalid_argument Index out of bounds
       */
      virtual void multiplyRowBy(const int &row, const double &scalar);

      /**
       * @brief Multiplies all the elements of the informed column by the informed scalar
       *
       * @param column Column to be multiplied
       * @param scalar Value to multiply the row
       * @exception std::invalid_argument Index out of bounds
       */
      virtual void multiplyColumnBy(const int &column, const double &scalar);

      /**
       * @brief Swaps the rows at the informed positions in a range of columns
       *
       * @param rowA Position A
       * @param rowB Position B
       * @param startColumn Start column position
       * @param endColumn End column postion
       * @exception std::invalid_argument Index out of bounds
       */
      virtual void swapRows(const int &rowA, const int &rowB, const int &startColumn,
                            const int &endColumn);

      /**
       * @brief Swaps the rows at the informed positions
       *
       * @param rowA Position A
       * @param rowB Position B
       * @exception std::invalid_argument Index out of bounds
       */
      virtual void swapRows(const int &rowA, const int &rowB);

      /**
       * @brief Swaps the columns at the informed positions in a range of rows
       *
       * @param columnA Position A
       * @param columnB Position B
       * @param startRow Start row position
       * @param endRow End row postion
       * @exception std::invalid_argument Index out of bounds
       */
      virtual void swapColumns(const int &columnA, const int &columnB, const int &startRow,
                               const int &endRow);

      /**
       * @brief Swaps the columns at the informed positions
       *
       * @param columnA Position A
       * @param columnB Position B
       * @exception std::invalid_argument Index out of bounds
       */
      virtual void swapColumns(const int &columnA, const int &columnB);

      /**
       * @brief Transposes this matrix
       *
       */
      virtual void transpose();

      /**
       * @brief Calculates the Frobenius Norm of this matrix
       * @details Frobenius Norm of matrix \f$ A\f$ is calculated from the dot product the following
       * way: \f[\sqrt{A:A}\f]
       * @return Frobenius Norm result
       */
      [[nodiscard]] virtual double getFrobeniusNorm() const;

      void fillWithRandomValues(const double &min, const double &max) override;

      /**
       * @brief Gets the informed row as a vector
       *
       * @param row Row postion
       * @return Vector Informed row as a vector
       * @exception std::invalid_argument Index out of bounds
       */
      [[nodiscard]] Vector rowToVector(const int &row) const;

      /**
       * @brief Gets the informed column as a vector
       *
       * @param column Column postion
       * @return Vector Informed column as a vector
       * @exception std::invalid_argument Index out of bounds
       */
      [[nodiscard]] Vector columnToVector(const int &column) const;

      [[nodiscard]] int occurrences(const double &value) const override;

      /**
       * @brief Informs the number of occurrences of the informed value at the informed row
       *
       * @param row Row position
       * @param value Value to be searched
       * @return int Number of occurrences
       * @exception std::invalid_argument Index out of bounds
       */
      [[nodiscard]] virtual int occurrencesInRow(const int row, const double &value) const;

      /**
       * @brief Informs the number of occurrences of the informed value at the informed column
       *
       * @param column Column position
       * @param value Value to be searched
       * @return int Number of occurrences
       * @exception std::invalid_argument Index out of bounds
       */
      [[nodiscard]] virtual int occurrencesInColumn(const int column, const double &value) const;

      [[nodiscard]] std::string formattedString() const override;

      /**
       * @brief Inserts a row after the specified position and sets its elements with the specified
       * value
       *
       * @param row If row is negative or greater than rowSize-1 then it is set to -1 or
       * rowSize-1 respectively
       * @param value
       */
      void insertRow(const int &row, const double &value);

      void insertColumn(const int &col, const double &value);
};

} // namespace pmat

#endif