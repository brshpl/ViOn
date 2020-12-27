cmake_minimum_required(VERSION 3.17)
project(ViOn_server)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -ggdb3 -pthread")

# add the Server library
add_subdirectory(Server)

file(GLOB sources
        ${PROJECT_SOURCE_DIR}/include/*.h
        ${PROJECT_SOURCE_DIR}/src/*.cpp)

include_directories(include)

# add the executable
add_executable(ViOn_server ${sources})

target_link_libraries(ViOn_server PUBLIC Server)

# add the binary tree to the search path for include files
# so that we will find ViOn_serverConfig.h
target_include_directories(ViOn_server PUBLIC
        "${PROJECT_BINARY_DIR}"
        "${PROJECT_SOURCE_DIR}/Server/include"
        "${PROJECT_SOURCE_DIR}/FileController/include"
        "${PROJECT_SOURCE_DIR}/Socket/include"
        )