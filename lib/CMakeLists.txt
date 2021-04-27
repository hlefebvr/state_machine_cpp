include(GNUInstallDirs)

# define libray name once and for all
set(LIBRARY_NAME state_machine_cpp)

# define API files
set(PUBLIC_FILES
        include/__comparable.h
        include/__hash.h
        include/__pointer.h
        include/algorithm.h
        include/context.h
        include/builder.h
        include/build.h
        include/plot.h
        include/sanity_check.h
        include/states.h
        include/transitions.h
        include/basics.h
)

# define to-be-compiled files
set(PRIVATE_FILES
        src/algorithm.cpp
        src/builder.cpp
        src/states_any.cpp
        src/states.cpp
        src/transitions.cpp
        src/transition_handlers.cpp
)
list(APPEND PRIVATE_FILES "${PUBLIC_FILES}") # this is for CLion to enable code insight features...

# defines library target
add_library(${LIBRARY_NAME} ${PRIVATE_FILES})

# define C++ version
set_target_properties(${LIBRARY_NAME} PROPERTIES CXX_STANDARD 11)

# define libray version as project's version
set_target_properties(state_machine_cpp PROPERTIES VERSION ${PROJECT_VERSION})

# configures version file
string(TOUPPER ${LIBRARY_NAME} CAPITAL_LIBRARY_NAME)
configure_file(version.h.in ../version.h @ONLY)
list(APPEND PUBLIC_FILES ${PROJECT_BINARY_DIR}/version.h)

# define API
set_target_properties(${LIBRARY_NAME} PROPERTIES PUBLIC_HEADER "${PUBLIC_FILES}")

# define a private include
target_include_directories(${LIBRARY_NAME} PRIVATE include)

# define install target
install(TARGETS ${LIBRARY_NAME}
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/${LIBRARY_NAME}
    )

# define custom target
add_custom_target(install_${LIBRARY_NAME}
                    sudo "${CMAKE_COMMAND}" --build "${CMAKE_BINARY_DIR}" --target install
                    COMMENT "Installing ${LIBRARY_NAME}")
