#pragma once

#include <memory>
#include <optional>

#include "geometry/hit_info.h"
#include "geometry/ray.h"
#include "geometry/shape.h"
#include "material/material.h"
#include "math/vector.h"

// An infinite flat surface through point, facing normal.
class Plane : public Shape {
  public:
    Plane(const Vector& point, const Vector& normal, std::shared_ptr<const Material> material);

    std::optional<HitInfo> hit(const Ray& ray) const override;

  private:
    Vector _point;
    Vector _normal;
    std::shared_ptr<const Material> _material;
};
