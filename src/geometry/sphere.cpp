#include "geometry/sphere.h"

#include <cmath>

Sphere::Sphere(const Vector& center, double radius, const Colour& colour)
    : _center(center), _radius(radius), _colour(colour) {}

Vector Sphere::center() const { return _center; }
double Sphere::radius() const { return _radius; }
Colour Sphere::colour() const { return _colour; }

bool Sphere::isHitBy(const Ray& ray) const {
    Vector D = ray.direction();
    Vector L = ray.origin() - _center;
    double a = D.dot(D);
    double b = 2.0 * D.dot(L);
    double c = L.dot(L) - _radius * _radius;
    double discriminant = b * b - 4.0 * a * c;
    if (discriminant < 0.0) {
        return false;
    }

    double t1 = (-b - std::sqrt(discriminant)) / (2.0 * a);
    double t2 = (-b + std::sqrt(discriminant)) / (2.0 * a);
    return t1 > 0.0 || t2 > 0.0;
}
