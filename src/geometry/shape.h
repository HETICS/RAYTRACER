#pragma once

#include <optional>

#include "geometry/hit_info.h"
#include "geometry/ray.h"

class Shape {
  public:
    virtual ~Shape() = default;

    // Every shape gives its nearest hit in front of the ray's origin (t > 0), with a unit normal, or nothing.
    virtual std::optional<HitInfo> hit(const Ray& ray) const = 0;
};
