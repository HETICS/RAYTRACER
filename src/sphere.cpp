#include "sphere.h"

Sphere::Sphere(const Vector& center, double radius) : _center(center), _radius(radius) {}

Vector Sphere::center() const { return _center; }
double Sphere::radius() const { return _radius; }
