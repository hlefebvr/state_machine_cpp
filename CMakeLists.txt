cmake_minimum_required(VERSION 3.9)
project(state_machine_cpp VERSION 0.1 DESCRIPTION "State machine algorithms in C++")

set(CMAKE_CXX_STANDARD 11)

add_subdirectory(lib)
add_subdirectory(examples)
add_subdirectory(dev)