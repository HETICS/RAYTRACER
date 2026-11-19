cmake_minimum_required(VERSION 3.20)
project(Raytracer LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
  set(CMAKE_BUILD_TYPE Debug)
endif()

include(FetchContent)

# LodePNG has no releases and no CMake project, so we pin a commit and build it here.
FetchContent_Declare(
  lodepng
  GIT_REPOSITORY https://github.com/lvandeve/lodepng.git
  GIT_TAG 7b2893e35891c0c85bee5595caafaf3c2044b409
)
FetchContent_MakeAvailable(lodepng)
add_library(lodepng STATIC ${lodepng_SOURCE_DIR}/lodepng.cpp)
target_include_directories(lodepng PUBLIC ${lodepng_SOURCE_DIR})

# Code shared by the program and the tests, so tests exercise the real code.
add_library(raytracer_core
  src/greeting.cpp
  src/math/vector.cpp
  src/colour/colour.cpp
  src/render/camera.cpp
  src/render/trace.cpp
  src/image/image.cpp
  src/io/png_saver.cpp
  src/material/flat_shader.cpp
  src/material/lambert_shader.cpp
  src/light/light.cpp
  src/geometry/sphere.cpp
  src/geometry/plane.cpp
  src/scene/scene.cpp
  src/geometry/ray.cpp
)
target_include_directories(raytracer_core PUBLIC src)
target_link_libraries(raytracer_core PRIVATE lodepng)
target_compile_options(raytracer_core PUBLIC
  $<$<CXX_COMPILER_ID:GNU,Clang,AppleClang>:-Wall -Wextra -Wpedantic>
  $<$<CXX_COMPILER_ID:MSVC>:/W4>
)

add_executable(raytracer src/main.cpp)
target_link_libraries(raytracer PRIVATE raytracer_core)

FetchContent_Declare(
  Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG v3.7.1
)
FetchContent_MakeAvailable(Catch2)

enable_testing()

add_executable(raytracer_tests
  tests/test_helpers.cpp
  tests/greeting_test.cpp
  tests/math/vector_test.cpp
  tests/image/image_test.cpp
  tests/io/png_saver_test.cpp
  tests/material/flat_shader_test.cpp
  tests/material/lambert_shader_test.cpp
  tests/light/light_test.cpp
  tests/render/trace_test.cpp
  tests/geometry/sphere_test.cpp
  tests/geometry/plane_test.cpp
  tests/scene/scene_test.cpp
  tests/colour/colour_test.cpp
  tests/geometry/ray_test.cpp
  tests/render/camera_test.cpp
)
target_include_directories(raytracer_tests PRIVATE tests)
target_link_libraries(raytracer_tests PRIVATE raytracer_core lodepng Catch2::Catch2WithMain)

list(APPEND CMAKE_MODULE_PATH ${catch2_SOURCE_DIR}/extras)
include(Catch)
catch_discover_tests(raytracer_tests)
