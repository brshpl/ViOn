cmake_minimum_required(VERSION 3.17)
project(Server)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -ggdb3 -pthread")


# Создаем статическую библиотеку Socket
set(SOCKET_PATH ../Socket)
set(SOCKET_LIB
        ${SOCKET_PATH}/Socket.h
        ${SOCKET_PATH}/Socket.cpp)
add_library(socket_lib STATIC ${SOCKET_LIB})
target_include_directories(socket_lib PUBLIC ${SOCKET_PATH})

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
