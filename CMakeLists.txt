cmake_minimum_required(VERSION 3.15.3)
project(BattleShip)

set(CMAKE_CXX_STANDARD 14)

add_executable(BattleShip main.cpp game.cpp game.h input.cpp input.h board.cpp board.h)