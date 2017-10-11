cmake_minimum_required(VERSION 2.8)

project(mirim)
include_directories(include)

set(MR_SRCS mirim.c error.c)
set(MR_SRC_PATH src/mirim)
foreach(SRC ${MR_SRCS})
  list(APPEND MR_SRCS_ABS ${MR_SRC_PATH}/${SRC})
endforeach()

add_library(mirim SHARED ${MR_SRCS_ABS})
add_executable(mirim_sample src/example/mirim.c)
target_link_libraries(mirim_sample mirim)
