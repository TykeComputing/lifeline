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

function(setup_external_dependencies_runtime)
  if("${CMAKE_SYSTEM_NAME}" STREQUAL "Windows")

    option(LE_COPY_EXTERNAL_DLLS_TO_WORKING_DIR
      "Copy external dependency DLLs to the working directory upon configuration." 
      ON)

    if(LE_COPY_EXTERNAL_DLLS_TO_WORKING_DIR)
      message(STATUS "Copying all external DLLs from ${LE_EXTERNAL_DLL_DIR}/ to ${LE_WORKING_DIR}/...")

      file(GLOB EXTERNAL_DLL_COPY_LIST "${LE_EXTERNAL_DLL_DIR}/*.DLL")
      if(EXTERNAL_DLL_COPY_LIST)
        foreach(DLL_IT ${EXTERNAL_DLL_COPY_LIST})

          message(STATUS "  Copying ${DLL_IT}...")      
        endforeach()

        file(COPY ${EXTERNAL_DLL_COPY_LIST} DESTINATION "${LE_WORKING_DIR}")    
      else()
        message(STATUS "  Nothing to copy - no external DLLs found...")
      endif()

      unset(EXTERNAL_DLL_COPY_LIST)
    endif()
  endif()
endfunction()