cmake_minimum_required(VERSION 3.17)
project(ping)

set(CMAKE_CXX_STANDARD 11)

include_directories(headers)

add_subdirectory(sources)
add_subdirectory(tests)
add_subdirectory(libs/googletest)
z