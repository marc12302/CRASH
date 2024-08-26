cmake_minimum_required(VERSION 3.10)
project(CRASH_GAME)

set(CMAKE_CXX_STANDARD 17)

find_package(Curses REQUIRED)

add_executable(CRASH_GAME main.cpp)
target_link_libraries(CRASH_GAME PRIVATE ${CURSES_LIBRARIES})
include_directories(${CURSES_INCLUDE_DIRS})
