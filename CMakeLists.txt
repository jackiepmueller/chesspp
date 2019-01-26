cmake_minimum_required (VERSION 3.5.1)

set (CMAKE_CXX_STANDARD 17)
set (CMAKE_CXX_STANDARD_REQUIRED ON)
set (CMAKE_CXX_EXTENSIONS OFF)

project (chesspp)

include(cmake/Functions.cmake)

set(OUTPUT_DIR ${CMAKE_BINARY_DIR}/output CACHE PATH "")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${OUTPUT_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${OUTPUT_DIR})

set(BOOST_INCLUDE "/src/boost_1_69_0" CACHE PATH "Boost include directory")

add_subdirectory(libchess)
add_subdirectory(test)
