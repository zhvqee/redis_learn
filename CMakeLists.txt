# cmake_minimum_required(VERSION <specify CMake version here>)
project(redis_learn C)

set(CMAKE_C_STANDARD 99)

add_executable(redis_learn src/cstring/sds.c src/cstring/sds.h)