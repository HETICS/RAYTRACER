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

TEST_CASE("a + b sums each component", "[vector]") {
    requireVectorsEqual(Vector(1, 2, 3) + Vector(4, 5, 6), Vector(5, 7, 9));
}

TEST_CASE("a - b takes away each component", "[vector]") {
    requireVectorsEqual(Vector(-1, 4, 0) - Vector(-5, 2, 1), Vector(4, 2, -1));
}

TEST_CASE("t * v scales each component", "[vector]") {
    requireVectorsEqual(2.0 * Vector(3, -4, 1), Vector(6, -8, 2));
}

TEST_CASE("v * t scales each component, like t * v", "[vector]") {
    requireVectorsEqual(Vector(3, -4, 1) * 2.0, Vector(6, -8, 2));
}

TEST_CASE("O + t * D gives the point on the ray at t", "[vector]") {
    Vector O(0, 8, 0);
    Vector D(3, -4, 0);
    double t = 2;

    requireVectorsEqual(O + t * D, Vector(6, 0, 0));
}
