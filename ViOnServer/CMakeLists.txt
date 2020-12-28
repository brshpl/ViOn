cmake_minimum_required(VERSION 2.8.12.2)
project(bin/ViOn_server)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -ggdb3 -pthread")

# add the Server library
set(VION_LIB_DIR ../ViOn_lib)
add_subdirectory(Server)

include_directories(include)

file(GLOB sources
        "include/*.h"
        "src/*.cpp")

# add the executable
add_executable(ViOn_server ${sources})

target_link_libraries(ViOn_server PUBLIC Server)

# add the binary tree to the search path for include files
# so that we will find ViOn_serverConfig.h
target_include_directories(ViOn_server PUBLIC
        "${PROJECT_BINARY_DIR}"
        "${PROJECT_SOURCE_DIR}/Server/include"
        "${VION_LIB_DIR}/FileController/include"
        "${VION_LIB_DIR}/Socket/include"
        )