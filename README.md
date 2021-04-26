# state_machine_cpp library

![releases](https://img.shields.io/github/v/release/hlefebvr/state_machine_cpp)
![open_issues](https://img.shields.io/github/issues-raw/hlefebvr/state_machine_cpp)
![closed_issues](https://img.shields.io/github/issues-closed-raw/hlefebvr/state_machine_cpp)

## Installation

### Dependencies

This library has no dependency other than, at least, C++11. You will need cmake
to install it, though. Doxygen has to be used to build the documentation.

By default, the library uses the `std::unordered_map` as hash table. **TODO, configure
to use robin_hood implementation**.

### Installation

The following commands will install the library as a shared library. 

```shell
mkdir build
cd build
cmake -DBUILD_SHARED_LIBS=ON .. # to install as a static library, simply use: cmake ..
make
sudo make install
```

By default, on linux, this will install the library in `/usr/local/lib/state_machine_cpp.so`
and include files will be placed in `/usr/local/include/state_machine_cpp/`.

### Compiling and running examples

**Once the library is installed**, you can compile example *example_ForLoop* (for instance)
as follows:
```shell
cd build
cmake ..
make example_ForLoop # for instance
```
Then execute it with
```shell
./examples/for-loop/example_ForLoop
```

### Linking with cmake

Use the following cmake code,
```cmake
add_executable(<MY_TARGET> main.cpp)

find_library(STATE_MACHINE_LIBRARY state_machine_cpp)
target_link_libraries(<MY_TARGET> ${STATE_MACHINE_LIBRARY})
```

Then, your `main.cpp` may look like the following:
```c++
#include <iostream>

int main(int argc, const char** argv) {

    std::cout 
             << "Successfully linked with state_machine_cpp, "
             "version " << STATE_MACHINE_CPP_VERSION_MAJOR
             << '.' << STATE_MACHINE_CPP_VERSION_MINOR 
             << std::endl;
    
    return 0;
}

```

### Building the documentation

To build the documentation, use doxygen as follows:
```shell
cd docs
doxygen Doxyfile
```
