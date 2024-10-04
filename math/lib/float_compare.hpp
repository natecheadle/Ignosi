#pragma once

#include <algorithm>
#include <concepts>
#include <cstdlib>
#include <limits>
#include <type_traits>

namespace ignosi::math {

template <typename T, typename... Args>
T max(T a, T b, Args... args) {
  return std::max(std::max(a, b), args...);
}

template <typename T, typename... Args>
T min(T a, T b, Args... args) {
  return std::min(std::min(a, b), args...);
}

template <std::floating_point T>
bool AlmostEqual(T lhs, T rhs) {
  if constexpr (std::is_floating_point_v<T>) {
    T maxXYOne = max<T>(1, std::abs(lhs), std::abs(rhs));
    return std::abs(lhs - rhs) <= std::numeric_limits<T>::epsilon() * maxXYOne;
  }
  return lhs == rhs;
}
}  // namespace ignosi::math
