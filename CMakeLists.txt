cmake_minimum_required(VERSION 3.28)
project(Compilador)

set(CMAKE_CXX_STANDARD 20)

add_executable(Compilador src/compiler.cpp)
add_executable(Interpretador src/Interpreter/interpreter.cpp)
