#pragma once

#include <cmath>
#include <gcem.hpp>
#include <numbers>

#include "unit.hpp"

namespace ignosi::units {
template <class T, string::StringLiteral Units, class Derived>
class Angle : public Unit<T, UnitType::Angle, Units, Derived> {
 protected:
  using BASE = Unit<T, UnitType::Angle, Units, Derived>;

  constexpr Angle(T val) : BASE(val) {}

  constexpr Angle() = default;
  Angle(const Angle& other) = default;
  Angle(Angle&& other) noexcept = default;
  virtual ~Angle() = default;

  Angle& operator=(const Angle& other) = default;
  Angle& operator=(Angle&& other) = default;

 public:
  void Modulo() {
    BASE::BaseValue(
        std::fmod(BASE::BaseValue(), 2.0f * std::numbers::pi_v<float>));
  }
};

template <class T, class Derived, string::StringLiteral Units>
constexpr T sin(const Angle<T, Units, Derived>& val) {
  return gcem::sin(val.BaseValue());
}

template <class T, class Derived, string::StringLiteral Units>
constexpr T cos(const Angle<T, Units, Derived>& val) {
  return gcem::cos(val.BaseValue());
}

template <class T, class Derived, string::StringLiteral Units>
constexpr T tan(const Angle<T, Units, Derived>& val) {
  return gcem::tan(val.BaseValue());
}

}  // namespace ignosi::units
