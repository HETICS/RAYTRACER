# 10. A shape has a material

## Context

Each surface needs two things: its geometry (where a ray hits it, and the normal there) and its appearance (how it turns light into a colour). The client changes its requirements with every film and wants to add new shapes and effects without touching the core of the renderer (see the discovery report). We render a sphere and a plane today, with a flat and a Lambert shader, and more of both will come.

Alternatives considered:
- **Inheritance** (`RedSphere`, `LambertPlane`...): each combination is a class, so N shapes and M materials give N × M classes.
- **A colour field on each shape, shaded in `trace`**: simple, but every new shading technique means changing `trace`.
- **Composition**: each shape holds a material; the shape does the geometry, the material does the shading.

## Decision

We choose composition:
- `Shape` is an interface with `hit(ray)`, returning the nearest hit in front of the ray, or nothing. `Sphere` and `Plane` implement it.
- `Material` is an interface with `shade(hit, light)`. `FlatShader` and `LambertShader` implement it.
- Each shape receives a `std::shared_ptr<const Material>` in its constructor, so several shapes can share the same material.
- `hit` returns a `HitInfo` with `t`, the point, the unit normal and a pointer to the shape's material.
- `trace` asks the scene for the nearest hit and lets that hit's material shade it; with no hit, the pixel is black.

## Status

Accepted

## Consequences

- A new shape or a new material is one new class: N + M classes instead of N × M.
- Geometry and shading are tested separately.
- Shapes and materials can be combined freely when building a scene.
- `HitInfo` holds a raw pointer to the material: it is only valid while the shape that produced it exists. This is fine because hits are used immediately in `trace`.
- `shared_ptr` adds a small cost and ownership to explain to newcomers to C++.
- A material only sees one light and the hit: shadows and reflections will need more information, and a new decision.
