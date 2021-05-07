cmake_minimum_required(VERSION 3.9)

# Define project
project(
        state_machine_cpp
        VERSION         1.0.6
        LANGUAGES       CXX
        DESCRIPTION     "State machine library written in C++"
)

# Define public files
set(PUBLIC_FILES
        state_machine_cpp/include/impl/__comparable.h
        state_machine_cpp/include/impl/__hash.h
        state_machine_cpp/include/impl/__pointer.h
        state_machine_cpp/include/impl/__unordered_map.h
        state_machine_cpp/include/impl/__map.h

        state_machine_cpp/include/states/state.h
        state_machine_cpp/include/states/state_id.h
        state_machine_cpp/include/states/state_instance.h
        state_machine_cpp/include/states/state_any.h

        state_machine_cpp/include/transitions/transition.h
        state_machine_cpp/include/transitions/transition_any.h
        state_machine_cpp/include/transitions/transition_handlers.h

        state_machine_cpp/include/algorithms/algorithm.h

        state_machine_cpp/include/builder/builder.h
        state_machine_cpp/include/builder/builder_types.h
        state_machine_cpp/include/builder/builder_layers.h
        state_machine_cpp/include/builder/builder_indirection.h
        state_machine_cpp/include/builder/builder_states.h
        state_machine_cpp/include/builder/builder_transitions.h
        state_machine_cpp/include/builder/builder_impl_layers.h
        state_machine_cpp/include/builder/builder_impl_states.h
        state_machine_cpp/include/builder/builder_impl_transitions.h

        state_machine_cpp/include/context/context.h
        state_machine_cpp/include/context/context_simple.h
        state_machine_cpp/include/context/context_layered.h
        state_machine_cpp/include/context/context_auto.h

        state_machine_cpp/include/algorithms/build.h
        state_machine_cpp/include/algorithms/plot.h
        state_machine_cpp/include/algorithms/sanity_check.h
        state_machine_cpp/include/algorithms/run.h

        state_machine_cpp/include/basics.h
)

# Define private files
set(PRIVATE_FILES
        state_machine_cpp/src/impl/__map.cpp

        state_machine_cpp/src/states/state.cpp
        state_machine_cpp/src/states/state_any.cpp
        state_machine_cpp/src/states/state_id.cpp
        state_machine_cpp/src/states/state_instance.cpp

        state_machine_cpp/src/transitions/transition_any.cpp
        state_machine_cpp/src/transitions/transition_handlers.cpp

        state_machine_cpp/src/algorithms/algorithm.cpp

        state_machine_cpp/src/builder/builder.cpp
        state_machine_cpp/src/builder/builder_layers.cpp
        state_machine_cpp/src/builder/builder_indirection.cpp
        state_machine_cpp/src/builder/builder_states.cpp
        state_machine_cpp/src/builder/builder_transitions.cpp
        state_machine_cpp/src/builder/builder_impl_layers.cpp
        state_machine_cpp/src/builder/builder_impl_states.cpp
        state_machine_cpp/src/builder/builder_impl_transitions.cpp

        state_machine_cpp/src/context/context_auto.cpp

        state_machine_cpp/src/algorithms/run.cpp

        state_machine_cpp/src/algorithms/plot.cpp

        state_machine_cpp/src/algorithms/sanity_check.cpp
)

# Define Library
add_library(state_machine_cpp ${PRIVATE_FILES} ${PUBLIC_FILES})

# Define c++ version
target_compile_features(state_machine_cpp PUBLIC cxx_std_17)

# Define include directories
target_include_directories(state_machine_cpp
        PUBLIC
        $<INSTALL_INTERFACE:include/state_machine_cpp>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/state_machine_cpp/include>
        PRIVATE state_machine_cpp/src
        )

# Adds pthread as dependency
target_link_libraries(state_machine_cpp PRIVATE pthread)

# Imports some variables
include(GNUInstallDirs)

# Create install
install(TARGETS             state_machine_cpp
        EXPORT              state_machine_cpp-export
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        )

# Install include files
foreach(PUBLIC_FILE ${PUBLIC_FILES})
    get_filename_component(PUBLIC_FILE_LOCATION ${PUBLIC_FILE} DIRECTORY)
    STRING(REGEX REPLACE "/include" "" PUBLIC_FILE_DESTINATION ${PUBLIC_FILE_LOCATION})
    install(FILES ${PUBLIC_FILE} DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/${PUBLIC_FILE_DESTINATION})
endforeach()

# Exports targets
install(EXPORT      state_machine_cpp-export
        FILE        state_machine_cpp-targets.cmake
        NAMESPACE   state_machine_cpp::
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/state_machine_cpp
        )
set(STATE_MACHINE_CPP_TARGETS_FILE ${CMAKE_INSTALL_FULL_LIBDIR}/cmake/state_machine_cpp/state_machine_cpp-targets.cmake)

# Imports functions
include(CMakePackageConfigHelpers)

# Create Config file
configure_package_config_file(
        ${CMAKE_CURRENT_LIST_DIR}/cmake/state_machine_cpp-config.cmake.in
        ${CMAKE_CURRENT_BINARY_DIR}/state_machine_cpp-config.cmake
        INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake
)

# Install config files
install(FILES
        ${CMAKE_CURRENT_BINARY_DIR}/state_machine_cpp-config.cmake
        DESTINATION ${CMAKE_INSTALL_DATADIR}/state_machine_cpp/cmake
        )

# Add tests
option(COMPILE_TESTS "ON if the tests should be compiled" OFF)
if (COMPILE_TESTS)
    add_subdirectory(tests)
endif()
#unset(COMPILE_TESTS CACHE)
