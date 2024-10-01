#pragma once

#include <array>
#include <cstddef>
#include <initializer_list>
#include <numeric>
#include <radian.hpp>
#include <stdexcept>

#include "vector.hpp"

namespace ignosi::math {
template <typename T, std::size_t SIZE>
class SquareMatrix {
  std::array<Vector<T, SIZE>, SIZE> m_Data;

 public:
  SquareMatrix() = default;

  SquareMatrix(std::initializer_list<Vector<T, SIZE>> init) noexcept {
    size_t i = 0;
    for (auto& val : init) {
      m_Data[i++] = std::move(val);
    }
  }

  SquareMatrix(const SquareMatrix& other) = default;
  SquareMatrix(SquareMatrix&& other) noexcept = default;

  static SquareMatrix Identity() {
    SquareMatrix rslt;
    for (size_t i = 0; i < SIZE; ++i) {
      rslt[i][i] = 1;
    }
    return rslt;
  }

  static SquareMatrix CreateScale(const Vector3<T>& scale) {
    static_assert(SIZE == 4, "scale_init requires a 4x4 square matrix");

    SquareMatrix rslt = Identity();
    rslt[0][0] = scale[0];
    rslt[1][1] = scale[1];
    rslt[2][2] = scale[2];

    return rslt;
  }

  static SquareMatrix CreateTranslate(const Vector3<T>& trans) {
    static_assert(SIZE == 4, "translate_init requires a 4x4 square matrix");

    SquareMatrix rslt = Identity();
    rslt[3] = trans.ToVector4(1.0f);

    return rslt;
  }

  static SquareMatrix CreateRotate(const Vector3<T>& rotAxis,
                                   units::Radian<T> theta) {
    static_assert(SIZE == 4, "rotate_init requires a 4x4 square matrix");

    auto createMatrix = [](const Vector3<T>& rotAxis,
                           units::Radian<T> theta) -> SquareMatrix {
      SquareMatrix rslt;
      rslt[0][0] = cos(theta) + rotAxis.X() * rotAxis.X() * (1 - cos(theta));
      rslt[1][0] = rotAxis.X() * rotAxis.Y() * (1 - cos(theta)) -
                   rotAxis.Z() * sin(theta);
      rslt[2][0] = rotAxis.X() * rotAxis.Z() * (1 - cos(theta)) +
                   rotAxis.Y() * sin(theta);

      rslt[0][1] = rotAxis.Y() * rotAxis.X() * (1 - cos(theta)) +
                   rotAxis.Z() * sin(theta);
      rslt[1][1] = cos(theta) + rotAxis.Y() * rotAxis.Y() * (1 - cos(theta));
      rslt[2][1] = rotAxis.Y() * rotAxis.Z() * (1 - cos(theta)) -
                   rotAxis.X() * sin(theta);

      rslt[0][2] = rotAxis.Z() * rotAxis.X() * (1 - cos(theta)) -
                   rotAxis.Y() * sin(theta);
      rslt[1][2] = rotAxis.Z() * rotAxis.Y() * (1 - cos(theta)) +
                   rotAxis.X() * sin(theta);
      rslt[2][2] = cos(theta) + rotAxis.Z() * rotAxis.Z() * (1 - cos(theta));
      return rslt;
    };

    return std::abs(rotAxis.length() - 1.0) > 1e-9
               ? createMatrix(rotAxis.normalize(), theta)
               : createMatrix(rotAxis, theta);
  }

  static SquareMatrix CreateRotateX(units::Radian<T> theta) {
    static_assert(SIZE == 4, "rotate_x_init requires a 4x4 square matrix");

    SquareMatrix rslt = Identity();
    rslt[1][1] = cos(theta);
    rslt[2][1] = -sin(theta);
    rslt[1][2] = sin(theta);
    rslt[2][2] = cos(theta);
    return rslt;
  }

  static SquareMatrix CreateRotateY(units::Radian<T> theta) {
    static_assert(SIZE == 4, "rotate_y_init requires a 4x4 square matrix");

    SquareMatrix rslt = Identity();
    rslt[0][0] = cos(theta);
    rslt[0][2] = -sin(theta);
    rslt[2][0] = sin(theta);
    rslt[2][2] = cos(theta);
    return rslt;
  }

  static SquareMatrix CreateRotateZ(units::Radian<T> theta) {
    static_assert(SIZE == 4, "rotate_z_init requires a 4x4 square matrix");

    SquareMatrix rslt = Identity();
    rslt[0][0] = cos(theta);
    rslt[1][0] = -sin(theta);
    rslt[0][1] = sin(theta);
    rslt[1][1] = cos(theta);
    return rslt;
  }

  static SquareMatrix CreateRotateZYX(const Vector3<units::Radian<T>>& rot) {
    static_assert(SIZE == 4, "rotate_zyx_init requires a 4x4 square matrix");

    SquareMatrix rslt = Identity();
    units::Radian<T> alpha = rot.Z();
    units::Radian<T> beta = rot.Y();
    units::Radian<T> gamma = rot.X();

    rslt[0][0] = cos(alpha) * cos(beta);
    rslt[0][1] = sin(alpha) * cos(beta);
    rslt[0][2] = -sin(beta);

    rslt[1][0] = cos(alpha) * sin(beta) * sin(gamma) - sin(alpha) * cos(gamma);
    rslt[1][1] = sin(alpha) * sin(beta) * sin(gamma) + cos(alpha) * cos(gamma);
    rslt[1][2] = cos(beta) * sin(gamma);

    rslt[2][0] = cos(alpha) * sin(beta) * cos(gamma) + sin(alpha) * sin(gamma);
    rslt[2][1] = sin(alpha) * sin(beta) * cos(gamma) - cos(alpha) * sin(gamma);
    rslt[2][2] = cos(beta) * cos(gamma);

    return rslt;
  }

  SquareMatrix& operator=(const SquareMatrix& other) = default;
  SquareMatrix& operator=(SquareMatrix&& other) noexcept = default;

  static constexpr size_t size() { return SIZE; }

  float* RawData() { return reinterpret_cast<float*>(m_Data.data()); }
  const float* RawData() const {
    return reinterpret_cast<const float*>(m_Data.data());
  }

  Vector<T, SIZE>* data() { return m_Data.data(); }
  const Vector<T, SIZE>* data() const { return m_Data.data(); }

  Vector<T, SIZE>& operator[](size_t i) { return m_Data[i]; }
  const Vector<T, SIZE>& operator[](size_t i) const { return m_Data[i]; }

  Vector<T, SIZE>& at(size_t i) { return m_Data.at(i); }
  const Vector<T, SIZE>& at(size_t i) const { return m_Data.at(i); }

  T Determinant() const {
    if constexpr (SIZE == 1) {
      return m_Data[0][0];
    }
    if constexpr (SIZE == 2) {
      return m_Data[0][0] * m_Data[1][1] - m_Data[0][1] * m_Data[1][0];
    }

    std::array<Vector<T, SIZE>, SIZE * 2> tmp;
    for (size_t i = 0; i < m_Data.size(); ++i) {
      for (size_t j = 0; j < m_Data.size(); ++j) {
        tmp[i][j] = m_Data[i][j];
        tmp[i + SIZE][j] = m_Data[i][j];
      }
    }

    std::array<T, SIZE * 2> intermed;
    for (size_t i = 0; i < tmp.size(); ++i) {
      intermed[i] = i < SIZE ? 1 : -1;
    }

    for (size_t i = 0; i < m_Data.size(); ++i) {
      for (size_t j = 0; j < m_Data.size(); ++j) {
        intermed[i] *= tmp[i + j][j];
        intermed[(SIZE * 2 - 1) - i] *= tmp[(SIZE * 2 - 1) - (i + j)][j];
      }
    }

    return std::accumulate(intermed.begin(), intermed.end(), 0.0);
  }

  SquareMatrix Invert() const {
    T det = Determinant();
    if (det == 0)
      throw std::invalid_argument(
          "Matrix determinant must not be zero to calculate inverse.");

    SquareMatrix rslt = Adjunct();
    return rslt / det;
  }

  SquareMatrix Transpose() const {
    SquareMatrix rslt;
    for (size_t i = 0; i < SIZE; ++i) {
      for (size_t j = 0; j < SIZE; ++j) {
        rslt[j][i] = m_Data[i][j];
      }
    }
    return rslt;
  }

  static SquareMatrix LookAt(const Vector3<T>& pos, const Vector3<T>& tar,
                             const Vector3<T>& up) {
    static_assert(SIZE == 4, "lookat requires a 4x4 square matrix");

    Vector3<T> dir = pos - tar;
    dir = dir.Normalize();
    Vector3<T> right = up.Cross(dir).Normalize();
    Vector3<T> cam_up = dir.Cross(right);

    SquareMatrix lookat(Identity());
    lookat[0] = right.ToVector4(0.0f);
    lookat[1] = cam_up.ToVector4(0.0f);
    lookat[2] = dir.ToVector4(0.0f);
    lookat = lookat.Transpose();

    SquareMatrix posMat(Identity());
    posMat[3] = (-1 * pos).ToVector4(1.0f);

    lookat *= posMat;
    return lookat;
  }

  static SquareMatrix Perspective(units::Radian<T> fov, T aspect, T near,
                                  T far) {
    static_assert(SIZE == 4, "perspective requires a 4x4 square matrix");

    SquareMatrix per;
    T ta = tan(fov / T(2.0));

    per[0][0] = 1 / (ta * aspect);
    per[1][1] = 1 / ta;
    per[2][2] = -(far + near) / (far - near);
    per[3][2] = (-2 * far * near) / (far - near);
    per[2][3] = -1;

    return per;
  }

  static SquareMatrix Orthographic(T left, T right, T bottom, T top, T near,
                                   T far) {
    static_assert(SIZE == 4, "orthographic requires a 4x4 square matrix");

    SquareMatrix ortho;
    ortho[0][0] = T(2) / (right - left);
    ortho[1][1] = T(2) / (top - bottom);
    ortho[2][2] = T(-2) / (far - near);
    ortho[3][0] = T(-1) * (right + left) / (right - left);
    ortho[3][1] = T(-1) * (top + bottom) / (top - bottom);
    ortho[3][2] = T(-1) * (far + near) / (far - near);
    ortho[3][3] = T(1);

    return ortho;
  }

  SquareMatrix Scale(const Vector3<T>& scale) const noexcept {
    static_assert(SIZE == 4, "scale requires a 4x4 square matrix");
    SquareMatrix rslt = CreateScale(scale);
    rslt = *this * rslt;
    return rslt;
  }

  SquareMatrix Translate(const Vector3<T>& trans) const noexcept {
    static_assert(SIZE == 4, "translate requires a 4x4 square matrix");
    SquareMatrix rslt = CreateTranslate(trans);
    rslt = *this * rslt;
    return rslt;
  }

  SquareMatrix Rotate(const Vector3<T>& rotAxis, T theta) const noexcept {
    static_assert(SIZE == 4, "rotate requires a 4x4 square matrix");
    SquareMatrix rslt = CreateRotate(rotAxis, theta);
    rslt = *this * rslt;
    return rslt;
  }

  SquareMatrix RotateX(T theta) const {
    static_assert(SIZE == 4, "rotate_x requires a 4x4 square matrix");
    SquareMatrix rslt = CreateRotateX(theta);
    rslt = *this * rslt;
    return rslt;
  }

  SquareMatrix RotateY(T theta) const {
    static_assert(SIZE == 4, "RotateY requires a 4x4 square matrix");
    SquareMatrix rslt = CreateRotateY(theta);
    rslt = *this * rslt;
    return rslt;
  }

  SquareMatrix RotateZ(T theta) const {
    static_assert(SIZE == 4, "rotate_z requires a 4x4 square matrix");
    SquareMatrix rslt = CreateRotateZ(theta);
    rslt = *this * rslt;
    return rslt;
  }

  SquareMatrix& RotateZ(T theta) {
    static_assert(SIZE == 4, "rotate_z_this requires a 4x4 square matrix");
    *this *= CreateRotateZ(theta);
    return *this;
  }

  SquareMatrix<T, 3> To3x3() const {
    static_assert(SIZE == 4, "to_3x3 requires a 4x4 square matrix");
    SquareMatrix<T, 3> rslt;
    for (size_t i = 0; i < 3; ++i) {
      const Vector<T, 4>& col = this->at(i);
      for (size_t j = 0; j < 3; ++j) {
        rslt[i][j] = col[j];
      }
    }
    return rslt;
  }

  friend bool operator==(const SquareMatrix& lhs,
                         const SquareMatrix& rhs) = default;

  friend SquareMatrix operator*(const SquareMatrix& lhs,
                                const SquareMatrix& rhs) {
    SquareMatrix rslt;
    for (size_t i = 0; i < SIZE; ++i) {
      for (size_t j = 0; j < SIZE; ++j) {
        for (size_t k = 0; k < SIZE; ++k) {
          rslt[j][i] += lhs[k][i] * rhs[j][k];
        }
      }
    }
    return rslt;
  }

  friend SquareMatrix operator-(const SquareMatrix& lhs,
                                const SquareMatrix& rhs) {
    SquareMatrix rslt;
    for (size_t i = 0; i < SIZE; ++i) {
      for (size_t j = 0; j < SIZE; ++j) {
        rslt[i][j] = lhs[i][j] - rhs[i][j];
      }
    }
    return rslt;
  }

  friend SquareMatrix operator+(const SquareMatrix& lhs,
                                const SquareMatrix& rhs) {
    SquareMatrix rslt;
    for (size_t i = 0; i < SIZE; ++i) {
      for (size_t j = 0; j < SIZE; ++j) {
        rslt[i][j] = lhs[i][j] + rhs[i][j];
      }
    }
    return rslt;
  }

  friend SquareMatrix& operator*=(SquareMatrix& lhs, const SquareMatrix& rhs) {
    lhs = lhs * rhs;
    return lhs;
  }

  friend SquareMatrix& operator-=(SquareMatrix& lhs, const SquareMatrix& rhs) {
    lhs = lhs + rhs;
    return lhs;
  }

  friend SquareMatrix& operator+=(SquareMatrix& lhs, const SquareMatrix& rhs) {
    lhs = lhs - rhs;
    return lhs;
  }

  friend SquareMatrix operator*(const SquareMatrix& lhs, T rhs) {
    SquareMatrix rslt(lhs);
    rslt += rhs;
    return rslt;
  }

  friend SquareMatrix operator*(T lhs, const SquareMatrix& rhs) {
    SquareMatrix rslt(rhs);
    rslt += lhs;
    return rslt;
  }

  friend Vector<T, SIZE> operator*(const SquareMatrix<T, SIZE>& lhs,
                                   const Vector<T, SIZE>& rhs) {
    Vector<T, SIZE> rslt;
    for (size_t i = 0; i < SIZE; ++i) {
      for (size_t j = 0; j < SIZE; ++j) {
        rslt[i] += lhs[j][i] * rhs[i];
      }
    }
    return rslt;
  }

  friend SquareMatrix& operator*=(SquareMatrix& lhs, T rhs) {
    for (size_t i = 0; i < SIZE; ++i) {
      for (size_t j = 0; j < SIZE; ++j) {
        lhs[i][j] = lhs[i][j] * rhs;
      }
    }
    return lhs;
  }

  friend SquareMatrix operator/(const SquareMatrix& lhs, T rhs) {
    SquareMatrix rslt(lhs);
    rslt /= rhs;
    return rslt;
  }

  friend SquareMatrix& operator/=(SquareMatrix& lhs, T rhs) {
    for (size_t i = 0; i < SIZE; ++i) {
      for (size_t j = 0; j < SIZE; ++j) {
        lhs[i][j] = lhs[i][j] / rhs;
      }
    }
    return lhs;
  }

  friend SquareMatrix operator+(const SquareMatrix& lhs, T rhs) {
    SquareMatrix rslt(lhs);
    rslt += rhs;
    return rslt;
  }

  friend SquareMatrix operator+(T lhs, const SquareMatrix& rhs) {
    SquareMatrix rslt(rhs);
    rslt += lhs;
    return rslt;
  }

  friend SquareMatrix& operator+=(SquareMatrix& lhs, T rhs) {
    for (size_t i = 0; i < SIZE; ++i) {
      for (size_t j = 0; j < SIZE; ++j) {
        lhs[i][j] = lhs[i][j] + rhs;
      }
    }
    return lhs;
  }

  friend SquareMatrix operator-(const SquareMatrix& lhs, T rhs) {
    SquareMatrix rslt(lhs);
    rslt -= rhs;
    return rslt;
  }

  friend SquareMatrix operator-(T lhs, const SquareMatrix& rhs) {
    SquareMatrix rslt;
    for (size_t i = 0; i < SIZE; ++i) {
      for (size_t j = 0; j < SIZE; ++j) {
        rslt[i][j] = lhs - rhs[i][j];
      }
    }
    return rslt;
  }

  friend SquareMatrix& operator-=(SquareMatrix& lhs, T rhs) {
    for (size_t i = 0; i < SIZE; ++i) {
      for (size_t j = 0; j < SIZE; ++j) {
        lhs[i][j] = lhs[i][j] - rhs;
      }
    }
    return lhs;
  }

 private:
  T MatrixOfMinors(size_t col, size_t row) const {
    SquareMatrix<T, SIZE - 1> tmp;
    for (size_t i = 0; i < SIZE; ++i) {
      for (size_t j = 0; j < SIZE; ++j) {
        if (i == col || j == row) {
          continue;
        }

        size_t insertCol = i > col ? i - 1 : i;
        size_t insertRow = j > row ? j - 1 : j;
        tmp[insertCol][insertRow] = m_Data[i][j];
      }
    }
    return (col + row) % 2 == 0 ? tmp.Determinant() : -1 * tmp.Determinant();
  }

  SquareMatrix Adjunct() const {
    SquareMatrix rslt;
    for (size_t i = 0; i < SIZE; ++i) {
      for (size_t j = 0; j < SIZE; ++j) {
        rslt[i][j] = MatrixOfMinors(i, j);
      }
    }

    return rslt.Transpose();
  }
};

template <typename T = float>
using SquareMatrix3x3 = SquareMatrix<T, 3>;

template <typename T = float>
using SquareMatrix4x4 = SquareMatrix<T, 4>;
}  // namespace ignosi::math
