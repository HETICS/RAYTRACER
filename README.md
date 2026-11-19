# Raytracer

A student raytracer written in C++17. It renders a lit red ball on a grey floor to `image.png`, built with CMake and tested with Catch2.

## Development environment

The project builds inside a dev container, so every contributor gets the same compiler, CMake and Ninja on macOS, Linux or Windows.

Requirements on your machine: [Docker](https://docs.docker.com/get-docker/) (or OrbStack / Podman) and an editor that supports dev containers.

- **VS Code**: install the *Dev Containers* extension, open the folder, then run *Dev Containers: Reopen in Container*.
- **Zed**: open the folder and accept the *Open in Dev Container* prompt (or run `project: open dev container` from the command palette).
- **Command line**: `npx @devcontainers/cli up --workspace-folder .` then `npx @devcontainers/cli exec --workspace-folder . bash`.

The container is defined in [`.devcontainer/`](.devcontainer/). The first build downloads the image and takes a few minutes.

You can also build without the container if you have CMake 3.20+ and a C++17 compiler installed.

## Build and run

Shortcuts, like `npm run` scripts (see the [`Makefile`](Makefile)):

```bash
make build    # configure and build
make run      # build, then run
make test     # build, then run the tests
make clean    # delete build/ to start from scratch
```

The same steps by hand:

All commands run from the project root, inside the container.

```bash
cmake -B build -G Ninja      # configure: generates the build files in build/ (downloads Catch2 the first time)
cmake --build build          # compile the program and the tests
./build/raytracer            # run: writes image.png and prints its name
```

Run the configure step again only when `CMakeLists.txt` changes. To start from scratch, delete the `build/` folder.

## Tests

```bash
cmake --build build && ctest --test-dir build --output-on-failure
```

`ctest` runs every Catch2 test case and prints the details of any failure. You can also run the test executable directly with `./build/raytracer_tests`.

### Project layout

| Path | Content |
|---|---|
| `src/` | Code of the raytracer, one folder per concept (`src/math/`, ...), compiled into the `raytracer_core` library |
| `src/main.cpp` | Entry point of the `raytracer` program |
| `tests/` | Catch2 tests, in the same folders as the code they test, compiled into `raytracer_tests` |

The program and the tests both link `raytracer_core`, so the tests check the same code that the program runs.

### Working with TDD

1. **Red**: write a test in `tests/` that describes the behaviour you want, then build and run the tests. It must fail (or not compile).
2. **Green**: write the smallest amount of code in `src/` that makes the test pass.
3. **Refactor**: clean up the code and the test, and keep running the tests until they are all green.

A test looks like this:

```cpp
#include <catch2/catch_test_macros.hpp>

#include "math/vector.h"

TEST_CASE("length follows Pythagoras", "[vector]") {
    REQUIRE(Vector(3, -4, 0).length() == 5);
}
```

To add a new test file, create it in the matching folder of `tests/` and add it to `add_executable(raytracer_tests ...)` in `CMakeLists.txt`. To add a new source file, put it in its concept folder under `src/` and add it to `add_library(raytracer_core ...)`.

## Contributing

- [CONTRIBUTING.md](CONTRIBUTING.md): set up, commands, TDD and ADRs
- [CODE_OF_CONDUCT.md](CODE_OF_CONDUCT.md)
- [LICENSE](LICENSE): MIT
- CI: [`.github/workflows/ci.yml`](.github/workflows/ci.yml) builds and tests every pull request in the dev container
