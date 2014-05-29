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

# Will start with one project and split into multiple if deemed useful.
project(lifeline)
cmake_minimum_required(VERSION 2.8)#.12

set(TARGET_ARCH "x86" CACHE STRING "Determines if application 32 bit or 64 bit. This affects what external libs are used.")

set(LE_CMAKE_DIR ${CMAKE_SOURCE_DIR}/CMake)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_SOURCE_DIR}/CMake/Modules/)

if("${CMAKE_SYSTEM_NAME}" STREQUAL "Windows")
  set(LE_EXTERNAL_LIB_DIR "${PROJECT_SOURCE_DIR}/external/windows/lib/${TARGET_ARCH}" CACHE PATH "Where all external dependency libraries are stored.")
  set(LE_EXTERNAL_DLL_DIR "${PROJECT_SOURCE_DIR}/external/windows/dll/${TARGET_ARCH}" CACHE PATH "Where all external dependency dlls are stored.")
  set(LE_EXTERNAL_INCLUDE_DIR "${PROJECT_SOURCE_DIR}/external/windows/include" CACHE PATH "Where all external dependency includes are stored.")
endif()

message(STATUS "##########################################")
message(STATUS "Targets")
message(STATUS "-------")
message(STATUS "OS: ${CMAKE_SYSTEM_NAME}")
message(STATUS "Compiler: ${CMAKE_CXX_COMPILER_ID}")
message(STATUS "Architecture: ${TARGET_ARCH}")
message(STATUS "##########################################")

find_package(SDL2 REQUIRED)
find_package(GLEW REQUIRED)
find_package(OpenGL REQUIRED)

include(${LE_CMAKE_DIR}/BuildWarnings.cmake)
include(${LE_CMAKE_DIR}/SetupLibraries.cmake)

if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
  add_compile_options(-std=c++11)

  if("${TARGET_ARCH}" STREQUAL "x86")
    add_compile_options(-m32)
  endif()
endif()

set(LE_EXECUTABLE_SRC_LIST
  src/main.cpp

  src/common/assert.h
  src/common/fatal_construction_exception.cpp
  src/common/LE_printf.cpp

  src/graphics/shader_program.cpp

  src/engine/engine.cpp
  src/engine/graphics_context.cpp
  src/engine/OS_interface.cpp
  src/engine/window.cpp
)

include_directories(
  src
  ${GLEW_INCLUDE_PATH}
  ${SDL2_INCLUDE_DIR}
)

add_executable(${PROJECT_NAME} ${LE_EXECUTABLE_SRC_LIST})

target_link_libraries(${PROJECT_NAME}
  ${GLEW_LIBRARY}
  ${OPENGL_gl_LIBRARY}
  ${SDL2_LIBRARY}
  ${SDL2MAIN_LIBRARY}
)
