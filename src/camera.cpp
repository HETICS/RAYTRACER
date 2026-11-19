#include "camera.h"

Camera::Camera(const Vector& position) : _position(position) {}

Vector Camera::position() const { return _position; }
