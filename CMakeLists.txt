cmake_minimum_required(VERSION 3.12)

project(wssim)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_subdirectory(src)
add_subdirectory(test)
add_subdirectory(example)
