cmake_minimum_required(VERSION 3.14)
project(wssim_app)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(include)

add_executable(wssim_app main.cc)
target_link_libraries(wssim_app libtestcase)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/python/draw.py DESTINATION ${CMAKE_CURRENT_BINARY_DIR})