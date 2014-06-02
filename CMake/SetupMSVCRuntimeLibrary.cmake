################################################################################################
# Copyright 2014 Peter Clark
#
# This file is part of Lifeline Engine.
#
# Lifeline Engine is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# Lifeline Engine is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with Lifeline Engine.  If not, see <http://www.gnu.org/licenses/>.
################################################################################################`

# Original implementation: 
# http://stackoverflow.com/questions/10113017/setting-the-msvc-runtime-in-cmake

if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")

set(MSVC_RUNTIME "dynamic" CACHE STRING
  "Valid values: dynamic and static. Controls whether /MD* or /MT* are used")

  # Store all variables of CMAKE_C**_FLAGS_* in CONFIG_FLAG_VARS
  foreach(CONFIG_TYPE ${CMAKE_CONFIGURATION_TYPES})
    set(UPPER_VAR_TEMP)
    string(TOUPPER "CMAKE_C_FLAGS_${CONFIG_TYPE}" UPPER_VAR_TEMP)
    set(CONFIG_FLAG_VARS ${CONFIG_FLAG_VARS} ${UPPER_VAR_TEMP})
    string(TOUPPER "CMAKE_CXX_FLAGS_${CONFIG_TYPE}" UPPER_VAR_TEMP)
    set(CONFIG_FLAG_VARS ${CONFIG_FLAG_VARS} ${UPPER_VAR_TEMP})
    unset(UPPER_VAR_TEMP)
  endforeach()  

  message(STATUS "MSVC: Forcing use of ${MSVC_RUNTIME}ally-linked runtime.")

  # For each variable in CONFIG_FLAG_VARS, replace all instances of MSVC runtime specifying flags
  #   with the appropriate flag.
  if(${MSVC_RUNTIME} STREQUAL "dynamic")    
    foreach(CONFIG_FLAG_VAR_IT ${CONFIG_FLAG_VARS})
      if(${CONFIG_FLAG_VAR_IT} MATCHES "/MT")
        string(REGEX REPLACE "/MT" "/MD" ${CONFIG_FLAG_VAR_IT} "${${CONFIG_FLAG_VAR_IT}}")
      endif()
    endforeach()
  elseif(${MSVC_RUNTIME} STREQUAL "static")
    foreach(CONFIG_FLAG_VAR_IT ${CONFIG_FLAG_VARS})
      if(${CONFIG_FLAG_VAR_IT} MATCHES "/MD")
        string(REGEX REPLACE "/MD" "/MT" ${CONFIG_FLAG_VAR_IT} "${${CONFIG_FLAG_VAR_IT}}")
      endif()
    endforeach()
  else()
    message(FATAL_ERROR
      "Invalid value given for MSVC_RUNTIME: ${MSVC_RUNTIME}, valid values are static and dynamic.")    
  endif()

  # message(STATUS "Initial build flags:")
  # foreach(CONFIG_FLAG_VAR_IT ${CONFIG_FLAG_VARS})
  #   message(STATUS "  '${CONFIG_FLAG_VAR_IT}': ${${CONFIG_FLAG_VAR_IT}}")
  # endforeach()
  # message(STATUS "")
  
endif()
