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
################################################################################################

if("${CMAKE_SYSTEM_NAME}" STREQUAL "Windows")
  message(STATUS "Copying all external DLLs from {LE_EXTERNAL_DLL_DIR}/...")
  
  file(GLOB EXTERNAL_DLL_REMOVAL_LIST "${CMAKE_BINARY_DIR}*.dll")
  if(EXTERNAL_DLL_REMOVAL_LIST)
    message(STATUS "  Removing ${EXTERNAL_DLL_REMOVAL_LIST}...")
    file(REMOVE ${EXTERNAL_DLL_REMOVAL_LIST})
  else()
    message(STATUS "  Nothing to remove - no existing external dlls found...")
  endif()

  file(GLOB EXTERNAL_DLL_COPY_LIST "${LE_EXTERNAL_DLL_DIR}/*.dll")
  message(STATUS " test ${LE_EXTERNAL_DLL_DIR}")
  if(EXTERNAL_DLL_COPY_LIST)
    message(STATUS "  Copying ${EXTERNAL_DLL_COPY_LIST}...")
    file(COPY ${EXTERNAL_DLL_COPY_LIST} DESTINATION "${CMAKE_BINARY_DIR}")
  else()
    message(STATUS "  Nothing to copy - no external dlls found...")
  endif()

  unset(EXTERNAL_DLL_REMOVAL_LIST)
  unset(EXTERNAL_DLL_COPY_LIST)
endif()
