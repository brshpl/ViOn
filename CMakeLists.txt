cmake_minimum_required(VERSION 3.1)
project(ViOn_server CXX C)

set(PROJECT_NAME ViOn_server)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)


set(INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include)
set(SOURCE_DIR ${PROJECT_SOURCE_DIR}/src)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}) # важная строка!!!!!!!!!!!!!!!!!!!!!


include_directories(${INCLUDE_DIR})
include_directories(${SOURCE_DIR})


set(SOURCE_FILES src/main.cpp src/Server.cpp include/Server.h)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})

SET_TARGET_PROPERTIES(ViOn_server PROPERTIES LINKER_LANGUAGE C)


file(GLOB filecontroller_sources
        "include/FileController/*.h"
        "include/FileController/json.hpp"
        "src/FileController/*.cpp")

file(GLOB server_sources
        "include/Server/*.h"
        "src/Server/*.cpp")

file(GLOB socket_sources
        "include/Socket/*.h"
        "src/Socket/*.cpp")

file(GLOB client_sources
        "include/Client/*.h"
        "src/Client/*.cpp")

add_library(filecontroller_lib STATIC ${filecontroller_sources})

add_library(socket_lib STATIC ${socket_sources})

add_library(server_lib STATIC ${server_sources})
target_link_libraries(server_lib ${filecontroller_lib} ${socket_lib})

target_link_libraries(${PROJECT_NAME} PUBLIC server_lib)