#include "DPLU_MatrixSquare.h"

void pmat::DPLU_MatrixSquare::swapRowsBellow(MatrixSquare &matU, const unsigned &idxPivot) {
   unsigned idxMax = idxPivot;
   double valMax = std::abs(matU(idxPivot, idxPivot));
   for (unsigned i = idxPivot + 1; i < matU.size(); i++)
      if (std::abs(matU(i, idxPivot)) > valMax) {
         valMax = std::abs(matU(i, idxPivot));
         idxMax = i;
      }

   if (idxMax != idxPivot) {
      matU.swapRows(idxMax, idxPivot);
      _matP.swapRows(idxMax, idxPivot);
      if (idxPivot > 0)
         _matL.partialSwapRows(idxMax, idxPivot, 0, idxPivot - 1);
      _swappedRows.emplace_back(idxMax, idxPivot);
      _changeSignForDet = !_changeSignForDet;
   }
}
