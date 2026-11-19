#include <catch2/catch_test_macros.hpp>

#include "colour/colour.h"
#include "geometry/hit_info.h"
#include "light/light.h"
#include "material/flat_shader.h"
#include "math/vector.h"
#include "test_helpers.h"

TEST_CASE("a flat shader gives its own colour, whatever the light", "[material]") {
    FlatShader shader(Colour(1, 0.5, 0));
    HitInfo hit{1, Vector(0, 0, 0), Vector(0, 1, 0), &shader};
    Light light(Vector(0, -10, 0), Colour(0, 0, 1));

    requireColoursEqual(shader.shade(hit, light), Colour(1, 0.5, 0));
}
