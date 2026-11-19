#pragma once

#include <string>

#include "image/image.h"

class ImageSaver {
  public:
    virtual ~ImageSaver() = default;

    // Writes the whole image to path, or throws std::runtime_error.
    virtual void save(Image& image, const std::string& path) = 0;
};
