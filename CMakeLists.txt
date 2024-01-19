# Entry point CMakeList

cmake_minimum_required(VERSION 3.28)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(MAKE_DIRECTORY ${CMAKE_SOURCE_DIR}/bin/)
set( CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin )

project(StackVector VERSION 1.0)

add_subdirectory("Test1")
add_subdirectory("Test2")
