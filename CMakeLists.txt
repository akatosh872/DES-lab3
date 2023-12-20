cmake_minimum_required(VERSION 3.21)
project(untitled)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -ffast-math -march=native -mtune=native")

add_executable(untitled
        main.cpp
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
        include/DESInputHandler.h
)

target_compile_options(untitled PRIVATE -O3 -funroll-loops -finline-functions)