project(cppclassgen)
cmake_minimum_required(VERSION 2.8)

message(STATUS "Setting compiler flags for ${CMAKE_CXX_COMPILER_ID}...")
if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
  add_compile_options(/EHa /MTd /W4 /WX /D_CRT_SECURE_NO_DEPRECATE)
elseif("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
  add_compile_options(-std=c++11)
  add_compile_options(-Wall -Wextra -Werror -pedantic -pedantic-errors)
endif()

add_executable(${PROJECT_NAME} main.cpp)
