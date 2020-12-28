cmake_minimum_required(VERSION 2.8.12.2)
project(TextEditor)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -ggdb3 -pthread")

set(VION_LIB_PATH ../../ViOn_lib)

# Создаем статическую библиотеку Socket
set(SOCKET_PATH ${VION_LIB_PATH}/Socket)
set(SOCKET_LIB
        ${SOCKET_PATH}/include/Socket.h
        ${SOCKET_PATH}/src/Socket.cpp)
add_library(socket_lib STATIC ${SOCKET_LIB})
target_include_directories(socket_lib PUBLIC ${SOCKET_PATH}/include)

# Создаем статическую библиотеку FileController
set(FILECONTROLLER_PATH ${VION_LIB_PATH}/FileController)
file(GLOB file_controller_sources
        ${FILECONTROLLER_PATH}/include/FileController/*.h
        ${FILECONTROLLER_PATH}/src/*.cpp)
add_library(file_controller_lib STATIC ${file_controller_sources})
target_include_directories(file_controller_lib PUBLIC ${FILECONTROLLER_PATH}/include)

# Добавляем Curses
find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIR})

# Добавляем в заголовочные файлы парсер json
include_directories(${FILECONTROLLER_PATH}/nlohmann)

include_directories(include)

file(GLOB sources
        ${PROJECT_SOURCE_DIR}/include/*.h
        ${PROJECT_SOURCE_DIR}/src/*.cpp)


add_library(TextEditor ${sources})

target_link_libraries(TextEditor PRIVATE ${CURSES_LIBRARIES})
target_link_libraries(TextEditor PRIVATE socket_lib)
target_link_libraries(TextEditor PRIVATE file_controller_lib)
