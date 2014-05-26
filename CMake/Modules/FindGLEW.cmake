#
# Try to find GLEW library and include path.
# Once done this will define
#
# GLEW_FOUND
# GLEW_INCLUDE_PATH
# GLEW_LIBRARY
#

# SOURCE https://code.google.com/p/nvidia-texture-tools/source/browse/trunk/cmake/FindGLEW.cmake?r=96
# Retreived on 5/24/14

# Lifeline Engine specific modifications:
#   - Changed SDL2_SEARCH_PATHS values to be OS dependent (since they are). (5/2014)
#     - Added Lifeline Engine specific path to external libraries. (5/2014)
# Lifeline Engine specific TODO:
#   - Clean up code added. (5/2014)

IF ("${CMAKE_SYSTEM_NAME}" STREQUAL "Windows")
  FIND_PATH( GLEW_INCLUDE_PATH GL/glew.h
    PATHS ${LE_EXTERNAL_INCLUDE_DIR}
    DOC "The directory where GL/glew.h resides")
  FIND_LIBRARY( GLEW_LIBRARY
    NAMES glew GLEW glew32 glew32s
    PATHS ${LE_EXTERNAL_LIB_DIR}
    DOC "The GLEW library")
ELSE ("${CMAKE_SYSTEM_NAME}" STREQUAL "Linux")
  FIND_PATH( GLEW_INCLUDE_PATH GL/glew.h
    /usr/include
    /usr/local/include
    /sw/include
    /opt/local/include
    DOC "The directory where GL/glew.h resides")
  FIND_LIBRARY( GLEW_LIBRARY
    NAMES GLEW glew
    PATH_SUFFIXES lib64 lib
    PATHS
    /usr/lib64
    /usr/lib
    /usr/local/lib64
    /usr/local/lib
    /sw/lib
    /opt/local/lib
    DOC "The GLEW library")

ELSE()
    # Lifeline Engine TODO - Change this if needed.
    MESSAGE(FATAL "Unable to find SDL2 - UNSUPPORTED PLATFORM")
ENDIF ()

IF (GLEW_INCLUDE_PATH)
  SET( GLEW_FOUND 1 CACHE STRING "Set to 1 if GLEW is found, 0 otherwise")
ELSE (GLEW_INCLUDE_PATH)
  SET( GLEW_FOUND 0 CACHE STRING "Set to 1 if GLEW is found, 0 otherwise")
ENDIF (GLEW_INCLUDE_PATH)

MARK_AS_ADVANCED( GLEW_FOUND )
