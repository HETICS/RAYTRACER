#include <iostream>

#include "render/camera.h"
#include "render/trace.h"
#include "colour/colour.h"
#include "math/vector.h"
#include "geometry/ray.h"
#include "geometry/sphere.h"

int main() {
    Camera camera(Vector(0, 0, -1));
    Sphere sphere(Vector(0, 0, 9), 5, Colour(1, 0, 0));

    Ray ray = camera.rayThroughCentre();
    Colour pixel = trace(ray, sphere);

    std::cout << "(" << pixel.r() << ", " << pixel.g() << ", " << pixel.b() << ")\n";
    return 0;
}
