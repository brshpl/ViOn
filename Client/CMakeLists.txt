cmake_minimum_required(VERSION 3.17)
project(Client)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -ggdb3 -pthread")


# Создаем статическую библиотеку Socket
set(SOCKET_PATH ../Socket)
set(SOCKET_LIB
        ${SOCKET_PATH}/include/Socket.h
        ${SOCKET_PATH}/src/Socket.cpp)
add_library(socket_lib STATIC ${SOCKET_LIB})
target_include_directories(socket_lib PUBLIC ${SOCKET_PATH}/include)


set(APP_ROOT_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(APP_ROOT_SRC_DIR ${APP_ROOT_DIR}/src)
set(INCLUDES ${APP_ROOT_DIR}/include)

include_directories(${INCLUDES})
file(GLOB sources
        "${APP_ROOT_SRC_DIR}/*.cpp")

add_executable(client ${sources})

# Линкуем библиотеку Socket
target_link_libraries(client PRIVATE socket_lib)


add_definitions(-DSOURCE_DIR="${CMAKE_CURRENT_SOURCE_DIR}")

# googletest
configure_file(CMakeLists.txt.in
        googletest-download/CMakeLists.txt)
execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/googletest-download )
execute_process(COMMAND ${CMAKE_COMMAND} --build .
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/googletest-download )

add_subdirectory(${CMAKE_BINARY_DIR}/googletest-src
        ${CMAKE_BINARY_DIR}/googletest-build)

enable_testing()
add_subdirectory(tests)
