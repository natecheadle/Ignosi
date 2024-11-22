#pragma once

#include <radian.hpp>
#include <vector.hpp>

#include "light.h"
#include "light_attenuation.h"

namespace ignosi::render {
struct Light_Spotlight {
  math::Vector3<float> Direction;
  math::Vector3<float> Position;
  units::Radian<float> Cutoff;
  units::Radian<float> OuterCutoff;
  Light_Attenuation Attenuation;
  struct Light Light;
};
}  // namespace ignosi::render
