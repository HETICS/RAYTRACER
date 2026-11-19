#include "material/lambert_shader.h"

#include <algorithm>

#include "geometry/hit_info.h"
#include "light/light.h"

LambertShader::LambertShader(const Colour& colour) : _colour(colour) {}

Colour LambertShader::shade(const HitInfo& hit, const Light& light) const {
    Vector toLight = (light.position() - hit.point).normalised();
    double brightness = std::max(0.0, hit.normal.dot(toLight));
    Colour tint = light.colour();
    return Colour(brightness * _colour.r() * tint.r(),
                  brightness * _colour.g() * tint.g(),
                  brightness * _colour.b() * tint.b());
}
