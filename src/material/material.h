#pragma once

#include "colour/colour.h"

struct HitInfo;
class Light;

// How a surface turns light into a colour. Each shading technique is one implementation.
class Material {
  public:
    virtual ~Material() = default;

    virtual Colour shade(const HitInfo& hit, const Light& light) const = 0;
};
