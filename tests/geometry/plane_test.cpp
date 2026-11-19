#include <catch2/catch_test_macros.hpp>

#include <memory>
#include <optional>

#include "colour/colour.h"
#include "geometry/hit_info.h"
#include "geometry/plane.h"
#include "geometry/ray.h"
#include "material/flat_shader.h"
#include "math/vector.h"
#include "test_helpers.h"

static std::shared_ptr<const Material> grey() {
    return std::make_shared<FlatShader>(Colour(0.8, 0.8, 0.8));
}

// The floor y = -5, seen from an eye at (0, 0, -1).
TEST_CASE("a ray going down hits the floor where t = n.(P - O) / n.D", "[plane]") {
    Plane floor(Vector(0, -5, 0), Vector(0, 1, 0), grey());
    Ray ray(Vector(0, 0, -1), Vector(0, -1, 1));

    std::optional<HitInfo> hit = floor.hit(ray);

    REQUIRE(hit.has_value());
    requireVectorsEqual(hit->point, Vector(0, -5, 4));
    requireVectorsEqual(hit->normal, Vector(0, 1, 0));
}

TEST_CASE("a ray parallel to the floor misses it", "[plane]") {
    Plane floor(Vector(0, -5, 0), Vector(0, 1, 0), grey());

    REQUIRE_FALSE(floor.hit(Ray(Vector(0, 0, -1), Vector(0, 0, 1))).has_value());
}

TEST_CASE("a ray going up misses the floor below it", "[plane]") {
    Plane floor(Vector(0, -5, 0), Vector(0, 1, 0), grey());

    REQUIRE_FALSE(floor.hit(Ray(Vector(0, 0, -1), Vector(0, 1, 1))).has_value());
}

TEST_CASE("the plane's normal is given back with length 1", "[plane]") {
    Plane floor(Vector(0, -5, 0), Vector(0, 2, 0), grey());

    std::optional<HitInfo> hit = floor.hit(Ray(Vector(0, 0, -1), Vector(0, -1, 1)));

    REQUIRE(hit.has_value());
    requireVectorsEqual(hit->normal, Vector(0, 1, 0));
}
