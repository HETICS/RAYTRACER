# 2. Build with CMake and run tests with CTest

## Context

The studio's own team must maintain the renderer for years, and partner studios that already write C++ must be able to contribute (see the discovery report). The build system has to work on every platform, fetch our few dependencies, and run the tests.

Alternatives considered:
- **Hand-written Makefiles**: simple at first, but platform-specific and hard to maintain as the project grows.
- **Meson**: cleaner syntax, but less known in C++ studios.
- **Bazel**: powerful, but far too heavy for a project of this size.

## Decision

We use CMake (3.20 or newer) with the Ninja generator. The code is compiled into a `raytracer_core` library, linked by both the `raytracer` program and the `raytracer_tests` executable, so the tests exercise the real code. Dependencies are fetched with `FetchContent` at a pinned version or commit. Tests are run with CTest.

## Status

Accepted

## Consequences

- CMake is the de facto standard for C++ projects: studio developers and contributors are likely to know it already.
- CTest ships with CMake, so running the tests needs no extra tool.
- Pinned dependencies make builds reproducible.
- CMake's syntax is verbose and hard to read for newcomers.
- The first configure needs internet access to download the dependencies.
- Every new source file must be added to `CMakeLists.txt` by hand.
