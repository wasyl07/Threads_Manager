#----------------------------------------------------------------
# Generated CMake target import file for configuration "Debug".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "Threading::Threads_Manager" for configuration "Debug"
set_property(TARGET Threading::Threads_Manager APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(Threading::Threads_Manager PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_DEBUG "CXX"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/lib/libThreads_Managerd.a"
  )

list(APPEND _IMPORT_CHECK_TARGETS Threading::Threads_Manager )
list(APPEND _IMPORT_CHECK_FILES_FOR_Threading::Threads_Manager "${_IMPORT_PREFIX}/lib/libThreads_Managerd.a" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
