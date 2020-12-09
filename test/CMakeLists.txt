include_directories("${PROJECT_SOURCE_DIR}/include")

include(FetchContent)

FetchContent_Declare(json
        GIT_REPOSITORY https://github.com/ArthurSonzogni/nlohmann_json_cmake_fetchcontent
        GIT_TAG v3.9.1)

FetchContent_GetProperties(json)
if(NOT json_POPULATED)
    FetchContent_Populate(json)
    add_subdirectory(${json_SOURCE_DIR} ${json_BINARY_DIR} EXCLUDE_FROM_ALL)
endif()


file(GLOB sources "${PROJECT_SOURCE_DIR}/src/*.cpp")
list(REMOVE_ITEM sources "${PROJECT_SOURCE_DIR}/src/main.cpp")

file(GLOB tests "${PROJECT_SOURCE_DIR}/test/*.cpp")
list(REMOVE_ITEM tests "${PROJECT_SOURCE_DIR}/test/main.cpp")

foreach(file ${tests})
    set(name)
    get_filename_component(name ${file} NAME_WE)
    add_executable("${name}_tests"
            ${sources}
            ${file}
            "${PROJECT_SOURCE_DIR}/test/main.cpp")
    target_link_libraries("${name}_tests" gtest_main nlohmann_json::nlohmann_json)
    add_test(NAME ${name} COMMAND "${name}_tests")
endforeach()

