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
        Cactus.hpp
        Cactus.cpp
        Pterodactyl.cpp
        Pterodactyl.hpp
        Menu/Menu.cpp
        Menu/Menu.hpp
        Menu/Rating.cpp
        Menu/Rating.hpp
        Menu/LevelMenu.cpp
        Menu/LevelMenu.hpp
        Menu/Modal.cpp
        Menu/Modal.hpp
        StandardMode.cpp
        StandardMode.hpp
        globals.hpp
        Coin.cpp
        Coin.hpp
        Menu/CharacterMenu.cpp
        Menu/CharacterMenu.hpp)

target_link_libraries(dino sfml-graphics sfml-window sfml-system)