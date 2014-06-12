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

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release CACHE STRING
      "Choose the type of build, options are: ${CMAKE_CONFIGURATION_TYPES}.")
endif()


if("${CMAKE_SYSTEM_NAME}" STREQUAL "Windows")
  set(LE_TARGET_ARCH "x86" CACHE STRING
    "Determines if application 32 bit or 64 bit. This affects what external libs are used.")
else("${CMAKE_SYSTEM_NAME}" STREQUAL "Linux")
  set(LE_TARGET_ARCH "x64" CACHE STRING
    "Determines if application 32 bit or 64 bit. This affects what external libs are used.")
endif()

set(LE_RUN_SETTINGS_SUPPORTED_IDES "VS2013")

set(LE_RUN_WORKING_DIR "${CMAKE_BINARY_DIR}"
  CACHE PATH
  "The default working directory application will be run from by when working with certain IDEs. Supported: ${LE_RUN_SETTINGS_SUPPORTED_IDES}.")

set(LE_RESOURCE_DIR "${CMAKE_SOURCE_DIR}/resources")

set(LE_EXTERNAL_DEPEND_DIR "${PROJECT_SOURCE_DIR}/external")

set(LE_EXTERNAL_LIB_DIR "${LE_EXTERNAL_DEPEND_DIR}/${CMAKE_SYSTEM_NAME}/lib/${LE_TARGET_ARCH}")
set(LE_EXTERNAL_DLL_DIR "${LE_EXTERNAL_DEPEND_DIR}/${CMAKE_SYSTEM_NAME}/dll/${LE_TARGET_ARCH}")

set(LE_EXTERNAL_INCLUDE_DIR "${LE_EXTERNAL_DEPEND_DIR}/include")
set(LE_EXTERNAL_SRC_DIR "${LE_EXTERNAL_DEPEND_DIR}/src")
