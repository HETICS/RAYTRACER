# 6. One folder per concept

## Context

At first, all sources sat in `src/` and all tests in `tests/`. A ray tracer quickly has many classes (vectors, rays, shapes, materials, lights, camera, image, saver). The client's team must find its way in code it did not write (see the discovery report). In a flat folder, it is hard to see which classes belong together and which test covers which class.

Alternatives considered:
- **Keep a flat `src/`**: fine for three classes, not for twenty.
- **Folders by technical layer** (`core/`, `utils/`): the names say little about the domain.
- **One library per folder**: enforces boundaries, but too much CMake for now.

## Decision

Each concept has its own folder under `src/`, for example `src/math/vector.h` and `src/math/vector.cpp`. Today: `math`, `colour`, `geometry`, `material`, `light`, `scene`, `render`, `image`, `io`. Tests mirror the layout: `tests/math/vector_test.cpp`. Includes start from `src/`: `#include "math/vector.h"`.

## Status

Proposed

## Consequences

- A class and its tests are found from the name of their concept.
- An include line shows where the header lives.
- Moving a file means updating `CMakeLists.txt`, the includes and the test path.
- Someone has to decide which concept a class belongs to (for example, `Ray` lives in `geometry`).
- Nothing yet stops one folder from depending on another; namespaces and per-folder libraries are left for later.
