#include "render/camera.h"

Camera::Camera(const Vector& position) : _position(position) {}

Vector Camera::position() const { return _position; }

Ray Camera::rayThroughCentre() const {
    return Ray(_position, Vector(0, 0, 1));
}
