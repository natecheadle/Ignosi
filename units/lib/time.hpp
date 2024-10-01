#pragma once

#include "unit.hpp"

namespace ignosi::units {
template <class T, string::StringLiteral Units, class Derived>
class Time : public Unit<T, UnitType::Time, Units, Derived> {
 protected:
  using BASE = Unit<T, UnitType::Time, Units, Derived>;

  constexpr Time(T val) : BASE(val) {}

  constexpr Time() = default;
  Time(const Time& other) = default;
  Time(Time&& other) noexcept = default;
  virtual ~Time() = default;

  Time& operator=(const Time& other) = default;
  Time& operator=(Time&& other) = default;
};

}  // namespace ignosi::units
