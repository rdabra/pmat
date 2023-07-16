

#file(GLOB_RECURSE sources *.cpp *.h)

add_library(pmatLib STATIC Array.cpp Vector.cpp Matrix.cpp)
target_include_directories(pmatLib BEFORE PUBLIC ../src)


add_executable(pmat_main pmat_main.cpp)


target_link_libraries(
  pmat_main
  pmatLib
)
