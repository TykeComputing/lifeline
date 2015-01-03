# Find cppformat library (https://github.com/cppformat/cppformat)

include(FindPackageHandleStandardArgs)

# Stored in subrepo, platform specific path set by LE_EXTERNAL_LIB_DIR.
find_path(CPPFORMAT_INCLUDE_PATH cppformat/format.h
  PATHS ${LE_EXTERNAL_INCLUDE_DIR}
  DOC "The directory where cppformat/format.h resides")

find_library(CPPFORMAT_LIBRARY
  NAMES format
  PATH_SUFFIXES lib
  PATHS ${LE_EXTERNAL_LIB_DIR}
  DOC "The cppformat library")

if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
  find_library(CPPFORMAT_LIBRARY_DEBUG
    NAMES formatd
    PATH_SUFFIXES lib
    PATHS ${LE_EXTERNAL_LIB_DIR}
    DOC "The cppformat library, debug version")
else()
  set(CPPFORMAT_LIBRARY_DEBUG "NOT_USED")
endif()

if(CPPFORMAT_INCLUDE_PATH)
  set(CPPFORMAT_FOUND 1 CACHE STRING "Set to 1 if GLEW is found, 0 otherwise")
else ()
  set(CPPFORMAT_FOUND 0 CACHE STRING "Set to 1 if GLEW is found, 0 otherwise")
endif()

mark_as_advanced(CPPFORMAT_FOUND)

find_package_handle_standard_args(CPPFormat
  REQUIRED_VARS CPPFORMAT_LIBRARY CPPFORMAT_INCLUDE_PATH)
