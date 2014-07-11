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

# Header files are added so they will show up in all IDEs
#
# Files are currently ordered by modules from lowest to highest level to make a change to
# a multi-project setup easier.graphics
set(LE_EXECUTABLE_SRC_LIST
  src/main.cpp

  src/common/cppformat.h
  src/common/fatal_error.cpp
  src/common/fatal_error.h
  src/common/fatal_construction_exception.cpp
  src/common/fatal_construction_exception.h
  src/common/file_string.cpp
  src/common/file_string.h
  src/common/logging.cpp
  src/common/logging.h
  src/common/macros.h
  src/common/message_exception.cpp
  src/common/message_exception.h
  src/common/profiling.hpp
  src/common/profiling.h
  src/common/profiling_records.cpp
  src/common/profiling_records.h
  #src/common/resource.cpp
  #src/common/resource.h
  #src/common/resource_manager.cpp
  #src/common/resource_manager.h
  src/common/resource_exception.cpp
  src/common/resource_exception.h
  src/common/resource_manager.cpp
  src/common/resource_manager.h
  src/common/timer.h
  src/common/timer.cpp
  src/common/unique_id.hpp
  src/common/unique_id.h

  src/math/float.cpp
  src/math/float.hpp
  src/math/float.h
  src/math/mat.cpp
  src/math/mat.hpp
  src/math/mat.h
  src/math/transform.cpp
  src/math/transform.h
  src/math/vec.hpp
  src/math/vec.h

  src/graphics/debug_drawer.cpp
  src/graphics/debug_drawer.h
  src/graphics/debug_draw_manager.cpp
  src/graphics/debug_draw_manager.h
  src/graphics/error_checking.cpp
  src/graphics/error_checking.h
  src/graphics/shader.cpp
  src/graphics/shader.h
  src/graphics/shader_program.cpp
  src/graphics/shader_program.h
  src/graphics/stb_image.cpp
  #src/graphics/shader_program_definition.cpp
  #src/graphics/shader_program_definition.h
  src/graphics/texture.cpp
  src/graphics/texture.h
  src/graphics/vertex.cpp
  src/graphics/vertex.h
  src/graphics/vertex_array.cpp
  src/graphics/vertex_array.h
  src/graphics/vertex_buffer.cpp
  src/graphics/vertex_buffer.h

  src/engine/component_base.cpp
  src/engine/component_base.h
  src/engine/engine.cpp
  src/engine/engine.h
  src/engine/entity.cpp
  src/engine/entity.h
  src/engine/graphics_context.cpp
  src/engine/graphics_context.h
  src/engine/graphics_system.cpp
  src/engine/graphics_system.h
  src/engine/logic_component_base.cpp
  src/engine/logic_component_base.h
  src/engine/OS_interface.cpp
  src/engine/OS_interface.h
  src/engine/space.cpp
  src/engine/space.h
  src/engine/sprite_component.cpp
  src/engine/sprite_component.h
  src/engine/sprite_text_system.cpp
  src/engine/sprite_text_system.h
  src/engine/system_base.cpp
  src/engine/system_base.h
  src/engine/transform_component.cpp
  src/engine/transform_component.h
  src/engine/window.cpp
  src/engine/window.h

  src/devui/perf_vis.cpp
  src/devui/perf_vis.h

  src/game/game_hack.cpp
  src/game/game_hack.h
)

# File specific compile options
if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
  set_source_files_properties(
    ${CMAKE_SOURCE_DIR}/src/graphics/stb_image.cpp
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
