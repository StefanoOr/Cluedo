cmake_minimum_required(VERSION 3.9)
project(Cluedo C)

set(CMAKE_C_STANDARD 99)

add_executable(Cluedo main.c gioco.c gioco.h carte.c carte.h giocatori.c giocatori.h funzioni.c funzioni.h)