#pragma once

#include "math/vector.h"

class Sphere {
  public:
    Sphere(const Vector& center, double radius);

    Vector center() const;
    double radius() const;

  private:
    Vector _center;
    double _radius;
};
