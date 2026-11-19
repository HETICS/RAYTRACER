#include "image/image.h"

Image::Image(unsigned int width, unsigned int height)
    : _width(width), _height(height), _pixels(width * height, Colour(0, 0, 0)) {}

unsigned int Image::width() const { return _width; }
unsigned int Image::height() const { return _height; }

Colour Image::pixel(unsigned int x, unsigned int y) const {
    return _pixels[index(x, y)];
}

void Image::setPixel(unsigned int x, unsigned int y, const Colour& colour) {
    _pixels[index(x, y)] = colour;
}

unsigned int Image::index(unsigned int x, unsigned int y) const {
    return y * _width + x;
}
