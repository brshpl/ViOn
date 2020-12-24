cmake_minimum_required(VERSION 3.17)

project(ViOn)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")

##
### Test definitions ###

configure_file(CMakeLists.txt.in
        googletest-download/CMakeLists.txt)
execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" ..
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/googletest-download )
execute_process(COMMAND ${CMAKE_COMMAND} --build ..
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/googletest-download )

add_subdirectory(${CMAKE_BINARY_DIR}/googletest-src
        ${CMAKE_BINARY_DIR}/googletest-build)

enable_testing()
add_subdirectory(../test)


##
### Source definitions ###
##

set(INC_DIR include)
set(SRC_DIR src)

include_directories(${INC_DIR})

file(GLOB sources
        "FileController/include/FileController/*.h"
        "FileController/src/*.cpp")

add_executable(ViOn ${sources})
