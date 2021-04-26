find_library(STATE_MACHINE_LIB state_machine_cpp)

if (STATE_MACHINE_LIB)
    add_executable(example_ForLoop _example_ForLoop_main.cpp _example_for_loop.h)
    target_link_libraries(example_ForLoop PUBLIC state_machine_cpp)
else()
    message(STATUS "state_machine_cpp is not installed, example targets are therefore not generated...")
endif()
