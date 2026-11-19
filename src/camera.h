#pragma once

#include "math/vector.h"

// For now the camera always looks along +z.
class Camera {
  public:
    explicit Camera(const Vector& position);

    Vector position() const;

  private:
    Vector _position;
};
