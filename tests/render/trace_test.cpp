#include <catch2/catch_test_macros.hpp>

#include <memory>

#include "colour/colour.h"
#include "geometry/ray.h"
#include "geometry/sphere.h"
#include "material/flat_shader.h"
#include "light/light.h"
#include "math/vector.h"
#include "render/trace.h"
#include "test_helpers.h"

TEST_CASE("trace gives the sphere's colour when the ray hits it", "[trace]") {
    Ray ray(Vector(0, 0, -1), Vector(0, 0, 1));
    Sphere sphere(Vector(0, 0, 9), 5, std::make_shared<FlatShader>(Colour(1, 0, 0)));

    requireColoursEqual(trace(ray, sphere, Light(Vector(0, 0, -10), Colour(1, 1, 1))), Colour(1, 0, 0));
}

TEST_CASE("trace gives black when the ray misses the sphere", "[trace]") {
    Ray ray(Vector(0, 0, -1), Vector(0, 0, 1));
    Sphere sphere(Vector(6, 0, 9), 5, std::make_shared<FlatShader>(Colour(1, 0, 0)));

    requireColoursEqual(trace(ray, sphere, Light(Vector(0, 0, -10), Colour(1, 1, 1))), Colour(0, 0, 0));
}
