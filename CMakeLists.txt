cmake_minimum_required(VERSION 3.17)
project(VION)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_FLAGS "-g -Wall -Werror -O0 -fprofile-arcs -ftest-coverage")

find_package(GTest REQUIRED)
find_package(Threads REQUIRED)

include_directories("${GTEST_INCLUDE_DIRS}")
include_directories(source)
include_directories(includes)
include_directories(nlohmann)

add_executable(tests.out
        nlohmann/json.hpp
        source/JsonParser.cpp
        tests/tests.cpp
        source/ChangeCreator.cpp 
        source/Interpretator.cpp)

target_include_directories(tests.out PUBLIC includes)
target_include_directories(tests.out PUBLIC nlohmann)

target_link_libraries(tests.out
        ${GTEST_LIBRARIES}
        Threads::Threads
        pthread)

enable_testing()
add_test(NAME gtest COMMAND tests.out)
