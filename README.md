# state_machine_cpp

## Installation

```shell
sudo ./install
```

## Linking with cmake

```cmake
add_executable(my_target main.cpp)

find_library(STATE_MACHINE_LIBRARY state_machine_cpp)
target_link_libraries(my_target ${STATE_MACHINE_LIBRARY})
```