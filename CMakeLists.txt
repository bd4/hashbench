cmake_minimum_required(VERSION 3.18 FATAL_ERROR)
project(hashbench
        VERSION 0.01
        LANGUAGES CXX)

if (NOT CMAKE_BUILD_TYPE)
  message(STATUS "hashbench: Setting build type to 'Release' since none specified.")
  set(CMAKE_BUILD_TYPE "Release"
      CACHE STRING "Choose the type of build." FORCE)
endif()

include(cmake/CPM.cmake)
list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake/")

CPMAddPackage(
  NAME benchmark
  GITHUB_REPOSITORY google/benchmark
  GIT_TAG v1.6.1
  VERSION v1.6.1
  GIT_SHALLOW TRUE
  OPTIONS
    "BENCHMARK_ENABLE_TESTING OFF"
    "BENCHMARK_ENABLE_INSTALL OFF"
    "BENCHMARK_ENABLE_WERROR OFF"
    "CMAKE_BUILD_TYPE Release"
)

set(CMAKE_CXX_STANDARD 20)
add_subdirectory(src)
