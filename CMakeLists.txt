cmake_minimum_required(VERSION 3.10)
project(OPI8)

set(BUILD_SHARED_LIBS OFF CACHE BOOL "Build shared library")

add_subdirectory(game_lib)

add_executable(OPI main.cpp)
target_link_libraries(OPI game_lib)