

#file(GLOB_RECURSE sources *.cpp *.h)

add_library(pmatLib STATIC Array.cpp Vector.cpp Matrix.cpp MatrixSquare.cpp MatrixTriangular.cpp 
MatrixLowerTriangular.cpp MatrixUpperTriangular.cpp MatrixSymmetry.cpp  MatrixSymmetric.cpp  MatrixSkewSymmetric.cpp)

#DPLU_MatrixSquare.cpp DPQR_MatrixSquare.cpp DSAS_MatrixSquare.cpp

target_include_directories(pmatLib BEFORE PUBLIC ../src)


add_executable(pmat_main pmat_main.cpp)


target_link_libraries(
  pmat_main
  pmatLib
)
