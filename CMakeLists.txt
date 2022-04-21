cmake_minimum_required(VERSION 3.21)
project(KSP_public C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_FLAGS -g)
set(CMAKE_CXX_FLAGS -Wall)
set(CMAKE_CXX_FLAGS -std=c99)
set(CMAKE_CXX_FLAGS -pedantic)

add_executable(KSP_public
        aufgaben/a1/solution/njvm.c aufgaben/a1/solution/njvm.h aufgaben/a1/solution/programme.h aufgaben/a1/solution/exec.h aufgaben/a1/solution/exec.c aufgaben/a1/solution/printer.h aufgaben/a1/solution/printer.c)
