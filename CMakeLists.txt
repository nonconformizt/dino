cmake_minimum_required(VERSION 3.14)
project(dino)

set(CMAKE_CXX_STANDARD 14)

add_executable(dino main.cpp)

target_link_libraries(dino sfml-graphics sfml-window sfml-system)