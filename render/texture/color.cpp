
#include "color.h"

namespace ignosi::render {

Color::Color(math::Vector3<float> val) noexcept : m_Value(std::move(val)) {}

const math::Vector3<float>& Color::Data() const { return m_Value; }

math::Vector3<float>& Color::Data() { return m_Value; }

void Color::Data(const math::Vector3<float>& val) { m_Value = val; }
}  // namespace ignosi::render
