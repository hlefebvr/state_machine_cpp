add_executable(example_ForLoop _example_ForLoop_main.cpp)

target_link_libraries(example_ForLoop PUBLIC state_machine_cpp)
target_include_directories(example_ForLoop PUBLIC ../../src)
