#pragma once

#include "colour.h"
#include "math/vector.h"
#include "ray.h"

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
