cmake_minimum_required(VERSION 3.20)
project(Raytracer LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
  set(CMAKE_BUILD_TYPE Debug)
endif()

# Code shared by the program and the tests, so tests exercise the real code.
add_library(raytracer_core src/greeting.cpp)
target_include_directories(raytracer_core PUBLIC src)
target_compile_options(raytracer_core PUBLIC
  $<$<CXX_COMPILER_ID:GNU,Clang,AppleClang>:-Wall -Wextra -Wpedantic>
  $<$<CXX_COMPILER_ID:MSVC>:/W4>
)

add_executable(raytracer src/main.cpp)
target_link_libraries(raytracer PRIVATE raytracer_core)

include(FetchContent)
FetchContent_Declare(
  Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG v3.7.1
)
FetchContent_MakeAvailable(Catch2)

enable_testing()

add_executable(raytracer_tests tests/greeting_test.cpp)
target_link_libraries(raytracer_tests PRIVATE raytracer_core Catch2::Catch2WithMain)

list(APPEND CMAKE_MODULE_PATH ${catch2_SOURCE_DIR}/extras)
include(Catch)
catch_discover_tests(raytracer_tests)
