# 9. Coordinate system and camera

## Context

The camera, the shapes, the light and the tests must all agree on which way is up, which way the camera looks, and where pixel (0, 0) is. Without one written convention, a test written by one person and code written by another can disagree, and the image comes out flipped or mirrored.

Alternatives considered:
- **Right-handed, camera looking towards -z** (OpenGL convention): common in graphics, but depth values are negative in front of the camera.
- **Pixels counted from the bottom left**: matches maths, but not image files, which start at the top left.

## Decision

- **World**: x to the right, y up, z forward (away from the viewer, into the scene).
- **Camera**: a pinhole at `position`, looking along +z. The screen is a rectangle at distance 1 in front of it, `screenWidth` wide, its height following the image's aspect ratio, cut into square pixels.
- **Pixels**: counted from the top left corner of the image, x to the right, y down. The ray goes through the centre of the pixel: `screenX = (x + 0.5 - width / 2) * pixelSize`, `screenY = (height / 2 - y - 0.5) * pixelSize`.
- **Ray directions** from the camera are not normalised; shapes must not assume a unit direction.

## Status

Accepted

## Consequences

- Objects in front of the camera have a positive z: the main scene places the sphere at z = 9.
- Image rows map directly to PNG rows, top to bottom, with no flip when saving.
- Expected values in tests can be worked out by hand from these rules.
- The camera cannot rotate yet: looking in another direction will need a new decision.
- Since directions are not unit vectors, `t` is not a distance; code that needs a distance must normalise.
