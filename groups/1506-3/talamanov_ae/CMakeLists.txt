cmake_minimum_required(VERSION 2.8)

project(shell-sort)
add_definitions(-std=c++14)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include_directories(1-test-version)
add_subdirectory(1-test-version)
