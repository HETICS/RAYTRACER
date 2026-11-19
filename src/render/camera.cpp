#include "render/camera.h"

#include "render/trace.h"

Camera::Camera(const Vector& position, double screenWidth)
    : _position(position), _screenWidth(screenWidth) {}

Vector Camera::position() const { return _position; }
double Camera::screenWidth() const { return _screenWidth; }

Ray Camera::rayThroughPixel(unsigned int x, unsigned int y, unsigned int width, unsigned int height) const {
    double pixelSize = _screenWidth / width;
    double screenX = (x + 0.5 - width / 2.0) * pixelSize;
    double screenY = (height / 2.0 - y - 0.5) * pixelSize;
    return Ray(_position, Vector(screenX, screenY, 1));
}

Image Camera::render(const Sphere& sphere, unsigned int width, unsigned int height) const {
    Image image(width, height);
    for (unsigned int y = 0; y < height; y++) {
        for (unsigned int x = 0; x < width; x++) {
            image.setPixel(x, y, trace(rayThroughPixel(x, y, width, height), sphere));
        }
    }
    return image;
}
