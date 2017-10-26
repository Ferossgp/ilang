cmake_minimum_required(VERSION 3.6 FATAL_ERROR)
project(ilang VERSION 0.1 LANGUAGES CXX)

add_executable(voc
    main.cpp
)

set(CMAKE_CXX_FLAGS "-std=c++1z  -Werror -Wextra -Wall -Wundef -Wpointer-arith -Wno-sign-compare")