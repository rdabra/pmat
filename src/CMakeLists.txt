

#file(GLOB_RECURSE sources *.cpp *.h)

add_library(pmatLib STATIC Array.cpp Vector.cpp)
target_include_directories(pmatLib BEFORE PUBLIC ../src)


add_executable(pmatMain pmat_main.cpp)


target_link_libraries(
  pmatMain
  pmatLib
)
