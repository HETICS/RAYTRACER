#pragma once

#include "colour/colour.h"
#include "material/material.h"

// Lambert's law: the more directly the light falls on the surface, the brighter it is.
class LambertShader : public Material {
  public:
    explicit LambertShader(const Colour& colour);

    Colour shade(const HitInfo& hit, const Light& light) const override;

  private:
    Colour _colour;
};
