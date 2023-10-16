
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

#FetchContent_GetProperties(googletest)
#if(NOT googletest_POPULATED)
#  FetchContent_Populate(googletest)
#  add_subdirectory(${googletest_SOURCE_DIR} ${googletest_BINARY_DIR})
#endif()

add_executable(
  pmat_test
  tVector.h
  tMatrix.h
  tMatrixSquare.h
  tMatrixTriangular.h
  tMatrixSymmetric.h
  tMatrixSkewSymmetric.h
  pmat_test.cpp
)  
target_include_directories(pmat_test PUBLIC "$ENV{BLITZ_INCLUDE}" "$ENV{PMAT_SRC}")


target_link_directories(pmat_test PUBLIC "$ENV{BLITZ_LIB}")
target_link_libraries(
  pmat_test
  GTest::gtest_main blitz pmatLib 
)




include(GoogleTest)
gtest_discover_tests(pmat_test)
#gtest_add_tests(TARGET pmat_test)

