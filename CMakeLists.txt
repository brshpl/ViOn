cmake_minimum_required(VERSION 3.17)

project(ViOn)

set(CMAKE_CXX_STANDARD 17)

##
### Test definitions ###

configure_file(CMakeLists.txt.in
        googletest-download/CMakeLists.txt)
execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/googletest-download )
execute_process(COMMAND ${CMAKE_COMMAND} --build .
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/googletest-download )

add_subdirectory(${CMAKE_BINARY_DIR}/googletest-src
        ${CMAKE_BINARY_DIR}/googletest-build)

enable_testing()
add_subdirectory(test)

include(FetchContent)

FetchContent_Declare(json
        GIT_REPOSITORY https://github.com/ArthurSonzogni/nlohmann_json_cmake_fetchcontent
        GIT_TAG v3.9.1)

FetchContent_GetProperties(json)
if(NOT json_POPULATED)
    FetchContent_Populate(json)
    add_subdirectory(${json_SOURCE_DIR} ${json_BINARY_DIR} EXCLUDE_FROM_ALL)
endif()

##
### Source definitions ###
##

set(INC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include/FileController)
set(SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

include_directories(${INC_DIR})

file(GLOB sources
        "${PROJECT_SOURCE_DIR}/include/FileController/*.h"
        "${PROJECT_SOURCE_DIR}/src/*.cpp")

add_executable(ViOn ${sources})


target_link_libraries(ViOn PRIVATE nlohmann_json::nlohmann_json)