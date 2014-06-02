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

if("${CMAKE_SYSTEM_NAME}" STREQUAL "Windows")
  set(LE_EXTERNAL_DEPEND_DIR "${PROJECT_SOURCE_DIR}/external" CACHE PATH
    "Controls the default directory that external dependencies are looked for on a fresh configurtation.")

  set(LE_EXTERNAL_LIB_DIR "${LE_EXTERNAL_DEPEND_DIR}/windows/lib/${TARGET_ARCH}" CACHE PATH
    "Where all external dependency libraries are stored.")
  set(LE_EXTERNAL_DLL_DIR "${LE_EXTERNAL_DEPEND_DIR}/windows/dll/${TARGET_ARCH}" CACHE PATH
    "Where all external dependency dlls are stored.")
  set(LE_EXTERNAL_INCLUDE_DIR "${LE_EXTERNAL_DEPEND_DIR}/windows/include" CACHE PATH
    "Where all external dependency includes are stored.")

  # Copy DLLs into
  message(STATUS "Copying all external DLLs from ${LE_EXTERNAL_DLL_DIR}/ to ${CMAKE_BINARY_DIR}/...")

  file(GLOB EXTERNAL_DLL_COPY_LIST "${LE_EXTERNAL_DLL_DIR}/*.dll")
  if(EXTERNAL_DLL_COPY_LIST)
    foreach(DLL_IT ${EXTERNAL_DLL_COPY_LIST})

      message(STATUS "  Copying ${DLL_IT}...")      
    endforeach()

    file(COPY ${EXTERNAL_DLL_COPY_LIST} DESTINATION "${CMAKE_BINARY_DIR}")    
  else()
    message(STATUS "  Nothing to copy - no external dlls found...")
  endif()

  unset(EXTERNAL_DLL_COPY_LIST)
endif()