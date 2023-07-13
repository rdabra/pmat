
cmake_minimum_required (VERSION 3.26)


project(pmat LANGUAGES CXX VERSION 0.1 DESCRIPTION "SIMPLE C++ STATIC LIBRARY FOR MATRIX OPERATIONS")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON) 

enable_testing()

add_subdirectory (src)
add_subdirectory (test) 