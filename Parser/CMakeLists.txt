cmake_minimum_required(VERSION 3.17)

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

add_executable(parser ${sources})

target_link_libraries(parser PRIVATE nlohmann_json::nlohmann_json)
