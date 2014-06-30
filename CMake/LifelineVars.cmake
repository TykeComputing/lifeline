################################################################################################
# Copyright 2014 by Peter Clark. All Rights Reserved.
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
