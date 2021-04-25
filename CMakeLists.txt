cmake_minimum_required(VERSION 3.15)
project(ludum_48)

find_package(raylib 2.5.0 REQUIRED) # Requires at least version 2.5.0

set(CMAKE_C_STANDARD 11)

add_executable(ludum_48 src/main.c)

target_link_libraries(ludum_48 raylib)