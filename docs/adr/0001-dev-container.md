# 1. Build inside a dev container

## Context

The renderer must give the same output for the same input, and the client's last renderer failed partly because nobody could reproduce or explain its anomalies (see the discovery report). Contributors work on macOS, Linux and Windows, and partner studios will contribute later. If everyone installs their own compiler and CMake, builds and test results can silently differ from one machine to the next.

Alternatives considered:
- **Local install on each machine**: nothing to learn, but compiler and CMake versions drift.
- **A plain Docker image with scripts**: reproducible, but no editor integration.
- **Cloud environments (GitHub Codespaces)**: same container format, but needs a network connection and a paid plan for heavy use.

## Decision

We build, run and test inside a dev container defined in `.devcontainer/devcontainer.json`, based on the `mcr.microsoft.com/devcontainers/cpp:1-debian-12` image. VS Code and Zed open it directly; the `devcontainers` CLI works from the command line. The CI uses the same container (see [ADR 5](0005-github-actions-ci.md)).

## Status

Proposed

## Consequences

- Every contributor, and the CI, uses the same compiler and tools, whatever their operating system.
- A new contributor only needs Docker and a compatible editor to start.
- Docker is a heavy dependency, especially on Windows, and the first start downloads the image.
- The image tag `1-debian-12` follows minor updates: the toolchain can change without a commit. Pinning a digest would fix it, at the cost of manual updates.
- Building without the container is still possible, but nothing guarantees the same result.
