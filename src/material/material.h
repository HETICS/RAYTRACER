#pragma once

#include "colour/colour.h"

// How a surface turns into a colour. Each shading technique is one implementation.
class Material {
  public:
    virtual ~Material() = default;

    virtual Colour shade() const = 0;
};
