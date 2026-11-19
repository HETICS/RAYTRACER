#pragma once

#include "geometry/ray.h"
#include "geometry/sphere.h"
#include "image/image.h"
#include "math/vector.h"

// The camera looks along +z, at a screen 1 in front of it.
class Camera {
  public:
    Camera(const Vector& position, double screenWidth);

    Vector position() const;
    double screenWidth() const;

    Ray rayThroughPixel(unsigned int x, unsigned int y, unsigned int width, unsigned int height) const;
    Image render(const Sphere& sphere, unsigned int width, unsigned int height) const;

  private:
    Vector _position;
    double _screenWidth;
};
