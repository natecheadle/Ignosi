#pragma once

#include <vector.hpp>

#include "light.h"
#include "light_attenuation.h"

namespace ignosi::render {
struct Light_Point {
  math::Vector3<float> Position;
  Light_Attenuation Attenuation;
  struct Light Light;
};
}  // namespace ignosi::render
