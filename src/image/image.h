#pragma once

#include <vector>

#include "colour/colour.h"

// Pixels are counted from the top left corner, (0, 0).
class Image {
  public:
    Image(unsigned int width, unsigned int height);

    unsigned int width() const;
    unsigned int height() const;

    Colour pixel(unsigned int x, unsigned int y) const;
    void setPixel(unsigned int x, unsigned int y, const Colour& colour);

  private:
    unsigned int index(unsigned int x, unsigned int y) const;

    unsigned int _width;
    unsigned int _height;
    std::vector<Colour> _pixels;
};
