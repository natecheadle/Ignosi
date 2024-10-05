#pragma once

#include <vector.hpp>

#include "light.h"

namespace ignosi::render {
struct Light_Directional {
  math::Vector3<float> Direction;
  struct Light Light;
};
}  // namespace ignosi::render
