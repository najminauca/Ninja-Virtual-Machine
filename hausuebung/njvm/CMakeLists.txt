cmake_minimum_required(VERSION 3.21)
project(njvm C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_FLAGS -g)
set(CMAKE_CXX_FLAGS -Wall)
set(CMAKE_CXX_FLAGS -std=c99)
set(CMAKE_CXX_FLAGS -pedantic)

add_executable(njvm src/njvm.c src/njvm.h src/exec.c src/exec.h src/printer.c src/printer.h src/programme.h)
