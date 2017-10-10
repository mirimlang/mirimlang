cmake_minimum_required(VERSION 2.8)

project(mirim)
include_directories(include)
add_library(mirim src/mirim/mirim.c)
add_executable(mirim_sample src/example/mirim.c)
target_link_libraries(mirim_sample mirim)
