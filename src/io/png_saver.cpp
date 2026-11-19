#include "io/png_saver.h"

#include <cmath>
#include <stdexcept>
#include <vector>

#include "lodepng.h"

static unsigned char toByte(double value) {
    return static_cast<unsigned char>(std::lround(value * 255));
}

void PngSaver::save(Image& image, const std::string& path) {
    std::vector<unsigned char> bytes;
    for (unsigned int y = 0; y < image.height(); y++) {
        for (unsigned int x = 0; x < image.width(); x++) {
            Colour colour = image.pixel(x, y);
            bytes.push_back(toByte(colour.r()));
            bytes.push_back(toByte(colour.g()));
            bytes.push_back(toByte(colour.b()));
        }
    }

    unsigned error = lodepng::encode(path, bytes, image.width(), image.height(), LCT_RGB);
    if (error != 0) {
        throw std::runtime_error(lodepng_error_text(error));
    }
}
