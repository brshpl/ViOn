cmake_minimum_required(VERSION 3.17)
project(ViOn)

find_package(GTest REQUIRED)

set(CMAKE_CXX_STANDARD 17)

include_directories(includes)
include_directories(source)
include_directories(tests)


add_executable(tests.out tests/tests.cpp
        includes/message.h
        includes/ChangeCreator.h
        includes/interpretator.h
        includes/parser.h)

