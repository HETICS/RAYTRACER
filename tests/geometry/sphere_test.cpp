#include <catch2/catch_test_macros.hpp>

#include <memory>
#include <optional>

#include "colour/colour.h"
#include "geometry/hit_info.h"
#include "geometry/ray.h"
#include "geometry/sphere.h"
#include "material/flat_shader.h"
#include "math/vector.h"
#include "test_helpers.h"

static std::shared_ptr<const Material> red() {
    return std::make_shared<FlatShader>(Colour(1, 0, 0));
}

TEST_CASE("a ray through the centre of a sphere hits it on the near side", "[sphere]") {
    Ray ray(Vector(0, 0, -1), Vector(0, 0, 1));
    Sphere sphere(Vector(0, 0, 9), 5, red());

    std::optional<HitInfo> hit = sphere.hit(ray);

    REQUIRE(hit.has_value());
    requireVectorsEqual(hit->point, Vector(0, 0, 4));
}

TEST_CASE("the normal points from the centre to the hit point, with length 1", "[sphere]") {
    Ray ray(Vector(0, 0, -1), Vector(0, 0, 1));
    Sphere sphere(Vector(0, 0, 9), 5, red());

    std::optional<HitInfo> hit = sphere.hit(ray);

    REQUIRE(hit.has_value());
    requireVectorsEqual(hit->normal, Vector(0, 0, -1));
}

TEST_CASE("a hit carries the sphere's material", "[sphere]") {
    std::shared_ptr<const Material> material = std::make_shared<FlatShader>(Colour(1, 0.5, 0));
    Sphere sphere(Vector(0, 0, 9), 5, material);

    std::optional<HitInfo> hit = sphere.hit(Ray(Vector(0, 0, -1), Vector(0, 0, 1)));

    REQUIRE(hit.has_value());
    REQUIRE(hit->material == material.get());
}

TEST_CASE("a ray through the side of a sphere hits it", "[sphere]") {
    Ray ray(Vector(0, 0, -1), Vector(0, 0, 1));
    Sphere sphere(Vector(3, 0, 9), 5, red());

    REQUIRE(sphere.hit(ray).has_value());
}

TEST_CASE("a ray that passes beside a sphere misses it", "[sphere]") {
    Ray ray(Vector(0, 0, -1), Vector(0, 0, 1));
    Sphere sphere(Vector(6, 0, 9), 5, red());

    REQUIRE_FALSE(sphere.hit(ray).has_value());
}

TEST_CASE("a sphere behind the ray's origin is missed", "[sphere]") {
    Ray ray(Vector(0, 0, -1), Vector(0, 0, 1));
    Sphere sphere(Vector(0, 0, -11), 5, red());

    REQUIRE_FALSE(sphere.hit(ray).has_value());
}
