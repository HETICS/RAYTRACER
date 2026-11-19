#include "render/trace.h"

#include <optional>

#include "geometry/hit_info.h"

Colour trace(const Ray& ray, const Sphere& sphere) {
    std::optional<HitInfo> hit = sphere.hit(ray);
    if (!hit) {
        return Colour(0, 0, 0);
    }
    return hit->material->shade();
}
