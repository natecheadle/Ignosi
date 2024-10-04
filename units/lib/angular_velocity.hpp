#pragma once

#include "radian.hpp"
#include "second.hpp"
#include "unit.hpp"

namespace ignosi::units {

template <class T, class AngleUnit, class TimeUnit>
class AngularVelocity
    : public Unit<T, UnitType::AngularVelocity,
                  AngleUnit::StringLit() + string::StringLiteral("/") +
                      TimeUnit::StringLit(),
                  AngularVelocity<T, AngleUnit, TimeUnit>> {
  using BASE = Unit<T, UnitType::AngularVelocity,
                    AngleUnit::StringLit() + string::StringLiteral("/") +
                        TimeUnit::StringLit(),
                    AngularVelocity<T, AngleUnit, TimeUnit>>;
  static constexpr AngleUnit angle = AngleUnit(1.0);
  static constexpr TimeUnit time = TimeUnit(1.0);

 public:
  constexpr AngularVelocity(T val) : BASE(val / PerBase()) {}

  AngularVelocity() = default;
  AngularVelocity(const AngularVelocity& other) = default;
  AngularVelocity(AngularVelocity&& other) noexcept = default;
  virtual ~AngularVelocity() = default;

  AngularVelocity& operator=(const AngularVelocity& other) = default;
  AngularVelocity& operator=(AngularVelocity&& other) = default;

  template <class OtherAngleUnit, class OtherTimeUnit>
  AngularVelocity(
      const AngularVelocity<T, OtherAngleUnit, OtherTimeUnit>& other)
      : BASE(other.BaseValue()) {}

  template <class OtherAngleUnit, class OtherTimeUnit>
  AngularVelocity& operator=(
      const AngularVelocity<T, OtherAngleUnit, OtherTimeUnit>& other) {
    if (this == &other) return *this;

    BASE::BaseValue(other.BaseValue());
    return *this;
  }

  template <class OtherTimeUnit, string::StringLiteral OtherUnits>
  AngleUnit operator*(const Time<T, OtherUnits, OtherTimeUnit>& other) {
    AngleUnit rslt;
    rslt.Value(rslt.FromBase(BASE::BaseValue() * other.BaseValue()));
    return rslt;
  }

  constexpr T PerBase() const override {
    return angle.PerBase() / time.PerBase();
  }
};

template <class T>
using RadianPerSecond = AngularVelocity<T, Radian<T>, Second<T>>;

template <class T, class OtherAngleUnit, class OtherTimeUnit,
          string::StringLiteral OtherUnits1, string::StringLiteral OtherUnits2>
RadianPerSecond<T> operator/(const Angle<T, OtherUnits1, OtherAngleUnit>& lhs,
                             const Time<T, OtherUnits2, OtherTimeUnit>& rhs) {
  RadianPerSecond<T> rslt(lhs.BaseValue() / rhs.BaseValue());
  return rslt;
}

}  // namespace ignosi::units
