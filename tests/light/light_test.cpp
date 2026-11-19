#include <catch2/catch_test_macros.hpp>

#include "colour/colour.h"
#include "light/light.h"
#include "math/vector.h"
#include "test_helpers.h"

TEST_CASE("a light gives back its position and colour", "[light]") {
    Light light(Vector(-10, 10, -10), Colour(1, 1, 0.5));

    requireVectorsEqual(light.position(), Vector(-10, 10, -10));
    requireColoursEqual(light.colour(), Colour(1, 1, 0.5));
}
