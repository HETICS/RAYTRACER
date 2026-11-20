# 5. Continuous integration with GitHub Actions in the dev container

## Context

Partner studios will propose changes, and the studio keeps the final say on what is accepted (see the discovery report). Reviewers need proof that a pull request builds and passes the tests, in the same environment as local work ([ADR 1](0001-dev-container.md)). The repository is on GitHub.

Alternatives considered:
- **No CI**: reviewers run the tests by hand, which is slow and easy to forget.
- **Another CI service (GitLab CI, CircleCI)**: works, but adds a second service for a project already on GitHub.
- **GitHub Actions with a toolchain installed on the runner**: faster, but the environment differs from the dev container.

## Decision

The workflow `.github/workflows/ci.yml` runs on every pull request and every push to `main`. It uses the `devcontainers/ci` action to start the dev container and run `make test` inside it.

## Status

Accepted

## Consequences

- Every pull request is built and tested with the same toolchain as local work.
- The CI runs the same command as contributors, so a failure can be reproduced locally.
- The container is built on every run, which makes the CI slower. A cache can be added later.
- We depend on GitHub and on the third-party `devcontainers/ci` action, pinned to `v0.3`, not to a commit.
