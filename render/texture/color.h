#pragma once

#include <vector.hpp>

namespace ignosi::render {
class Color {
  math::Vector3<float> m_Value;

 protected:
  Color() noexcept = default;
  Color(math::Vector3<float> val) noexcept;

 public:
  const math::Vector3<float>& Data() const;
  math::Vector3<float>& Data();
  void Data(const math::Vector3<float>& val);
};
}  // namespace ignosi::render
