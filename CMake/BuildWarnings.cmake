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

message(STATUS "Setting build warnings for ${CMAKE_CXX_COMPILER_ID}...")
if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
  # TODO - When on a windows machine, find out what default switches are used in VS2013 and add them here.
  add_compile_options(/EHa /MTd /W4 /WX /D_CRT_SECURE_NO_DEPRECATE)
elseif("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
  add_compile_options(-Wall -Wextra -Werror -Wfatal-errors)
  add_compile_options(-pedantic -pedantic-errors)
  # TODO - Determine what warnings shoud be set by reading GCC docs and then set them here.

  # TODO - Place optimization flags for appropriate configurations elsewhere
  #set(-ftree-vectorize -ffast-math -ftree-vectorizer-verbose=1)
endif()
