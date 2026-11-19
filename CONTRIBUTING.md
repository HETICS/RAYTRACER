# Contributing

Thank you for your interest in this ray tracer. This page explains how to build it, test it and propose a change.

## Set up the dev container

The project builds inside a dev container, so everyone uses the same compiler and tools.

1. Install [Docker](https://docs.docker.com/get-docker/) (or OrbStack / Podman) and an editor that supports dev containers (VS Code, Zed).
2. Clone the repository and open it in its dev container (*Dev Containers: Reopen in Container* in VS Code).

The first build downloads the image and the test framework, so it needs internet access and takes a few minutes.

## Build, run and test

```sh
make build    # configure and build
make run      # build, then run
make test     # build, then run the tests
make clean    # delete build/
```

## Work test first

We use test-driven development:

1. **Red**: write a test in `tests/` that describes the behaviour you want. Run `make test` and see it fail, for the right reason.
2. **Green**: write the smallest amount of code in `src/` that makes it pass.
3. **Refactor**: clean up, and keep `make test` green.

Expected values in tests come from the maths or the specification, not from running the code.

## Architecture decisions

Our decisions are recorded in [`docs/adr/`](docs/adr/). Read them before changing the build, the tools or the test setup.

- A change must not go against an accepted ADR.
- To change a decision, add a new ADR with status *Proposed* in your pull request. The maintainers decide whether to accept it.

## Submit a change

1. Create a branch from `main`.
2. Make small commits that say why.
3. Run `make test` in the dev container.
4. Open a pull request and fill in the template. The CI builds the project and runs the tests in the same dev container.

Please follow our [Code of Conduct](CODE_OF_CONDUCT.md).
