#pragma once

#include <memory>
#include <optional>

#include "geometry/hit_info.h"
#include "geometry/ray.h"
#include "geometry/shape.h"
#include "material/material.h"
#include "math/vector.h"

class Sphere : public Shape {
  public:
    Sphere(const Vector& center, double radius, std::shared_ptr<const Material> material);

    Vector center() const;
    double radius() const;
    const Material& material() const;

    std::optional<HitInfo> hit(const Ray& ray) const override;

  private:
    Vector _center;
    double _radius;
    std::shared_ptr<const Material> _material;
};
