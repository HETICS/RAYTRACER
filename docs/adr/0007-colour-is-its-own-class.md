# 7. Colour is its own class, not a Vector

## Context

A colour (r, g, b) and a 3D vector (x, y, z) both hold three numbers, so it is tempting to reuse `Vector` for colours, as some tutorials do. But they mean different things: adding a point to a colour, or taking the dot product of two colours, makes no sense. The client wants anomalies to be traceable (see the discovery report): mixing the two types would let this kind of mistake compile silently.

Alternatives considered:
- **Reuse `Vector` for colours** (a type alias): less code, but the compiler cannot catch a colour used as a position.
- **A shared base class or template for three-component types**: avoids duplication, but more advanced C++ than we need now.

## Decision

`Colour` is a separate class in `src/colour/`, with `r()`, `g()` and `b()` in the range 0 to 1. It has no conversion to or from `Vector`. Operations are added to `Colour` only when a feature needs them.

## Status

Proposed

## Consequences

- The compiler refuses to mix a colour and a vector by mistake.
- The code reads in the domain's words: `colour.r()` rather than `vector.x()`.
- Some code is duplicated (constructor, accessors, and later arithmetic such as multiplying by a factor).
- Values outside 0 to 1 are not prevented by the type; the image saver must handle them.
