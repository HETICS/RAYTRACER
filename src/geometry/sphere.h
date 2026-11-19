#pragma once

#include "colour/colour.h"
#include "math/vector.h"
#include "geometry/ray.h"

class Sphere {
  public:
    Sphere(const Vector& center, double radius, const Colour& colour);

    Vector center() const;
    double radius() const;
    Colour colour() const;

    bool isHitBy(const Ray& ray) const;

  private:
    Vector _center;
    double _radius;
    Colour _colour;
};
