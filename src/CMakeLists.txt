

add_library(pmatLib STATIC Array.cpp Vector.cpp Matrix.cpp MatrixSquare.cpp MatrixTriangular.cpp 
MatrixLowerTriangular.cpp MatrixUpperTriangular.cpp MatrixSymmetry.cpp  MatrixSymmetric.cpp  MatrixSkewSymmetric.cpp 
DecompositionPLU.cpp DecompositionSAS.cpp DecompositionPQR.cpp DecompositionCholesky.cpp TMultiplicationManager.cpp 
TMultiplicationPerformer.cpp)

#target_include_directories(pmatLib BEFORE PUBLIC ../src)

set(PMAT_SOURCE CMAKE_CURRENT_LIST_DIR)

add_executable(pmat_main pmat_main.cpp)

target_link_libraries(
  pmat_main
  pmatLib
)

