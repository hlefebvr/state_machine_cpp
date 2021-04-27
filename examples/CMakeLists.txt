cmake_minimum_required(VERSION 3.9)
project(state_machine_cpp_examples)

set(CMAKE_CXX_STANDARD 11)

find_library(STATE_MACHINE_LIB state_machine_cpp REQUIRED)

add_subdirectory(0-version)
add_subdirectory(1-for-loop)
add_subdirectory(2-power-loop)
