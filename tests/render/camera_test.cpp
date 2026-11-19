#include <catch2/catch_test_macros.hpp>

#include <string>
#include <vector>

#include "colour/colour.h"
#include "geometry/ray.h"
#include "geometry/sphere.h"
#include "image/image.h"
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

// A screen 2 wide over 512 columns: one pixel is 2 / 512 = 0.00390625 across.
TEST_CASE("with smaller pixels, the corner rays go through the corner pixels' centres", "[camera]") {
    Camera camera(Vector(0, 0, -1), 2);

    requireVectorsEqual(camera.rayThroughPixel(0, 0, 512, 256).direction(),
                        Vector(-0.998046875, 0.498046875, 1));
    requireVectorsEqual(camera.rayThroughPixel(511, 255, 512, 256).direction(),
                        Vector(0.998046875, -0.498046875, 1));
    requireVectorsEqual(camera.rayThroughPixel(256, 128, 512, 256).direction(),
                        Vector(0.001953125, -0.001953125, 1));
}

TEST_CASE("render gives an image of the size asked for", "[camera]") {
    Camera camera(Vector(0, 0, -1), 5);
    Sphere sphere(Vector(0, 0, 6), 5, Colour(1, 0, 0));

    Image image = camera.render(sphere, 5, 3);

    REQUIRE(image.width() == 5);
    REQUIRE(image.height() == 3);
}

TEST_CASE("render colours the pixels whose ray hits the sphere: a plus", "[camera]") {
    Camera camera(Vector(0, 0, -1), 5);
    Sphere sphere(Vector(0, 0, 6), 5, Colour(1, 0, 0));

    Image image = camera.render(sphere, 5, 3);

    std::vector<std::string> expected = {
        "..#..",
        ".###.",
        "..#..",
    };
    for (unsigned int y = 0; y < 3; y++) {
        for (unsigned int x = 0; x < 5; x++) {
            if (expected[y][x] == '#') {
                requireColoursEqual(image.pixel(x, y), Colour(1, 0, 0));
            } else {
                requireColoursEqual(image.pixel(x, y), Colour(0, 0, 0));
            }
        }
    }
}
