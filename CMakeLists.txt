cmake_minimum_required(VERSION 3.27)
project(untitled1)

set(CMAKE_CXX_STANDARD 20)


set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fprofile-generate")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fprofile-use")

if (CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Ofast -mavx2 -unroll-loops -march=native -Wall -Wextra -static")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3")
elseif (CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
    add_compile_options(/O2)
    add_compile_options(/W4)
endif()

add_executable(untitled1
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