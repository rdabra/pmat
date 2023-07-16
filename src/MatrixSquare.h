#ifndef MATRIXSQUARE_H
#define MATRIXSQUARE_H

#include <memory>
#pragma once

#include "Matrix.h"

namespace pmat {

class AbstractMatrixTriangular;

class MatrixLowerTriangular;

class MatrixUpperTriangular;

class MatrixSquare;

class MatrixSymmetric;

class MatrixSkewSymmetric;

enum class SubMatrixPos { lower, upper };

struct D_PLU {
      std::unique_ptr<MatrixSquare> matP;
      std::unique_ptr<MatrixLowerTriangular> matL;
      std::unique_ptr<MatrixUpperTriangular> matU;
      std::vector<std::pair<unsigned, unsigned>> swappedRows;
};

struct D_SAS {
      std::unique_ptr<MatrixSymmetric> matS;
      std::unique_ptr<MatrixSkewSymmetric> matAS;
};

struct D_PQR {
      std::unique_ptr<MatrixSquare> matP;
      std::unique_ptr<MatrixSquare> matQ;
      std::unique_ptr<MatrixUpperTriangular> matR;
      std::vector<std::pair<unsigned, unsigned>> swappedColumns;
      unsigned rank{0};
};

class MatrixSquare : public Matrix {

   protected:
      void swapRowsBellow(MatrixSquare &matU, const unsigned &idxPivot);
      void swapPivotColumn(MatrixSquare &partialR, const unsigned &idxPivot);
      void nullifyElementBellow(MatrixSquare &matU, const unsigned &idxPivot) const;
      void findInverseByBackSubstitution(const AbstractMatrixTriangular *matrix,
                                         AbstractMatrixTriangular *resp) const;
      [[nodiscard]] Vector findSolutionByBackSubstitution(const AbstractMatrixTriangular &matrix,
                                                          const Vector &rhs) const;
      [[nodiscard]] MatrixSquare calculateHouseholderSubMatrix(const MatrixSquare &partialR,
                                                               const unsigned idxPivot) const;
      MatrixSquare calculateInverseByPlu();
      MatrixSquare calculateInverseByPQR();
      virtual void decomposeToPlu();
      virtual void decomposeToStrictLu();
      virtual void decomposeToSas();
      virtual void decomposeToQr();

   public:
      MatrixSquare() = default;
      explicit MatrixSquare(const unsigned &size) : Matrix{size, size} {}
      MatrixSquare(const MatrixSquare &matrix);
      MatrixSquare(MatrixSquare &&matrix) noexcept : Matrix{std::move(matrix)} {}
      MatrixSquare(Matrix &&matrix);
      ~MatrixSquare() override;
      [[nodiscard]] unsigned size() const;
      virtual void resize(const unsigned &size) { Matrix::resize(size, size); }
      MatrixSquare &operator=(const MatrixSquare &matrix);
      MatrixSquare &operator=(MatrixSquare &&matrix) noexcept;
      MatrixSquare operator+(const MatrixSquare &matrix) const;
      MatrixSquare operator-(const MatrixSquare &matrix) const;
      virtual MatrixSquare operator*(const MatrixSquare &matrix) const;
      virtual MatrixSquare multiplyByBiggerMatrix(const MatrixSquare &matrix, SubMatrixPos pos);
      MatrixSquare operator*(const double &scalar) const;
      Vector operator*(const Vector &vector) const override { return Matrix::operator*(vector); }
      [[nodiscard]] virtual double trace() const;
      virtual const D_PLU getPLU();
      virtual const D_PLU getStrictLU();
      virtual double getDeterminant();
      virtual const D_SAS getSAS();
      virtual const D_PQR getPQR();
      virtual bool isStrictLUDecomposable();
      virtual bool isInvertible();
      [[nodiscard]] virtual MatrixLowerTriangular extractLowerPart() const;
      [[nodiscard]] virtual MatrixUpperTriangular extractUpperPart() const;
      virtual MatrixSquare getInverse();
      virtual Vector linearSolve(const Vector &rhs);
      virtual bool isPositiveDefinite();
      virtual bool isOrthogonal();
      unsigned getRank();
      virtual void fillDiagonalWith(const double &value);
};

} // namespace pmat

#endif