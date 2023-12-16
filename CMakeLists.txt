cmake_minimum_required(VERSION 3.21)
project(untitled)

set(CMAKE_CXX_STANDARD 14)

add_executable(untitled main.cpp
        source/DES.cpp
        include/DES.h
        include/MatrixConst.h
        source/FileHandler.cpp
        include/FileHandler.h
        source/InputHandler.cpp
        include/InputHandler.h
        source/DesEncryptor.cpp
        include/DesEncryptor.h
        source/DESInputHandler.cpp
        include/DESInputHandler.h)
