#include "geometry/sphere.h"

#include <cmath>
#include <utility>

Sphere::Sphere(const Vector& center, double radius, std::shared_ptr<const Material> material)
    : _center(center), _radius(radius), _material(std::move(material)) {}

Vector Sphere::center() const { return _center; }
double Sphere::radius() const { return _radius; }
const Material& Sphere::material() const { return *_material; }

std::optional<HitInfo> Sphere::hit(const Ray& ray) const {
    Vector D = ray.direction();
    Vector L = ray.origin() - _center;
    double a = D.dot(D);
    double b = 2.0 * D.dot(L);
    double c = L.dot(L) - _radius * _radius;
    double discriminant = b * b - 4.0 * a * c;
    if (discriminant < 0.0) {
        return std::nullopt;
    }

    double t1 = (-b - std::sqrt(discriminant)) / (2.0 * a);
    double t2 = (-b + std::sqrt(discriminant)) / (2.0 * a);
    double t;
    if (t1 > 0.0) {
        t = t1;
    } else if (t2 > 0.0) {
        t = t2;
    } else {
        return std::nullopt;
    }

    Vector point = ray.at(t);
    Vector normal = (point - _center).normalised();
    return HitInfo{point, normal, _material.get()};
}
