cmake_minimum_required(VERSION 3.19)
project(state_machine_cpp)

set(CMAKE_CXX_STANDARD 14)

add_executable(state_machine_cpp main.cpp states/StateId.cpp states/StateId.h states/StateInstance.cpp states/StateInstance.h utils/comparable.h states/hash.h builder/Builder.cpp builder/Builder.h states/StateAny.h builder/AlgorithmInstance.cpp builder/AlgorithmInstance.h builder/build.h transitions/TransitionHandler.h)