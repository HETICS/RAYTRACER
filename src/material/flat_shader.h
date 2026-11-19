#pragma once

#include "colour/colour.h"
#include "material/material.h"

// Ignores the light: the same colour everywhere.
class FlatShader : public Material {
  public:
    explicit FlatShader(const Colour& colour);

    Colour shade(const HitInfo& hit, const Light& light) const override;

  private:
    Colour _colour;
};
