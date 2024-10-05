#pragma once

#include "texture/color_rgb.h"

namespace ignosi::render {
struct Light {
  Color_RGB Ambient;
  Color_RGB Diffuse;
  Color_RGB Specular;
};
}  // namespace ignosi::render
