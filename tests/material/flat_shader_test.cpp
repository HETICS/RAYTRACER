#include <catch2/catch_test_macros.hpp>

#include "colour/colour.h"
#include "material/flat_shader.h"
#include "test_helpers.h"

TEST_CASE("a flat shader always gives its own colour", "[material]") {
    FlatShader shader(Colour(1, 0.5, 0));

    requireColoursEqual(shader.shade(), Colour(1, 0.5, 0));
}
