#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>

#include "math/vector.h"

using Catch::Matchers::WithinAbs;

const double tolerance = 1e-9;

static void requireVectorsEqual(const Vector& actual, const Vector& expected) {
    REQUIRE_THAT(actual.x(), WithinAbs(expected.x(), tolerance));
    REQUIRE_THAT(actual.y(), WithinAbs(expected.y(), tolerance));
    REQUIRE_THAT(actual.z(), WithinAbs(expected.z(), tolerance));
}

TEST_CASE("add sums each component", "[vector]") {
    requireVectorsEqual(Vector(1, 2, 3).add(Vector(4, 5, 6)), Vector(5, 7, 9));
}

TEST_CASE("subtract takes away each component", "[vector]") {
    requireVectorsEqual(Vector(-1, 4, 0).subtract(Vector(-5, 2, 1)), Vector(4, 2, -1));
}
