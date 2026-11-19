#pragma once

#include "material/material.h"
#include "math/vector.h"

// Where a ray meets a surface: how far along the ray, the point, the unit normal and the material.
// material points to the shape's material, which outlives the hit.
struct HitInfo {
    double t;
    Vector point;
    Vector normal;
    const Material* material;
};
