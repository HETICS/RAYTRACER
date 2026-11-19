#pragma once

#include <memory>
#include <optional>
#include <vector>

#include "geometry/hit_info.h"
#include "geometry/ray.h"
#include "geometry/shape.h"
#include "light/light.h"

class Scene {
  public:
    explicit Scene(const Light& light);

    void add(std::unique_ptr<Shape> shape);

    Light light() const;
    std::optional<HitInfo> nearestHit(const Ray& ray) const;

  private:
    Light _light;
    std::vector<std::unique_ptr<Shape>> _shapes;
};
