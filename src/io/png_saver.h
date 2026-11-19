#pragma once

#include <string>

#include "image/image.h"
#include "io/image_saver.h"

class PngSaver : public ImageSaver {
  public:
    void save(Image& image, const std::string& path) override;
};
