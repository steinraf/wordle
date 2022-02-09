cmake_minimum_required(VERSION 3.21)
project(Wordle)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_FLAGS "-Wpedantic -O3 -fopenmp")

add_executable(Wordle main.cpp src/Game.cpp src/Game.h src/Solver.cpp src/Solver.h src/Statistics.cpp src/Statistics.h)

