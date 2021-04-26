add_executable(example_SquareLoop _example_SquareLoop_main.cpp ../for-loop/_example_for_loop.h)

target_include_directories(example_SquareLoop PUBLIC ../../include)
target_link_libraries(example_SquareLoop PUBLIC state_machine_cpp)