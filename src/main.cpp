#include <iostream>
#include <memory>
#include <string>

#include "colour/colour.h"
#include "geometry/sphere.h"
#include "material/flat_shader.h"
#include "image/image.h"
#include "io/png_saver.h"
#include "math/vector.h"
#include "render/camera.h"

int main() {
    Camera camera(Vector(0, 0, -1), 2);
    Sphere sphere(Vector(0, 0, 9), 5, std::make_shared<FlatShader>(Colour(1, 0, 0)));

    Image image = camera.render(sphere, 400, 300);

    std::string path = "image.png";
    PngSaver saver;
    saver.save(image, path);
    std::cout << path << "\n";
    return 0;
}
