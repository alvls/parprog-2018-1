cmake_minimum_required(VERSION 3.5)
project(LinearCorrection)
set(LIBRARY ${PROJECT_NAME})
add_definitions(-std=c++14)

find_package(OpenCV REQUIRED)
add_library(${LIBRARY} linearcorection.h linearcorection.cpp)

add_executable(generator generator.cpp)
add_executable(checker checker.h checker.cpp sample_checker.cpp)

target_link_libraries(generator ${LIBRARY} ${OpenCV_LIBS})
target_link_libraries(checker ${LIBRARY} ${OpenCV_LIBS})
