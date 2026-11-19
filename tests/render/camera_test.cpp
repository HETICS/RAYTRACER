#include <catch2/catch_test_macros.hpp>

#include "geometry/ray.h"
#include "math/vector.h"
#include "render/camera.h"
#include "test_helpers.h"

TEST_CASE("in a 1 by 1 image, the ray starts at the camera and looks along +z", "[camera]") {
    Camera camera(Vector(1, 2, -1), 2);

    Ray ray = camera.rayThroughPixel(0, 0, 1, 1);

    requireVectorsEqual(ray.origin(), Vector(1, 2, -1));
    requireVectorsEqual(ray.direction(), Vector(0, 0, 1));
}

// The board's grid: a screen 5 wide, an image of 5 columns and 3 rows, so one pixel is 1 across.
TEST_CASE("the centre pixel's ray goes straight ahead", "[camera]") {
    Camera camera(Vector(0, 0, -1), 5);

    Ray ray = camera.rayThroughPixel(2, 1, 5, 3);

    requireVectorsEqual(ray.origin(), Vector(0, 0, -1));
    requireVectorsEqual(ray.direction(), Vector(0, 0, 1));
}

TEST_CASE("the top-right pixel's ray goes right and up", "[camera]") {
    Camera camera(Vector(0, 0, -1), 5);

    Ray ray = camera.rayThroughPixel(4, 0, 5, 3);

    requireVectorsEqual(ray.direction(), Vector(2, 1, 1));
}

TEST_CASE("the bottom-left pixel's ray goes left and down", "[camera]") {
    Camera camera(Vector(0, 0, -1), 5);

    Ray ray = camera.rayThroughPixel(0, 2, 5, 3);

    requireVectorsEqual(ray.direction(), Vector(-2, -1, 1));
}
