#include <catch2/catch_test_macros.hpp>

#include <memory>

#include "colour/colour.h"
#include "geometry/plane.h"
#include "geometry/ray.h"
#include "geometry/sphere.h"
#include "light/light.h"
#include "material/flat_shader.h"
#include "material/lambert_shader.h"
#include "math/vector.h"
#include "render/trace.h"
#include "scene/scene.h"
#include "test_helpers.h"

TEST_CASE("trace gives the colour of the nearest surface's material", "[trace]") {
    Scene scene(Light(Vector(0, 0, -10), Colour(1, 1, 1)));
    scene.add(std::make_unique<Sphere>(Vector(0, 0, 9), 5, std::make_shared<FlatShader>(Colour(1, 0, 0))));

    requireColoursEqual(trace(Ray(Vector(0, 0, -1), Vector(0, 0, 1)), scene), Colour(1, 0, 0));
}

TEST_CASE("trace gives black when the ray hits nothing", "[trace]") {
    Scene scene(Light(Vector(0, 0, -10), Colour(1, 1, 1)));
    scene.add(std::make_unique<Sphere>(Vector(6, 0, 9), 5, std::make_shared<FlatShader>(Colour(1, 0, 0))));

    requireColoursEqual(trace(Ray(Vector(0, 0, -1), Vector(0, 0, 1)), scene), Colour(0, 0, 0));
}

TEST_CASE("trace shades with the scene's light", "[trace]") {
    // The floor's normal is (0, 1, 0); the light straight above the hit point gives full brightness.
    Scene scene(Light(Vector(0, 5, 4), Colour(1, 1, 1)));
    scene.add(std::make_unique<Plane>(Vector(0, -5, 0), Vector(0, 1, 0),
                                      std::make_shared<LambertShader>(Colour(0.8, 0.8, 0.8))));

    requireColoursEqual(trace(Ray(Vector(0, 0, -1), Vector(0, -1, 1)), scene), Colour(0.8, 0.8, 0.8));
}
