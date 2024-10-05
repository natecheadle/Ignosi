#pragma once

#include <array>
#include <cmath>
#include <cstddef>

#include "float_compare.hpp"

namespace ignosi::math {

template <typename T, std::size_t SIZE>
class Vector {
  std::array<T, SIZE> m_Data;

 public:
  using const_iterator = typename std::array<T, SIZE>::const_iterator;
  using iterator = typename std::array<T, SIZE>::iterator;

  Vector() { m_Data.fill(T()); }

  Vector(const Vector& other) = default;
  Vector(Vector&& other) = default;

  Vector& operator=(const Vector& other) = default;
  Vector& operator=(Vector&& other) = default;

  template <typename... Ts>
    requires(sizeof...(Ts) == SIZE)
  Vector(Ts&&... values) : m_Data({T(std::forward<Ts>(values))...}) {}

  ~Vector() = default;

  T& At(std::size_t i) { return m_Data.at(i); }
  const T& At(std::size_t i) const { return m_Data.at(i); }

  T& operator[](std::size_t i) { return m_Data[i]; }
  const T& operator[](std::size_t i) const { return m_Data[i]; }

  std::size_t Size() const { return m_Data.size(); }

  T Magnitude() const {
    T sum{0};
    for (size_t i = 0; i < Size(); ++i) {
      sum += m_Data[i] * m_Data[i];
    }
    return std::sqrt(sum);
  }

  T Dot(const Vector& other) const {
    T sum{0};
    for (size_t i = 0; i < other.Size(); ++i) {
      sum += other.At(i) * At(i);
    }
    return sum;
  }

  T Distance(const Vector& other) const {
    T sum = 0.0f;
    for (size_t i = 0; i < SIZE; ++i) {
      T temp = (other.At(i) - At(i));
      sum += temp * temp;
    }

    return std::sqrt(sum);
  }

  Vector Normalize() const {
    Vector rslt(*this);
    return rslt / Magnitude();
  }

  Vector Perp() const {
    static_assert(SIZE == 2, "perp requires a vector of size 2");
    Vector perp(T(1), T(1));
    if (X() != T(0)) {
      perp[0] = -Y() / X();
    } else {
      perp[1] = -X() / Y();
    }

    return perp;
  }

  Vector Cross(const Vector& other) const {
    static_assert(SIZE == 3, "perp requires a vector of size 3");
    Vector rslt;
    rslt.X((Y() * other.Z()) - (Z() * other.Y()));
    rslt.Y((Z() * other.X()) - (X() * other.Z()));
    rslt.Z((X() * other.Y()) - (Y() * other.X()));

    return rslt;
  }

  T* Data() { return m_Data.data(); }
  const T* Data() const { return m_Data.data(); }

  iterator begin() { return m_Data.begin(); }

  const_iterator begin() const { return m_Data.begin(); }

  const_iterator cbegin() const { return m_Data.begin(); }

  iterator end() { return m_Data.end(); }

  const_iterator end() const { return m_Data.end(); }

  const_iterator cend() const { return m_Data.cend(); }

  constexpr T X() const {
    static_assert(SIZE >= 1 && SIZE <= 4,
                  "x() requires a vector of 1 <= size <= 4");
    return At(0U);
  }

  constexpr void X(T val) {
    static_assert(SIZE >= 1 && SIZE <= 4,
                  "x() requires a vector of 1 <= size <= 4");
    At(0U) = val;
  }

  constexpr T Y() const {
    static_assert(SIZE >= 2 && SIZE <= 4,
                  "y() requires a vector of 2 <= size <= 4");
    return At(1U);
  }

  constexpr void Y(T val) {
    static_assert(SIZE >= 2 && SIZE <= 4,
                  "y() requires a vector of 2 <= size <= 4");
    At(1U) = val;
  }

  constexpr T Z() const {
    static_assert(SIZE >= 3 && SIZE <= 4,
                  "z() requires a vector of 3 <= size <= 4");
    return At(2U);
  }

  constexpr void Z(T val) {
    static_assert(SIZE >= 3 && SIZE <= 4,
                  "z() requires a vector of 3 <= size <= 4");
    At(2U) = val;
  }

  constexpr T W() const {
    static_assert(SIZE == 4, "w() requires a vector of size 4");
    return At(3U);
  }

  constexpr void W(T val) {
    static_assert(SIZE == 4, "w() requires a vector of size 4");
    At(3U) = val;
  }

  friend bool operator==(const Vector& lhs, const Vector& rhs) {
    bool rslt{true};

    for (size_t i = 0; i < lhs.Size(); ++i) {
      rslt = rslt && AlmostEqual<T>(lhs[i], rhs[i]);
    }
    return rslt;
  }

  friend Vector operator-(const Vector& lhs, const Vector& rhs) {
    Vector rslt(lhs);
    return rslt -= rhs;
  }

  friend Vector operator+(const Vector& lhs, const Vector& rhs) {
    Vector rslt(lhs);
    return rslt += rhs;
  }

  friend Vector& operator-=(Vector& lhs, const Vector& rhs) {
    for (size_t i = 0; i < lhs.Size(); ++i) {
      lhs[i] -= rhs[i];
    }
    return lhs;
  }

  friend Vector& operator+=(Vector& lhs, const Vector& rhs) {
    for (size_t i = 0; i < lhs.Size(); ++i) {
      lhs[i] += rhs[i];
    }
    return lhs;
  }

  friend Vector operator*(const Vector& lhs, T rhs) {
    Vector rslt(lhs);
    return rslt *= rhs;
  }

  friend Vector operator*(T lhs, const Vector& rhs) {
    Vector rslt(rhs);
    return rslt *= lhs;
  }

  friend Vector operator*=(Vector& lhs, T rhs) {
    for (size_t i = 0; i < lhs.Size(); ++i) {
      lhs[i] *= rhs;
    }
    return lhs;
  }

  friend Vector operator/(const Vector& lhs, T rhs) {
    Vector rslt(lhs);
    return rslt /= rhs;
  }

  friend Vector operator/=(Vector& lhs, T rhs) {
    for (size_t i = 0; i < lhs.Size(); ++i) {
      lhs[i] /= rhs;
    }
    return lhs;
  }

  Vector<T, 3> ToVector3() const {
    static_assert(SIZE == 4, "ToVector3 requires a vector of size 4");
    return Vector<T, 3>(X(), Y(), Z());
  }

  Vector<T, 3> ToVector3(T z) const {
    static_assert(SIZE == 2, "ToVector3 requires a vector of size 2");
    return Vector<T, 3>(X(), Y(), z);
  }

  Vector<T, 4> ToVector4(T z, T w) const {
    static_assert(SIZE == 2, "ToVector4 requires a vector of size 2");
    return Vector<T, 4>(X(), Y(), z, w);
  }

  Vector<T, 4> ToVector4(T w) const {
    static_assert(SIZE == 3, "ToVector3 requires a vector of size 3");
    return Vector<T, 4>(X(), Y(), Z(), w);
  }
};

template <typename T>
using Vector2 = Vector<T, 2>;

template <typename T>
using Vector3 = Vector<T, 3>;

template <typename T>
using Vector4 = Vector<T, 4>;

}  // namespace ignosi::math
