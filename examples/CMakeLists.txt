cmake_minimum_required(VERSION 3.9)
project(state_machine_cpp_examples)

set(CMAKE_CXX_STANDARD 11)

find_library(STATE_MACHINE_LIB state_machine_cpp)

if (STATE_MACHINE_LIB)
    add_subdirectory(version)
    add_subdirectory(for-loop)
    add_subdirectory(square-loop)
else()
    message(STATUS "state_machine_cpp is not installed, example targets are therefore not generated...")
endif()
