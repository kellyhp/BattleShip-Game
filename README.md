##### Table of Contents  
* [General Info](#general-info)  
* [Technologies](#technologies) 
* [Setup](#setup)
   
## General Info
This project is a scratch version of a Battleship game where two players will first place their board in the game and then they will take turns guessing the location of their opponent's ship. The game returns back whether the shots fired were hit/missed and will end the game once all the ships on a player's board is destroyed. The boundaries of the board and number/name of ships along with its length is opened and read from a file.

## Technologies
Project is created with:
- CLion 2022.2.1 (can use any other IDE that is C++/C compatible)
- CMake (VERSION 3.15.3)
- CMAKE 14

## Setup 
To run this project, run any IDE for C/C++ and make sure CMake file has all of the files together. Write out the file name that hold all the information of the boundaries of the board and name of the ships that holds the size too in the runtime command line arguments.
For example:

```
$ GameConfigurations/filename.txt
```

This is what my CMakeList.txt file looks like to incorporated all of the files together.
```
cmake_minimum_required(VERSION 3.15.3)
project(BattleShip)

set(CMAKE_CXX_STANDARD 14)

add_executable(BattleShip main.cpp game.cpp game.h input.cpp input.h board.cpp board.h)

```


