cmake_minimum_required(VERSION 2.8.4)
project(clouten_cs)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

include_directories("include")

add_subdirectory("02-memory")
add_subdirectory("scratch")

