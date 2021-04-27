add_executable(2_SquareLoop PowerLoop_main.cpp ../1-for-loop/ForLoop_algorithm.h)

target_include_directories(2_SquareLoop PUBLIC ../../include)
target_link_libraries(2_SquareLoop PUBLIC state_machine_cpp)