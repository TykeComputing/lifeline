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

macro(setup_lifeline_vars)
  if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release CACHE STRING
        "Choose the type of build, options are: ${CMAKE_CONFIGURATION_TYPES}.")
  endif()

  set(LE_TARGET_ARCH "x86" CACHE STRING
    "Determines if application 32 bit or 64 bit. This affects what external libs are used.")  

  if("${CMAKE_SYSTEM_NAME}" STREQUAL "Windows")
    set(LE_EXTERNAL_DEPEND_DIR
     "${PROJECT_SOURCE_DIR}/external" 
     CACHE PATH
     "Controls the default directory that external dependencies are looked for on a fresh configurtation."
     FORCE)

    set(LE_EXTERNAL_LIB_DIR
     "${LE_EXTERNAL_DEPEND_DIR}/windows/lib/${LE_TARGET_ARCH}"
      CACHE INTERNAL PATH
      "Where all external dependency libraries are stored."
      FORCE)

    set(LE_EXTERNAL_DLL_DIR
     "${LE_EXTERNAL_DEPEND_DIR}/windows/dll/${LE_TARGET_ARCH}"
      CACHE INTERNAL PATH
      "Where all external dependency dlls are stored."
      FORCE)

    set(LE_EXTERNAL_INCLUDE_DIR
      "${LE_EXTERNAL_DEPEND_DIR}/windows/include"
      CACHE INTERNAL PATH
      "Where all external dependency includes are stored."
      FORCE)
  endif()
endmacro()