cmake_minimum_required(VERSION 3.28)
project(Test C)

set(CMAKE_C_STANDARD 17)

add_executable(Test main.c
        dynarr/dynarr.h
        dynarr/chainarr.h
        dynarr/blockarr.h
)
