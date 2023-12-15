cmake_minimum_required(VERSION 3.26)
project(modulariser2 C)

set(CMAKE_C_STANDARD 23)

add_executable(modulariser2 main.c
        jeu.c
        mot.c
        score.c)
