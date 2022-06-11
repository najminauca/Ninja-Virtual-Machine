cmake_minimum_required(VERSION 3.21)
project(njvm C)

set(CMAKE_C_STANDARD 99)
add_compile_options(-g -Wall -pedantic)

include_directories(src/bigint/build/include)
link_directories(src/bigint/build/lib)

#include_directories(src/bigint/build/include)
#link_directories(src/bigint/build/lib)
add_executable(njvm src/njvm.c src/njvm.h src/exec.c src/exec.h src/printer.c src/printer.h src/programme.h src/instruction.c src/instruction.h src/support.c)
target_link_libraries(njvm bigint)
