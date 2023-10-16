
#Environment variable (global scope) specifying the current directory as the include directory of this library  
set(ENV{PMAT_SRC} "${CMAKE_CURRENT_LIST_DIR}")

add_library(pmatLib STATIC Container1d.cpp Array.cpp Vector.cpp Matrix.cpp MatrixSquare.cpp MatrixTriangular.cpp 
MatrixLowerTriangular.cpp MatrixUpperTriangular.cpp MatrixSymmetry.cpp  MatrixSymmetric.cpp  MatrixSkewSymmetric.cpp 
DecompositionPLU.cpp DecompositionSAS.cpp DecompositionPQR.cpp DecompositionCholesky.cpp TMultiplicationManager.cpp 
TMultiplicationPerformer.cpp)
target_include_directories(pmatLib PUBLIC "$ENV{BLITZ_INCLUDE}")

add_executable(pmat_main pmat_main.cpp)
target_include_directories(pmat_main PUBLIC "$ENV{BLITZ_INCLUDE}")


target_link_directories(pmat_main PUBLIC "$ENV{BLITZ_LIB}")
target_link_libraries(
  pmat_main
  blitz
  pmatLib
)

