#pragma once

#include "material/material.h"
#include "math/vector.h"

// Where a ray meets a surface. material points to the shape's material, which outlives the hit.
struct HitInfo {
    Vector point;
    Vector normal;
    const Material* material;
};
