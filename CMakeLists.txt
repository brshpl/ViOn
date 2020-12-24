cmake_minimum_required(VERSION 3.17)
project(ViOn_ncurses)

set(CMAKE_CXX_STANDARD 17)

find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}/include/TextEditor
        ${CMAKE_CURRENT_SOURCE_DIR}/nonlib-include)
file(GLOB sources
        "${PROJECT_SOURCE_DIR}/include/TextEditor/*.h"
        "${PROJECT_SOURCE_DIR}/src/*.cpp"
        "${PROJECT_SOURCE_DIR}/nonlib-include/*.h"
        "${PROJECT_SOURCE_DIR}/nonlib-src/*.cpp")
add_executable(ViOn_ncurses ${sources} example.cpp main.cpp)
target_link_libraries(ViOn_ncurses ${CURSES_LIBRARIES})
