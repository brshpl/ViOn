cmake_minimum_required(VERSION 3.17)
project(VION)

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_C_FLAGS "-g -Wall -Werror -Wextra -O3 -fprofile-arcs -ftest-coverage")
set(CMAKE_CXX_FLAGS "-g -Wall -Werror -O3 -fprofile-arcs -ftest-coverage")

find_package(GTest REQUIRED)
find_package(Threads REQUIRED)

include_directories("${GTEST_INCLUDE_DIRS}")
include_directories(source)
include_directories(includes)

file(GLOB incs "includes/*.h")
file(GLOB srcs "source/Parser.cpp")

add_executable(tests.out tests/tests.cpp
        includes/Parser.h
        source/Parser.cpp)

target_include_directories(tests.out PUBLIC includes)

target_link_libraries(tests.out
        ${GTEST_LIBRARIES}
        Threads::Threads
        pthread)

enable_testing()
add_test(NAME gtest COMMAND tests.out)
