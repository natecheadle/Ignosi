#pragma once

#include <square_matrix.hpp>

#include "lighting/light.h"
#include "lighting/light_attenuation.h"
#include "lighting/light_directional.h"
#include "lighting/light_point.h"
#include "lighting/light_spotlight.h"
#include "texture/imaterial.h"

namespace ignosi::render {
class IShaderProgram {
 public:
  IShaderProgram() = default;
  virtual ~IShaderProgram() = default;

  virtual void Use() const = 0;

  virtual void SetShaderVar(std::string_view name, bool value) const = 0;
  virtual void SetShaderVar(std::string_view name, int value) const = 0;
  virtual void SetShaderVar(std::string_view name, float value) const = 0;
  virtual void SetShaderVar(
      std::string_view name,
      const math::SquareMatrix4x4<float>& value) const = 0;
  virtual void SetShaderVar(
      std::string_view name,
      const math::SquareMatrix3x3<float>& value) const = 0;
  virtual void SetShaderVar(std::string_view name,
                            const math::Vector3<float>& value) const = 0;
  virtual void SetShaderVar(std::string_view name,
                            const math::Vector4<float>& value) const = 0;
  virtual void SetShaderVar(std::string_view name,
                            const IMaterial& value) const = 0;
  virtual void SetShaderVar(std::string_view name,
                            const Light_Directional& value) const = 0;
  virtual void SetShaderVar(std::string_view name,
                            const Light_Point& value) const = 0;
  virtual void SetShaderVar(std::string_view name,
                            const Light_Spotlight& value) const = 0;
  virtual void SetShaderVar(std::string_view name,
                            const Light_Attenuation& value) const = 0;
  virtual void SetShaderVar(std::string_view name,
                            const Light& value) const = 0;
};
}  // namespace ignosi::render
