#pragma once

#include "colour/colour.h"
#include "material/material.h"

class FlatShader : public Material {
  public:
    explicit FlatShader(const Colour& colour);

    Colour shade() const override;

  private:
    Colour _colour;
};
