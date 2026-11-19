#include "scene/scene.h"

#include <utility>

Scene::Scene(const Light& light) : _light(light) {}

void Scene::add(std::unique_ptr<Shape> shape) {
    _shapes.push_back(std::move(shape));
}

Light Scene::light() const { return _light; }

std::optional<HitInfo> Scene::nearestHit(const Ray& ray) const {
    std::optional<HitInfo> nearest;
    for (const std::unique_ptr<Shape>& shape : _shapes) {
        std::optional<HitInfo> hit = shape->hit(ray);
        if (hit && (!nearest || hit->t < nearest->t)) {
            nearest = hit;
        }
    }
    return nearest;
}
