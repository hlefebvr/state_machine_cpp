include(GNUInstallDirs)

# define libray name once and for all
set(LIBRARY_NAME state_machine_cpp)

# define API files
set(PUBLIC_FILES
        include/AlgorithmInstance.h
        include/Builder_States.h
        include/build.h
        include/Context.h
        include/InitialContext.h
        include/Pointer.h
        include/StateAny.h
        include/StateInstance.h
        include/TransitionHandler.h
        include/Builder.h
        include/Builder_Transitions.h
        include/comparable.h
        include/hash.h
        include/plot.h
        include/sanity_check.h
        include/StateId.h
        include/TransitionAny.h
)

# define to-be-compiled files
set(PRIVATE_FILES
        src/AlgorithmInstance.cpp
        src/Builder.cpp
        src/Builder_States.cpp
        src/Builder_Transitions.cpp
        src/StateAny.cpp
        src/StateId.cpp
        src/StateInstance.cpp
        src/TransitionAny.cpp
        src/TransitionHandler.cpp
)

# defines library target
add_library(${LIBRARY_NAME} ${PRIVATE_FILES})

# define C++ version
set_target_properties(${LIBRARY_NAME} PROPERTIES CXX_STANDARD 11)

# define libray version as project's version
set_target_properties(state_machine_cpp PROPERTIES VERSION ${PROJECT_VERSION})

# configures version file
string(TOUPPER ${LIBRARY_NAME} CAPITAL_LIBRARY_NAME)
configure_file(version.h.in version.h)
list(APPEND ${PUBLIC_FILES} ${PROJECT_BINARY_DIR}/version.h)

# define API
set_target_properties(${LIBRARY_NAME} PROPERTIES PUBLIC_HEADER "${PUBLIC_FILES}")

# define a private include
target_include_directories(${LIBRARY_NAME} PRIVATE include)

# define install target
install(TARGETS ${LIBRARY_NAME}
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/${LIBRARY_NAME}
    )
