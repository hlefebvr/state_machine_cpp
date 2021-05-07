enable_testing()

add_executable(test_state_machine_cpp
        test_main.cpp
        test_utils.h
        test_transition_create.h
        test_transition_create_twice.h
        test_transition_override.h
        test_transition_declare_as_final.h
)

find_package(GTest REQUIRED)
target_link_libraries(test_state_machine_cpp GTest::GTest GTest::Main pthread state_machine_cpp)
