cmake_minimum_required (VERSION 2.6)
project (GaussianOpenMP)

list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR})

find_package(TBB)

include_directories(${TBB_INCLUDE_DIRS})
add_definitions(${TBB_DEFINITIONS})

add_executable(GaussianTBB gaussian_tbb_source.cpp)
target_link_libraries(GaussianTBB ${TBB_LIBRARIES})