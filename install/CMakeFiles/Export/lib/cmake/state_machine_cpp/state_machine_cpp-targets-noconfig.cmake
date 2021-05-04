#----------------------------------------------------------------
# Generated CMake target import file.
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "state_machine_cpp::state_machine_cpp" for configuration ""
set_property(TARGET state_machine_cpp::state_machine_cpp APPEND PROPERTY IMPORTED_CONFIGURATIONS NOCONFIG)
set_target_properties(state_machine_cpp::state_machine_cpp PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_NOCONFIG "CXX"
  IMPORTED_LOCATION_NOCONFIG "${_IMPORT_PREFIX}/lib/libstate_machine_cpp.a"
  )

list(APPEND _IMPORT_CHECK_TARGETS state_machine_cpp::state_machine_cpp )
list(APPEND _IMPORT_CHECK_FILES_FOR_state_machine_cpp::state_machine_cpp "${_IMPORT_PREFIX}/lib/libstate_machine_cpp.a" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
