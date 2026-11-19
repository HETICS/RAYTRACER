#include <catch2/catch_test_macros.hpp>

#include <memory>
#include <optional>

#include "colour/colour.h"
#include "geometry/hit_info.h"
#include "geometry/plane.h"
#include "geometry/ray.h"
#include "geometry/sphere.h"
#include "light/light.h"
#include "material/flat_shader.h"
#include "math/vector.h"
#include "scene/scene.h"
#include "test_helpers.h"

static Light whiteLight() {
    return Light(Vector(0, 10, -10), Colour(1, 1, 1));
}

TEST_CASE("an empty scene is never hit", "[scene]") {
    Scene scene(whiteLight());

    REQUIRE_FALSE(scene.nearestHit(Ray(Vector(0, 0, -1), Vector(0, 0, 1))).has_value());
}

TEST_CASE("of two spheres on the ray, the nearer one is hit, whatever the order they were added in", "[scene]") {
    std::shared_ptr<const Material> red = std::make_shared<FlatShader>(Colour(1, 0, 0));
    std::shared_ptr<const Material> blue = std::make_shared<FlatShader>(Colour(0, 0, 1));
    Scene scene(whiteLight());
    scene.add(std::make_unique<Sphere>(Vector(0, 0, 30), 5, blue));
    scene.add(std::make_unique<Sphere>(Vector(0, 0, 9), 5, red));

    std::optional<HitInfo> hit = scene.nearestHit(Ray(Vector(0, 0, -1), Vector(0, 0, 1)));

    REQUIRE(hit.has_value());
    requireVectorsEqual(hit->point, Vector(0, 0, 4));
    REQUIRE(hit->material == red.get());
}

TEST_CASE("a ray that misses the ball goes on to the floor", "[scene]") {
    std::shared_ptr<const Material> red = std::make_shared<FlatShader>(Colour(1, 0, 0));
    std::shared_ptr<const Material> grey = std::make_shared<FlatShader>(Colour(0.8, 0.8, 0.8));
    Scene scene(whiteLight());
    scene.add(std::make_unique<Sphere>(Vector(0, 0, 9), 5, red));
    scene.add(std::make_unique<Plane>(Vector(0, -5, 0), Vector(0, 1, 0), grey));

    std::optional<HitInfo> hit = scene.nearestHit(Ray(Vector(0, 0, -1), Vector(0, -1, 1)));

    REQUIRE(hit.has_value());
    requireVectorsEqual(hit->point, Vector(0, -5, 4));
    REQUIRE(hit->material == grey.get());
}

TEST_CASE("a scene gives back its light", "[scene]") {
    Scene scene(Light(Vector(1, 2, 3), Colour(1, 0.5, 0)));

    requireVectorsEqual(scene.light().position(), Vector(1, 2, 3));
    requireColoursEqual(scene.light().colour(), Colour(1, 0.5, 0));
}
