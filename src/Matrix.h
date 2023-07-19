#ifndef MATRIX_H
#define MATRIX_H
#pragma once

#include "Array.h"
#include "Vector.h"
#include <algorithm>

namespace pmat {

// TODO Tirar os data members do protected e colocar no private

class Matrix : public pmat::Array {
   private:
      std::vector<double> _matrix;
      bool _isTransposed{false};
      unsigned _rowSize{0}, _columnSize{0};

   protected:
      [[nodiscard]] virtual inline unsigned vectorIndex(const unsigned &row,
                                                        const unsigned &column) const {
         return _isTransposed ? row + column * _rowSize : column + row * _columnSize;
      }

      [[nodiscard]] double vectorElement(const unsigned &row, const unsigned &column) const {
         return _matrix[this->vectorIndex(row, column)];
      }

      void moveToThis(Matrix &&matrix) {
         _rowSize = matrix.rowSize();
         _columnSize = matrix.columnSize();
         _isTransposed = matrix._isTransposed;
         _matrix.clear();
         _matrix = std::move(matrix._matrix);
         matrix.~Matrix();
      }

      void initializeMembers(unsigned rowSize, unsigned columnSize) {
         _matrix.clear();
         _rowSize = rowSize;
         _columnSize = columnSize;
         _matrix.resize(this->length());
      }

   public:
      Matrix() = default;
      Matrix(const unsigned &rowSize, const unsigned &columnSize);
      Matrix(const std::string &fileName);
      Matrix(const Matrix &matrix)
          : _matrix{std::vector<double>{matrix._matrix}}, _rowSize{matrix.rowSize()},
            _columnSize{matrix.columnSize()}, _isTransposed{matrix._isTransposed} {};
      Matrix(Matrix &&matrix) noexcept
          : _matrix{std::move(matrix._matrix)}, _rowSize{matrix.rowSize()},
            _columnSize{matrix.columnSize()}, _isTransposed{matrix._isTransposed} {}
      ~Matrix() override = default;
      [[nodiscard]] inline unsigned length() const override { return _rowSize * _columnSize; }
      [[nodiscard]] inline unsigned dimension() const override { return 2; }
      void resize(const unsigned &rowSize, const unsigned &columnSize);
      void clear() override;
      virtual void setValue(const double &value, const unsigned &row, const unsigned &column);
      virtual double operator()(const unsigned &row, const unsigned &column) const;
      [[nodiscard]] inline unsigned rowSize() const { return _rowSize; }
      [[nodiscard]] inline unsigned columnSize() const { return _columnSize; }
      Matrix &operator=(const Matrix &matrix);
      Matrix &operator=(Matrix &&matrix) noexcept;
      virtual bool operator==(const Matrix &matrix) const;
      [[nodiscard]] virtual double dotProduct(const Matrix &matrix) const;
      Matrix operator+(const Matrix &matrix) const;
      void addBy(const Matrix &matrix);
      Matrix operator-(const Matrix &matrix) const;
      void subtractBy(const Matrix &matrix);
      virtual Matrix operator*(const Matrix &matrix) const;
      virtual Vector operator*(const Vector &vector) const;
      Matrix operator*(const double &scalar) const;
      virtual void multiplyBy(const double &scalar);
      [[nodiscard]] Matrix multiplyHadamardBy(const Matrix &matrix) const;
      virtual void multiplyRowBy(const unsigned &row, const double &scalar);
      virtual void multiplyColumnBy(const unsigned &column, const double &scalar);
      virtual void swapRows(const unsigned &rowA, const unsigned &rowB, const unsigned &startColumn,
                            const unsigned &endColumn);
      virtual void swapColumns(const unsigned &columnA, const unsigned &columnB,
                               const unsigned &startRow, const unsigned &endRow);
      virtual void transpose();
      [[nodiscard]] virtual double getFrobeniusNorm() const;
      void fillRandomly(const double &min, const double &max) override;
      [[nodiscard]] Vector extractRow(const unsigned &row) const;
      [[nodiscard]] Vector extractColumn(const unsigned &column) const;
      [[nodiscard]] unsigned occurrences(const double &value) const override;
      [[nodiscard]] virtual unsigned occurrencesInRow(const unsigned row,
                                                      const double &value) const;
      [[nodiscard]] virtual unsigned occurrencesInColumn(const unsigned column,
                                                         const double &value) const;
};

} // namespace pmat

#endif