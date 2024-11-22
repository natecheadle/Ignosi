
#include "color_rgb.h"

namespace ignosi::render {

Color_RGB::Color_RGB(float red, float green, float blue) noexcept
    : Color({red, green, blue}) {}

Color_RGB::Color_RGB(math::Vector3<float> val) noexcept
    : Color(std::move(val)) {}

float Color_RGB::Red() const { return Data()[0]; }

float Color_RGB::Green() const { return Data()[1]; }

float Color_RGB::Blue() const { return Data()[2]; }

void Color_RGB::Red(float val) { Data()[0] = val; }

void Color_RGB::Green(float val) { Data()[1] = val; }

void Color_RGB::Blue(float val) { Data()[2] = val; }
}  // namespace ignosi::render
