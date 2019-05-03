cmake_minimum_required(VERSION 3.14)
project(dino)

set(CMAKE_CXX_STANDARD 14)

add_executable(
        dino
        main.cpp
        config.h
        Entity.hpp
        Entity.cpp
        Player.hpp
        Player.cpp
        Missile.hpp
        Missile.cpp
        Level.hpp
        Level.cpp
        Camera.hpp
        Camera.cpp
)

target_link_libraries(dino sfml-graphics sfml-window sfml-system)