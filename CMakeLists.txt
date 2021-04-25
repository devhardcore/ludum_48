cmake_minimum_required(VERSION 3.15)
project(my_project)

find_package(raylib 2.5.0 REQUIRED) # Requires at least version 2.5.0

set(CMAKE_C_STANDARD 11)

add_executable(my_project src/snake.c)

target_link_libraries(my_project raylib)