#pragma once

#include "math/vector.h"
#include "geometry/ray.h"

// For now the camera always looks along +z.
class Camera {
  public:
    explicit Camera(const Vector& position);

    Vector position() const;
    Ray rayThroughCentre() const;

  private:
    Vector _position;
};
