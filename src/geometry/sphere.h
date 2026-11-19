#pragma once

#include <memory>

#include "geometry/ray.h"
#include "material/material.h"
#include "math/vector.h"

class Sphere {
  public:
    Sphere(const Vector& center, double radius, std::shared_ptr<const Material> material);

    Vector center() const;
    double radius() const;
    const Material& material() const;

    bool isHitBy(const Ray& ray) const;

  private:
    Vector _center;
    double _radius;
    std::shared_ptr<const Material> _material;
};
