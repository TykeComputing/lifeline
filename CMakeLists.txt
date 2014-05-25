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

cmake_minimum_required(VERSION 2.8)

# Will start with one project and split into multiple if deemed useful.
project(lifeline)

set(LE_CMAKE_DIR ${CMAKE_SOURCE_DIR}/CMake)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_SOURCE_DIR}/CMake/Modules/)

message(FATAL ${LE_CMAKE_DIR})
message(FATAL ${CMAKE_MODULE_PATH})

find_package(SDL2 REQUIRED)
find_package(GLEW REQUIRED)
find_package(OpenGL REQUIRED)

include(${LE_CMAKE_DIR}/BuildWarnings.cmake)
add_definitions(-std=c++11)

set(LE_EXECUTABLE_SRC_LIST
  src/main.cpp
)

include_directories(
  ${GLEW_INCLUDE_PATH}
  ${SDL2_INCLUDE_DIR}
)

add_executable(${PROJECT_NAME} ${LE_EXECUTABLE_SRC_LIST})

target_link_libraries(${PROJECT_NAME}
  ${GLEW_LIBRARY}
  ${OPENGL_gl_LIBRARY}
  ${SDL2_LIBRARY}
)
