# Find LuaBridge library (https://github.com/vinniefalco/LuaBridge)

include(FindPackageHandleStandardArgs)

# Stored in subrepo, platform specific path set by LE_EXTERNAL_LIB_DIR.
find_path(LUABRIDGE_INCLUDE_PATH LuaBridge/LuaBridge.h
  PATHS ${LE_EXTERNAL_INCLUDE_DIR}
  DOC "The directory where LuaBridge/LuaBridge.h resides")

if(LUABRIDGE_INCLUDE_PATH)
  set(LUABRIDGE_FOUND 1 CACHE STRING "Set to 1 if LuaBridge is found, 0 otherwise")
else ()
  set(LUABRIDGE_FOUND 0 CACHE STRING "Set to 1 if LuaBridge is found, 0 otherwise")
endif()

mark_as_advanced(LUABRIDGE_FOUND)

find_package_handle_standard_args(LuaBridge
  REQUIRED_VARS LUABRIDGE_LIBRARY LUABRIDGE_INCLUDE_PATH)
