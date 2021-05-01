include(GNUInstallDirs)

# define libray name once and for all
set(LIBRARY_NAME state_machine_cpp)

# define API files
set(PUBLIC_FILES
        include/__comparable.h
        include/__hash.h
        include/__pointer.h
        include/__unordered_map.h
        include/__map.h

        include/state.h
        include/state_id.h
        include/state_instance.h
        include/state_any.h

        include/transition.h
        include/transition_any.h
        include/transition_handlers.h

        include/algorithm.h

        include/builder.h
        include/builder_layers.h
        include/builder_indirection.h
        include/builder_states.h
        include/builder_transitions.h
        include/builder_impl_layers.h
        include/builder_impl_states.h
        include/builder_impl_transitions.h

        include/context.h
        include/context_simple.h
        include/context_layered.h

        include/build.h
        include/plot.h
        include/sanity_check.h
        include/run.h

        include/basics.h
)

# define to-be-compiled files
set(PRIVATE_FILES
        src/__map.cpp

        src/state.cpp
        src/state_any.cpp
        src/state_id.cpp
        src/state_instance.cpp

        src/transition_any.cpp
        src/transition_handlers.cpp

        src/algorithm.cpp

        src/builder.cpp
        src/builder_layers.cpp
        src/builder_indirection.cpp
        src/builder_states.cpp
        src/builder_transitions.cpp
        src/builder_impl_layers.cpp
        src/builder_impl_states.cpp
        src/builder_impl_transitions.cpp

        src/run.cpp

        src/plot.cpp

        src/sanity_check.cpp
)
list(APPEND PRIVATE_FILES "${PUBLIC_FILES}") # this is for CLion to enable code insight features...

# defines library target
add_library(${LIBRARY_NAME} ${PRIVATE_FILES})

# set POSITION_INDEPENDENT_CODE
set_property(TARGET ${LIBRARY_NAME} PROPERTY POSITION_INDEPENDENT_CODE ON)

# define C++ version
set_target_properties(${LIBRARY_NAME} PROPERTIES CXX_STANDARD 17)

# define libray version as project's 0-version
set_target_properties(${LIBRARY_NAME} PROPERTIES VERSION ${PROJECT_VERSION})

# configures version file
string(TOUPPER ${LIBRARY_NAME} CAPITAL_LIBRARY_NAME)
configure_file(version.h.in ../version.h @ONLY)
list(APPEND PUBLIC_FILES ${PROJECT_BINARY_DIR}/version.h)

# define API
set_target_properties(${LIBRARY_NAME} PROPERTIES PUBLIC_HEADER "${PUBLIC_FILES}")

# define a private include
target_include_directories(${LIBRARY_NAME} PRIVATE include)

if (USE_ROBIN_HOOD_UNORDERED_MAP)
    message(STATUS "Using robin_hood::unordered_map")
    add_compile_definitions(USE_ROBIN_HOOD_UNORDERED_MAP)
endif()


# define install target
install(TARGETS ${LIBRARY_NAME}
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/${LIBRARY_NAME}
    )

# define custom target
add_custom_target(install_${LIBRARY_NAME}
                    sudo "${CMAKE_COMMAND}" --build "${CMAKE_BINARY_DIR}" --target install
                    COMMENT "Installing ${LIBRARY_NAME}")
