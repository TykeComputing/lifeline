################################################################################################
# Copyright 2014 by Peter Clark. All Rights Reserved.
################################################################################################`

# TODO - Add checks for versions of VS < 2013 and add fatal messages

cmake_minimum_required(VERSION 2.8)

enable_language(CXX C)

set(LE_CMAKE_DIR ${CMAKE_SOURCE_DIR}/CMake)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${LE_CMAKE_DIR}/Modules)

set(LE_MESSAGE_LINE_BREAK "################################")
set(LE_MESSAGE_HEADER "----------------")

message(STATUS "${LE_MESSAGE_LINE_BREAK}")
message(STATUS "Targets")
message(STATUS "${LE_MESSAGE_HEADER}")
message(STATUS "OS: ${CMAKE_SYSTEM_NAME}")
message(STATUS "Compiler: ${CMAKE_CXX_COMPILER_ID}")
message(STATUS "Architecture: ${LE_TARGET_ARCH}")
message(STATUS "Build Type: ${CMAKE_BUILD_TYPE}")

message(STATUS "${LE_MESSAGE_LINE_BREAK}")

################################################################
# LIFELINE
################################################################
project(lifeline CXX C)

include(${LE_CMAKE_DIR}/LifelineVars.cmake)
include(${LE_CMAKE_DIR}/ExternalDependencyRuntimes.cmake)

find_package(SDL2 REQUIRED)
find_package(SDL2_ttf REQUIRED)
find_package(GLEW REQUIRED)
find_package(OpenGL REQUIRED)
find_package(CPPFormat REQUIRED)
find_package(Doxygen)

set(LE_SRC_DIR "${CMAKE_SOURCE_DIR}/src/LE")

# Header files are added so they will show up in all IDEs
#
# Files are currently ordered by modules from lowest to highest level to make a change to
# a multi-project setup easier.graphics
set(LE_EXECUTABLE_SRC_LIST
  ${LE_SRC_DIR}/main.cpp

  ${LE_SRC_DIR}/common/char.h
  ${LE_SRC_DIR}/common/cppformat.h
  ${LE_SRC_DIR}/common/fatal_error.cpp
  ${LE_SRC_DIR}/common/fatal_error.h
  ${LE_SRC_DIR}/common/fatal_construction_exception.cpp
  ${LE_SRC_DIR}/common/fatal_construction_exception.h
  ${LE_SRC_DIR}/common/file_string.cpp
  ${LE_SRC_DIR}/common/file_string.h
  ${LE_SRC_DIR}/common/logging.cpp
  ${LE_SRC_DIR}/common/logging.h
  ${LE_SRC_DIR}/common/macros.h
  ${LE_SRC_DIR}/common/profiling.hpp
  ${LE_SRC_DIR}/common/profiling.h
  ${LE_SRC_DIR}/common/profiling_records.cpp
  ${LE_SRC_DIR}/common/profiling_records.h
  #${LE_SRC_DIR}/common/resource.cpp
  #${LE_SRC_DIR}/common/resource.h
  ${LE_SRC_DIR}/common/resource_manager.cpp
  ${LE_SRC_DIR}/common/resource_manager.h
  ${LE_SRC_DIR}/common/resource_exception.cpp
  ${LE_SRC_DIR}/common/resource_exception.h
  ${LE_SRC_DIR}/common/resource_manager.cpp
  ${LE_SRC_DIR}/common/resource_manager.h
  ${LE_SRC_DIR}/common/timer.h
  ${LE_SRC_DIR}/common/timer.cpp
  ${LE_SRC_DIR}/common/unique_id.hpp
  ${LE_SRC_DIR}/common/unique_id.h

  ${LE_SRC_DIR}/math/float.cpp
  ${LE_SRC_DIR}/math/float.hpp
  ${LE_SRC_DIR}/math/float.h
  ${LE_SRC_DIR}/math/mat.cpp
  ${LE_SRC_DIR}/math/mat.hpp
  ${LE_SRC_DIR}/math/mat.h
  ${LE_SRC_DIR}/math/transform.cpp
  ${LE_SRC_DIR}/math/transform.h
  ${LE_SRC_DIR}/math/vec.hpp
  ${LE_SRC_DIR}/math/vec.h

  ${LE_SRC_DIR}/graphics/colors.cpp
  ${LE_SRC_DIR}/graphics/colors.h
  ${LE_SRC_DIR}/graphics/debug_drawer.cpp
  ${LE_SRC_DIR}/graphics/debug_drawer.h
  ${LE_SRC_DIR}/graphics/debug_draw_manager.cpp
  ${LE_SRC_DIR}/graphics/debug_draw_manager.h
  ${LE_SRC_DIR}/graphics/error_checking.cpp
  ${LE_SRC_DIR}/graphics/error_checking.h
  ${LE_SRC_DIR}/graphics/renderable_buffer.cpp
  ${LE_SRC_DIR}/graphics/renderable_buffer.hpp
  ${LE_SRC_DIR}/graphics/renderable_buffer.h
  ${LE_SRC_DIR}/graphics/shader.cpp
  ${LE_SRC_DIR}/graphics/shader.h
  ${LE_SRC_DIR}/graphics/shader_program.cpp
  ${LE_SRC_DIR}/graphics/shader_program.h
  ${LE_SRC_DIR}/graphics/stb_image.cpp
  #${LE_SRC_DIR}/graphics/shader_program_definition.cpp
  #${LE_SRC_DIR}/graphics/shader_program_definition.h
  ${LE_SRC_DIR}/graphics/texture.cpp
  ${LE_SRC_DIR}/graphics/texture.h
  ${LE_SRC_DIR}/graphics/vertex.cpp
  ${LE_SRC_DIR}/graphics/vertex.h
  ${LE_SRC_DIR}/graphics/vertex_array.cpp
  ${LE_SRC_DIR}/graphics/vertex_array.h
  ${LE_SRC_DIR}/graphics/vertex_buffer.cpp
  ${LE_SRC_DIR}/graphics/vertex_buffer.h

  ${LE_SRC_DIR}/engine/component_base.cpp
  ${LE_SRC_DIR}/engine/component_base.h
  ${LE_SRC_DIR}/engine/engine.cpp
  ${LE_SRC_DIR}/engine/engine.h
  ${LE_SRC_DIR}/engine/engine_component_base.cpp
  ${LE_SRC_DIR}/engine/engine_component_base.h
  ${LE_SRC_DIR}/engine/entity.cpp
  ${LE_SRC_DIR}/engine/entity.h
  ${LE_SRC_DIR}/engine/entity.hpp
  ${LE_SRC_DIR}/engine/graphics_context.cpp
  ${LE_SRC_DIR}/engine/graphics_context.h
  ${LE_SRC_DIR}/engine/graphics_system.cpp
  ${LE_SRC_DIR}/engine/graphics_system.h
  ${LE_SRC_DIR}/engine/input_system.cpp
  ${LE_SRC_DIR}/engine/input_system.h
  ${LE_SRC_DIR}/engine/logic_component_base.cpp
  ${LE_SRC_DIR}/engine/logic_component_base.h
  ${LE_SRC_DIR}/engine/logic_system.cpp
  ${LE_SRC_DIR}/engine/logic_system.h
  ${LE_SRC_DIR}/engine/OS_interface.cpp
  ${LE_SRC_DIR}/engine/OS_interface.h
  ${LE_SRC_DIR}/engine/space.cpp
  ${LE_SRC_DIR}/engine/space.hpp
  ${LE_SRC_DIR}/engine/space.h
  ${LE_SRC_DIR}/engine/sprite_component.cpp
  ${LE_SRC_DIR}/engine/sprite_component.h
  ${LE_SRC_DIR}/engine/tilemap_component.cpp
  ${LE_SRC_DIR}/engine/tilemap_component.h
  ${LE_SRC_DIR}/engine/transform_component.cpp
  ${LE_SRC_DIR}/engine/transform_component.h
  ${LE_SRC_DIR}/engine/TTF_system.cpp
  ${LE_SRC_DIR}/engine/TTF_system.h
  ${LE_SRC_DIR}/engine/window.cpp
  ${LE_SRC_DIR}/engine/window.h

  ${LE_SRC_DIR}/devui/perf_vis.cpp
  ${LE_SRC_DIR}/devui/perf_vis.h

  ${LE_SRC_DIR}/game/game_hack.cpp
  ${LE_SRC_DIR}/game/game_hack.h
)

# File specific compile options
if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
  set_source_files_properties(
    ${LE_SRC_DIR}/graphics/stb_image.cpp
      PROPERTIES
        COMPILE_FLAGS "-Wno-unused-but-set-variable -Wno-missing-field-initializers"
  )
endif()

add_executable(${PROJECT_NAME} ${LE_EXECUTABLE_SRC_LIST})

################################
# COMPILE OPTIONS
################################

# NOTE - If split into multiple projects, use the common library to set all compile flags
#       since all other libraries will use it.
# TODO - Consider Wraping platform specific messages with if statements.

message(STATUS "Compiler Setup")
message(STATUS "${LE_MESSAGE_HEADER}")

message(STATUS "Build warnings...")
target_compile_options(${PROJECT_NAME}
  PUBLIC
    $<$<CXX_COMPILER_ID:MSVC>:
      # Enable
      /W4 /WX
    >

    $<$<CXX_COMPILER_ID:GNU>:
      # Enable
      -Wall -Wextra -Werror -Wfatal-errors -Wpedantic
      # Disable
      -Wno-unused-local-typedefs #rapidjson
    >
)

message(STATUS "C++ runtime libraries...")
target_compile_options(${PROJECT_NAME}
  PUBLIC
    $<$<CXX_COMPILER_ID:MSVC>:

      # Release configs
      $<$<OR:$<CONFIG:RELEASE>,$<CONFIG:RELWITHDEBINFO>,$<CONFIG:MINSIZEREL>>:
        /MD
      >

      # Debug configs
      $<$<CONFIG:DEBUG>:
        /MDd
      >
    >
)

message(STATUS "General compile flags...")
target_compile_options(${PROJECT_NAME}
  PUBLIC
    $<$<CXX_COMPILER_ID:GNU>:
      -std=c++11
    >
)

message(STATUS "Preprocessor definitions...")
target_compile_definitions(${PROJECT_NAME}
  PUBLIC
    $<$<CXX_COMPILER_ID:MSVC>:
      /D_CRT_SECURE_NO_DEPRECATE
    >
)

target_include_directories(${PROJECT_NAME}
  PUBLIC
    src
)

message(STATUS "${LE_MESSAGE_LINE_BREAK}")

################################
# POST-BUILD STEPS
################################

if(DOXYGEN_FOUND)
  set(LE_BUILD_DOXYGEN FALSE CACHE BOOL "Whether to use doxygen to build documentation.")

  if(LE_BUILD_DOXYGEN)
    add_custom_command(
      TARGET ${PROJECT_NAME}
      POST_BUILD
      COMMAND ${DOXYGEN_EXECUTABLE} ${CMAKE_SOURCE_DIR}/Doxyfile
      WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
      COMMENT "Building doxygen documentation")
  endif()
endif()

################################
# RUNTIME SETUP
################################

message(STATUS "Runtime Setup")
message(STATUS "${LE_MESSAGE_HEADER}")

option(LE_RUN_WRITE_SETTINGS_FILE
  "Write an IDE specific file that default run environment settings. Will only be written if it does not already exist. To ensure the settings stick ensure the project is not open before configuring."
  ON)

option(LE_RUN_WRITE_SETTINGS_FILE_OVERWRITE
  "Force the existing existing runtime settings file to be overwritten a generated one"
  OFF)

# Optionally create a IDE specific file that contains runtime settings (working dir, command
#   line arguments, etc.). File is only created if it does not exist already.
if(LE_RUN_WRITE_SETTINGS_FILE)
  if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
    set(LE_RUN_SETTINGS_FILE_IN "${LE_CMAKE_DIR}/ConfigureFileTemplates/project.vcxproj.user.in")
    set(LE_RUN_SETTINGS_FILE_OUT "${CMAKE_BINARY_DIR}/${PROJECT_NAME}.vcxproj.user")
    if(NOT EXISTS "${LE_RUN_SETTINGS_FILE_OUT}" OR LE_RUN_WRITE_SETTINGS_FILE_OVERWRITE)
      set(LE_RUN_COMMAND_LINE_ARGS
        "--resource-dir=\"${LE_RESOURCE_DIR}\""
        CACHE PATH
        "The default arguments that will be passed to the application when run when working with certain IDEs. Supported:${LE_RUN_SETTINGS_SUPPORTED_IDES}")

      if(NOT LE_RUN_WRITE_SETTINGS_FILE_OVERWRITE)
        message(STATUS "Project runtime settings file not found, creating...")
      else()
        message(STATUS "Forcing overwrite of project runtime settings file, creating...")
      endif()

      message(STATUS "  Setting project working directory to ${LE_RUN_WORKING_DIR}...")
      message(STATUS "  Setting project command line arguments to ${LE_RUN_COMMAND_LINE_ARGS}...")
      message(STATUS "  Writing ${LE_RUN_SETTINGS_FILE_OUT}...")
      configure_file("${LE_RUN_SETTINGS_FILE_IN}" "${LE_RUN_SETTINGS_FILE_OUT}" @ONLY UNIX)
    else()
      message(STATUS "Project runtime settings file already exists, doing nothing...")
    endif()
  endif()
endif()

setup_external_dependencies_runtime()

message(STATUS "${LE_MESSAGE_LINE_BREAK}")

################################
# EXTERNAL DEPENDENCIES
################################

message(STATUS "External Dependency Setup")

# NOTE - If split into multiple projects, set the dependencies only where they're needed
#       using target_*_* and they will be propagated up. For example, linking/including
#       GLEW in graphics. GLEW will only need to be specified in graphics instead of for
#       each target that uses graphics all the way up.
target_include_directories(${PROJECT_NAME}
  PUBLIC
    ${GLEW_INCLUDE_PATH}
    ${SDL2_INCLUDE_DIR}
    ${SDL2_TTF_INCLUDE_DIR}
    ${CPPFORMAT_INCLUDE_PATH}

    ${LE_EXTERNAL_INCLUDE_DIR}
)

target_link_libraries(${PROJECT_NAME}
  PUBLIC
    general ${GLEW_LIBRARY}
    general ${OPENGL_gl_LIBRARY}
    general ${SDL2_LIBRARY}
    general ${SDL2_TTF_LIBRARY}

  $<$<CXX_COMPILER_ID:MSVC>:
    debug ${CPPFORMAT_LIBRARY_DEBUG}
    optimized ${CPPFORMAT_LIBRARY}
  >

  $<$<CXX_COMPILER_ID:GNU>:
      general ${CPPFORMAT_LIBRARY}
  >
)
