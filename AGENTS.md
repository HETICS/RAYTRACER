# AGENTS.md

## Commands

Run from the repository root, inside the dev container.

```sh
make build    # configure and build
make run      # build, then run
make test     # build, then run the tests
make clean    # delete build/
```

Without make:

```sh
cmake -B build -G Ninja                         # configure (first time, or after CMakeLists.txt changes)
cmake --build build                             # build
./build/raytracer                               # run
ctest --test-dir build --output-on-failure      # test (build first: CTest does not compile)
```

## Architecture decisions

Our architecture decisions are in `docs/adr/`. Read them before changing the build, the tools or the test setup.

- Never go against an accepted ADR. To change a decision, write a new ADR with status Proposed and ask me.
- Never set an ADR to Accepted.

## Contributing

See [CONTRIBUTING.md](CONTRIBUTING.md). The CI in `.github/workflows/ci.yml` runs `make test` in the dev container on every pull request.
