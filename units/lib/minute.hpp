#pragma once

#include "time.hpp"

namespace ignosi::units {
template <class T>
class Minute : public Time<T, "min", Minute<T>> {
  using BASE = Time<T, "min", Minute<T>>;

 public:
  constexpr Minute(T val) : BASE(val / PerBase()) {}

  Minute() = default;
  Minute(const Minute& other) = default;
  Minute(Minute&& other) noexcept = default;
  virtual ~Minute() = default;

  Minute& operator=(const Minute& other) = default;
  Minute& operator=(Minute&& other) = default;

  template <class OtherDerived, string::StringLiteral OtherUnits>
  Minute(const Time<T, OtherUnits, OtherDerived>& other) : BASE(0) {
    BASE::BASE::BaseValue(other.BaseValue());
  }

  template <class OtherDerived, string::StringLiteral OtherUnits>
  Minute& operator=(const Time<T, OtherUnits, OtherDerived>& other) {
    BASE::BASE::BaseValue(other.BaseValue());
    return *this;
  }

  constexpr T PerBase() const override { return static_cast<T>(1.0 / 60.0); }
};
}  // namespace ignosi::units
