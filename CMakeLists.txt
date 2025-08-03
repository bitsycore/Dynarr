cmake_minimum_required(VERSION 3.20)
project(Dynarr C)

set(CMAKE_C_STANDARD 99)

add_executable(Dynarr main.c
        dynarr/dynarr.h
        dynarr/chainarr.h
        dynarr/blockarr.h
)