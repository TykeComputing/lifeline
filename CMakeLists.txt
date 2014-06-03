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

# NOTE - Will start with one project and split into multiple if deemed useful.
cmake_minimum_required(VERSION 2.8)

enable_language(CXX C)

set(LE_CMAKE_DIR ${CMAKE_SOURCE_DIR}/CMake)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${LE_CMAKE_DIR}/Modules)

#include(${LE_CMAKE_DIR}/LifelineVars.cmake)
include(${LE_CMAKE_DIR}/ExternalDependencyRuntimes.cmake)

#setup_lifeline_vars()

message(STATUS "##########################################")
message(STATUS "Targets")
message(STATUS "-------")
message(STATUS "OS: ${CMAKE_SYSTEM_NAME}")
message(STATUS "Compiler: ${CMAKE_CXX_COMPILER_ID}")
message(STATUS "Architecture: ${LE_TARGET_ARCH}")
message(STATUS "Build Type: ${CMAKE_BUILD_TYPE}")
message(STATUS "##########################################")

################################################################
# LIFELINE
################################################################
project(lifeline CXX C)

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
      CACHE PATH
      "Where all external dependency libraries are stored."
      FORCE)

    set(LE_EXTERNAL_DLL_DIR
     "${LE_EXTERNAL_DEPEND_DIR}/windows/dll/${LE_TARGET_ARCH}"
      CACHE PATH
      "Where all external dependency dlls are stored."
      FORCE)

    set(LE_EXTERNAL_INCLUDE_DIR
      "${LE_EXTERNAL_DEPEND_DIR}/windows/include"
      CACHE PATH
      "Where all external dependency includes are stored."
      FORCE)
  endif()

setup_external_dependencies_runtime()

find_package(SDL2 REQUIRED)
find_package(GLEW REQUIRED)
find_package(OpenGL REQUIRED)

# Header files are added so they will show up in all IDEs
set(LE_EXECUTABLE_SRC_LIST
  src/main.cpp

  src/common/error.cpp
  src/common/error.h
  src/common/fatal_construction_exception.cpp
  src/common/fatal_construction_exception.h
  src/common/file_string.cpp
  src/common/file_string.h
  src/common/LE_printf.cpp
  src/common/LE_printf.h
  src/common/macros.h
  src/common/message_exception.cpp
  src/common/message_exception.h
  #src/common/resource.cpp
  #src/common/resource.h
  #src/common/resource_manager.cpp
  #src/common/resource_manager.h
  src/common/resource_exception.cpp
  src/common/resource_exception.h

  src/graphics/error_checking.cpp
  src/graphics/error_checking.h
  src/graphics/shader.cpp
  src/graphics/shader.h
  src/graphics/shader_program.cpp
  src/graphics/shader_program.h
  #src/graphics/shader_program_definition.cpp
  #src/graphics/shader_program_definition.h
  #src/graphics/texture2D.cpp
  #src/graphics/texture2D.h
  src/graphics/vertex.cpp
  src/graphics/vertex.h
  src/graphics/vertex_array.cpp
  src/graphics/vertex_array.h
  src/graphics/vertex_buffer.cpp
  src/graphics/vertex_buffer.h

  src/engine/engine.cpp
  src/engine/engine.h
  src/engine/graphics_context.cpp
  src/engine/graphics_context.h
  src/engine/OS_interface.cpp
  src/engine/OS_interface.h
  src/engine/window.cpp
  src/engine/window.h
)

add_executable(${PROJECT_NAME} ${LE_EXECUTABLE_SRC_LIST})


################################
# COMPILE FLAGS
################################

# NOTE - If split into multiple projects, use the common library to set all compile flags
#       since all other libraries will use it.
# TODO - Consider Wraping platform specific messages with if statements.

message(STATUS "Setting up build warnings...")
target_compile_options(${PROJECT_NAME}
  PUBLIC $<$<CXX_COMPILER_ID:MSVC>:
    /EHa /MTd /W4 /WX /D_CRT_SECURE_NO_DEPRECATE
  >

  PUBLIC $<$<CXX_COMPILER_ID:GNU>:
    -Wall -Wextra -Werror -Wfatal-errors
    -pedantic -pedantic-errors
  >
)


message(STATUS "Setting up C++ runtime libraries...")
target_compile_options(${PROJECT_NAME}
  PUBLIC $<$<CXX_COMPILER_ID:MSVC>:

    # Release configs
    $<$<OR:
      $<CONFIG:RELEASE>,
      $<CONFIG:RELWITHDEBINFO>,
      $<CONFIG:MINSIZEREL> >:
        /MD
    >

    # Debug configs
    $<$<CONFIG:DEBUG>:
      /MDd
    >
) 

message(STATUS "Enabling C++11 support...")
target_compile_options(${PROJECT_NAME}
  PUBLIC $<$<CXX_COMPILER_ID:GNU>:
    -std=c++11
  >
)

target_include_directories(${PROJECT_NAME}
  PUBLIC src
)

################################
# LIFELINE EXTERNAL DEPENDENCIES
################################

# NOTE - If split into multiple projects, set the dependencies only where they're needed
#       using target_*_* and they will be propagated up. For example, linking/including
#       GLEW in graphics. GLEW will only need to be specified in graphics instead of for
#       each target that uses graphics all the way up.
target_include_directories(${PROJECT_NAME}
  PUBLIC ${GLEW_INCLUDE_PATH}
  PUBLIC ${SDL2_INCLUDE_DIR}
)

target_link_libraries(${PROJECT_NAME}
  PUBLIC ${GLEW_LIBRARY}
  PUBLIC ${OPENGL_gl_LIBRARY}
  PUBLIC ${SDL2_LIBRARY}
  #PUBLIC ${SDL2MAIN_LIBRARY}
)
