#include <catch2/catch_test_macros.hpp>

#include "geometry/ray.h"
#include "math/vector.h"
#include "render/camera.h"
#include "test_helpers.h"

TEST_CASE("the centre ray starts at the camera and looks along +z", "[camera]") {
    Camera camera(Vector(1, 2, -1));

    Ray ray = camera.rayThroughCentre();

    requireVectorsEqual(ray.origin(), Vector(1, 2, -1));
    requireVectorsEqual(ray.direction(), Vector(0, 0, 1));
}
