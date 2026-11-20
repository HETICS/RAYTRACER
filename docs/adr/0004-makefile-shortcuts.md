# 4. Short commands with a Makefile

## Context

The CMake and CTest commands are long and easy to forget (`cmake -B build -G Ninja`, `cmake --build build`, `ctest --test-dir build --output-on-failure`). We wanted something like `npm run build` or `npm run test`, the same for every contributor and for the CI.

Alternatives considered:
- **Typing the commands by hand**: no extra file, but error-prone.
- **Shell scripts**: work, but one file per command and not portable to Windows outside the container.
- **just**: a nicer syntax, but another tool to install in the container.
- **CMake presets**: standard, but still long commands.

## Decision

A small `Makefile` at the root provides `make build`, `make run`, `make test` and `make clean`. It only calls CMake, CTest and the program: CMake stays the build system ([ADR 2](0002-cmake.md)).

## Status

Accepted

## Consequences

- Four short commands to remember, documented in the README, `AGENTS.md` and `CONTRIBUTING.md`.
- The CI runs exactly the same `make test` as contributors.
- `make` is already in the dev container: nothing to install.
- Two layers (Make calling CMake) can confuse newcomers about which one actually builds.
- Outside the container, Windows users do not have `make` by default.
