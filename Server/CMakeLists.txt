cmake_minimum_required(VERSION 3.17)
project(Server)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -ggdb3 -pthread")


# Создаем статическую библиотеку Socket
set(SOCKET_PATH ../Socket)
set(SOCKET_LIB
        ${SOCKET_PATH}/include/Socket.h
        ${SOCKET_PATH}/src/Socket.cpp)
add_library(socket_lib STATIC ${SOCKET_LIB})
target_include_directories(socket_lib PUBLIC ${SOCKET_PATH}/include)

# Создаем статическую библиотеку
set(FILECONTROLLER_PATH ../FileController)
file(GLOB sources1
        "../FileController/include/FileController/*.h"
        "../FileController/src/*.cpp")
#set(FILECONTROLLER_LIB
#        "${FILECONTROLLER_PATH}/include/FileController/.h"
#        "${FILECONTROLLER_PATH}/src/*.cpp")
add_library(file_controller_lib STATIC ${sources1})
target_include_directories(file_controller_lib PUBLIC ${FILECONTROLLER_PATH}/include)

# Создаем статическую библиотеку Socket
#set(PARSER_PATH ../Parser)
#set(PARSER_LIB
#        ${PARSER_PATH}/include/Parser.h
#        ${PARSER_PATH}/src/Parser.cpp)
#add_library(parser_lib STATIC ${PARSER_LIB})
##add_subdirectory(../Parser)
#target_include_directories(parser_lib PUBLIC ${PARSER_PATH}/include)

include(FetchContent)

FetchContent_Declare(json
        GIT_REPOSITORY https://github.com/ArthurSonzogni/nlohmann_json_cmake_fetchcontent
        GIT_TAG v3.9.1)

FetchContent_GetProperties(json)
if(NOT json_POPULATED)
    FetchContent_Populate(json)
    add_subdirectory(${json_SOURCE_DIR} ${json_BINARY_DIR} EXCLUDE_FROM_ALL)
endif()


set(APP_ROOT_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(APP_ROOT_SRC_DIR ${APP_ROOT_DIR}/src)
set(INCLUDES ${APP_ROOT_DIR}/include)

include_directories(${INCLUDES})
file(GLOB sources
        "${APP_ROOT_SRC_DIR}/*.cpp")

add_executable(server ${sources})

# Линкуем библиотеку Socket
target_link_libraries(server PRIVATE socket_lib)
target_link_libraries(server PRIVATE file_controller_lib)
#target_link_libraries(server PRIVATE parser_lib)

target_link_libraries(server PRIVATE nlohmann_json::nlohmann_json)


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