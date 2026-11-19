#include <catch2/catch_test_macros.hpp>

#include "colour/colour.h"
#include "image/image.h"
#include "test_helpers.h"

TEST_CASE("an image has the width and height it was made with", "[image]") {
    Image image(5, 3);

    REQUIRE(image.width() == 5);
    REQUIRE(image.height() == 3);
}

TEST_CASE("setPixel(3, 2) sets column 3, row 2, and leaves every other pixel black", "[image]") {
    Image image(5, 3);

    image.setPixel(3, 2, Colour(1, 0, 0));

    for (unsigned int y = 0; y < 3; y++) {
        for (unsigned int x = 0; x < 5; x++) {
            if (x == 3 && y == 2) {
                requireColoursEqual(image.pixel(x, y), Colour(1, 0, 0));
            } else {
                requireColoursEqual(image.pixel(x, y), Colour(0, 0, 0));
            }
        }
    }
}
