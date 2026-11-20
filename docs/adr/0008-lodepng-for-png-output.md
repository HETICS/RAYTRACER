# 8. Save images as PNG with LodePNG

## Context

The renderer is a batch tool: scene in, image files out, one file per frame (see the discovery report). We need a standard image format that every tool can open, and a library that builds the same way in the dev container, the CI and on any machine, without system packages.

Alternatives considered:
- **PPM (writing the file by hand)**: no dependency at all, but few image viewers open it and files are large.
- **libpng + zlib**: the reference implementation, but system libraries to install and link.
- **stb_image_write**: a single header, easy to add, but it only writes: tests could not read the file back.
- **LodePNG**: one `.cpp` and one `.h`, no external dependency, encodes and decodes PNG.

## Decision

We use LodePNG, fetched with `FetchContent` at a pinned commit (`7b2893e`), since it has no releases and no CMake project, and built as a small static library. The code only sees an `ImageSaver` interface; `PngSaver` is its PNG implementation, which turns each `Colour` into 8-bit RGB and calls `lodepng::encode`. The tests use `lodepng::decode` to read the file back and check its size and pixels.

## Status

Accepted

## Consequences

- PNG is lossless and opens everywhere.
- No system library: the build works the same everywhere.
- Saving can be tested round trip without extra tools.
- Another format (EXR for film, for example) can be added as a new `ImageSaver` without touching the renderer.
- LodePNG is slower than libpng, which does not matter at our resolutions for now.
- Pinning a commit instead of a release means we update it by hand.
- PNG is 8 bits per channel: not enough for a film pipeline later.
