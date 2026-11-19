#include <catch2/catch_test_macros.hpp>

#include <cmath>

#include "colour/colour.h"
#include "geometry/hit_info.h"
#include "light/light.h"
#include "material/lambert_shader.h"
#include "math/vector.h"
#include "test_helpers.h"

static const Colour WHITE(1, 1, 1);

TEST_CASE("a surface facing the light gets its full colour", "[material]") {
    LambertShader shader(Colour(1, 0, 0));
    HitInfo hit{1, Vector(0, 0, 0), Vector(0, 1, 0), &shader};
    Light light(Vector(0, 10, 0), WHITE);

    requireColoursEqual(shader.shade(hit, light), Colour(1, 0, 0));
}

TEST_CASE("light at 60 degrees from the normal gives half the colour", "[material]") {
    LambertShader shader(Colour(1, 0, 0));
    HitInfo hit{1, Vector(0, 0, 0), Vector(0, 1, 0), &shader};
    Light light(Vector(std::sqrt(3.0), 1, 0), WHITE);

    requireColoursEqual(shader.shade(hit, light), Colour(0.5, 0, 0));
}

TEST_CASE("a surface facing away from the light is black", "[material]") {
    LambertShader shader(Colour(1, 0, 0));
    HitInfo hit{1, Vector(0, 0, 0), Vector(0, 1, 0), &shader};
    Light light(Vector(0, -10, 0), WHITE);

    requireColoursEqual(shader.shade(hit, light), Colour(0, 0, 0));
}

TEST_CASE("the light's colour tints the surface", "[material]") {
    LambertShader shader(Colour(1, 1, 1));
    HitInfo hit{1, Vector(0, 0, 0), Vector(0, 1, 0), &shader};
    Light light(Vector(0, 10, 0), Colour(1, 0.5, 0));

    requireColoursEqual(shader.shade(hit, light), Colour(1, 0.5, 0));
}
