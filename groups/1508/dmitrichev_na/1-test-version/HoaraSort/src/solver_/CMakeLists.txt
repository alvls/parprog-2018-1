cmake_minimum_required(VERSION 2.8)

SET(CMAKE_CXX_FLAGS "-std=c++11 -O3")
set(PROJ_NAME "solver")
project(${PROJ_NAME})

add_library(${PROJECT_NAME}seq STATIC "sol.cpp")

set(CMAKE_EXE_COMPILE_FLAGS "-fopenmp -lgomp")
set(CMAKE_EXE_LINKER_FLAGS "-fopenmp -lgomp")

add_executable(${PROJECT_NAME} before_code.cpp )

target_link_libraries(${PROJECT_NAME} ${PROJECT_NAME}seq)
target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_11)

