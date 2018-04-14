cmake_minimum_required(VERSION 2.8)

SET(CMAKE_CXX_FLAGS "-std=c++11 -O3")
set(PROJ_NAME "ompsolver")
project(${PROJ_NAME})

find_package(OpenMP)
if (OPENMP_FOUND)
    set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
    set (CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_EXE_LINKER_FLAGS}")
endif()

add_library(${PROJECT_NAME}par STATIC "sol.cpp")

#set(CMAKE_EXE_COMPILE_FLAGS "-fopenmp -lgomp")
set(CMAKE_EXE_LINKER_FLAGS "-fopenmp -lgomp")

add_executable(${PROJECT_NAME} before_code.cpp )
#add_executable(${PROJECT_NAME} sol.cpp )

target_link_libraries(${PROJECT_NAME} ${PROJECT_NAME}par)
target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_11)

