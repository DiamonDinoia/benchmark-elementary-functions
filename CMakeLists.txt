cmake_minimum_required(VERSION 3.0)
project(benchmark-elementary-functions)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_VERBOSE_MAKEFILE ON)
set(DCMAKE_RULE_MESSAGES OFF)


message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")
if (CMAKE_BUILD_TYPE MATCHES Debug)
    add_compile_options(-fstack-protector-all)
    add_compile_options(-Wall -Wextra -pedantic)
endif ()
if (CMAKE_BUILD_TYPE MATCHES Release)
    add_compile_options(-freciprocal-math -fmerge-all-constants -fno-math-errno -g)
    add_compile_options(-O3 -march=native -funroll-loops -finline-functions -ftree-vectorize)
endif ()

Include(FetchContent)
FetchContent_Declare(
        Catch2
        GIT_REPOSITORY https://github.com/catchorg/Catch2.git
        GIT_TAG v2.13.1)
FetchContent_MakeAvailable(Catch2)

include_directories(inc)

add_executable(log log.cpp)
target_link_libraries(log Catch2::Catch2 m)
add_executable(sincos sincos.cpp)
target_link_libraries(sincos Catch2::Catch2 m)
