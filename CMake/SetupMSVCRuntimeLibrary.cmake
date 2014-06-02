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

set(MSVC_RUNTIME "dynamic" CACHE STRING
  "Valid values: dynamic and static. Controls whether /MD* or /MT* are used")

if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")

  if(${MSVC_RUNTIME} STREQUAL "dynamic")    
    foreach(config_type ${CMAKE_CONFIGURATION_TYPES})
      if(${config_type} MATCHES "/MT")
        string(REGEX REPLACE "/MT" "/MD" ${config_type} "${${config_type}}")
      endif()
    endforeach()

  elseif(${MSVC_RUNTIME} STREQUAL "static")
    foreach(config_type ${CMAKE_CONFIGURATION_TYPES})
      if(${config_type} MATCHES "/MD")
        string(REGEX REPLACE "/MD" "/MT" ${config_type} "${${config_type}}")
      endif()
    endforeach()

  else()
    message(FATAL_ERROR
      "Invalid value given for MSVC_RUNTIME: ${MSVC_RUNTIME}, valid values are static and dynamic.")
    
  endif()
  
  message(STATUS "MSVC: Forcing use of ${MSVC_RUNTIME}ally-linked runtime.")

endif()
