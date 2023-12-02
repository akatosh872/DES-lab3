cmake_minimum_required(VERSION 3.21)
project(untitled)

set(CMAKE_CXX_STANDARD 14)

add_executable(untitled main.cpp
        DES.cpp
        DES.h
        MatrixConst.h
        FileHandler.cpp
        FileHandler.h
        KeyInput.cpp
        KeyInput.h
        UserInterface.cpp
        UserInterface.h)
