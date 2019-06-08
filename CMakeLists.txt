cmake_minimum_required (VERSION 3.5.1)

set (CMAKE_CXX_STANDARD 17)
set (CMAKE_CXX_STANDARD_REQUIRED ON)
set (CMAKE_CXX_EXTENSIONS OFF)
set (CMAKE_EXPORT_COMPILE_COMMANDS ON)

project (chesspp)

include(cmake/Functions.cmake)

find_boost()

set(OUTPUT_DIR ${CMAKE_BINARY_DIR}/output CACHE PATH "")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${OUTPUT_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${OUTPUT_DIR})

add_subdirectory(libchess)
add_subdirectory(libchessui)
add_subdirectory(test)
add_subdirectory(chesspp)
