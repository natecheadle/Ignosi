#pragma once

#include "color.h"

namespace ignosi::render {

class Color_RGB : public Color {
 public:
  Color_RGB() noexcept = default;
  Color_RGB(float red, float green, float blue) noexcept;

  Color_RGB(math::Vector3<float> val) noexcept;

  float Red() const;
  float Green() const;
  float Blue() const;

  void Red(float val);
  void Green(float val);
  void Blue(float val);
};
}  // namespace ignosi::render
