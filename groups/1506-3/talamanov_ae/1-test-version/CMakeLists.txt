set(GEN_SOURCE generator/generator.cpp generator/demo_generator.cpp)
set(GEN_INCLUDE generator/generator.hpp)

set(CHECK_SOURCE checker/checker.cpp)
set(CHECK_INCLUDE checker/checker.cpp)

add_executable(generator ${GEN_SOURCE} ${GEN_INCLUDE})
add_executable(checker ${CHECK_SOURCE} ${CHECK_INCLUDE})
add_executable(before_code before_code.cpp)
