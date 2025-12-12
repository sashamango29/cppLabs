cmake_minimum_required(VERSION 4.0)
project(gameOfLife)

set(CMAKE_CXX_STANDARD 20)

add_executable(gameOfLife main.cpp
        model/universe.cpp
        model/universe.h
        view/view.cpp
        view/view.h
        controller/command.cpp
        controller/command.h
        controller/gameController.cpp
        controller/gameController.h
)
