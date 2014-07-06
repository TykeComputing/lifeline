# Lifeline Engine specific modifications:
#   - Changed SDL2_SEARCH_PATHS values to be OS dependent (since they are). (5/2014)
#     - Added Lifeline Engine specific path to external libraries. (5/2014)
# Lifeline Engine specific TODO:
#   - Clean up code added. (5/2014)

# Modified from FindSDL2.cmake

################################
#
# WINDOWS
#
################################
IF("${CMAKE_SYSTEM_NAME}" STREQUAL "Windows")
	FIND_PATH(SDL2_TTF_INCLUDE_DIR SDL_ttf.h
		PATHS ${LE_EXTERNAL_INCLUDE_DIR}/SDL2
	)

	FIND_LIBRARY(SDL2_TTF_LIBRARY
		NAMES SDL2_ttf
		PATHS ${LE_EXTERNAL_LIB_DIR}
	)

################################
#
# LINUX
#
################################
ELSEIF("${CMAKE_SYSTEM_NAME}" STREQUAL "Linux")
	SET(SDL2_TTF_SEARCH_PATHS 
		~/Library/Frameworks
		/Library/Frameworks
		/usr/local
		/usr
		/sw # Fink
		/opt/local # DarwinPorts
		/opt/csw # Blastwave
		/opt
	)

	FIND_PATH(SDL2_TTF_INCLUDE_DIR SDL_ttf.h
		PATH_SUFFIXES include/SDL2 include
		PATHS ${SDL2_TTF_SEARCH_PATHS}
	)

	FIND_LIBRARY(SDL2_TTF_LIBRARY
		NAMES SDL2_ttf
		PATH_SUFFIXES lib64 lib x86_64-linux-gnu
		PATHS ${SDL2_TTF_SEARCH_PATHS}
	)
ELSE()
	# Lifeline Engine TODO - Change this if needed.
	MESSAGE(FATAL "Unable to find SDL2_ttf - UNSUPPORTED PLATFORM")
ENDIF()

INCLUDE(FindPackageHandleStandardArgs)

FIND_PACKAGE_HANDLE_STANDARD_ARGS(SDL2_ttf REQUIRED_VARS SDL2_TTF_LIBRARY SDL2_TTF_INCLUDE_DIR)
