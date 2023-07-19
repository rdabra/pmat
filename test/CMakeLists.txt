
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/v1.13.0.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_executable(
  pmat_test
  tVector.h
  tMatrix.h
  tMatrixSquare.h
  tMatrixTriangular.h
  pmat_test.cpp
)  

target_link_libraries(
  pmat_test
  GTest::gtest_main pmatLib 
)


include(GoogleTest)
gtest_discover_tests(pmat_test)
#gtest_add_tests(TARGET pmat_test)

