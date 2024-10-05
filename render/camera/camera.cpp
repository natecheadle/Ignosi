#include "camera.h"

#include <window/window.h>

#include <cassert>
#include <square_matrix.hpp>

#include "window/window_size.h"

namespace ignosi::render {
Camera::Camera(void* pWindow) : m_pWindow(pWindow) {}

Camera::~Camera() {}

math::SquareMatrix4x4<float> Camera::Projection() const {
  IgnosiWindowSize size = system::WindowGetSize(m_pWindow);
  return math::SquareMatrix4x4<float>::Perspective(
      m_FOV, system::WindowGetAspectRatio(size), m_Near, m_Far);
}

math::SquareMatrix4x4<float> Camera::ViewPerspective() const {
  math::Vector3<float> right = m_Direction.Cross(m_WorldUp).Normalize();
  auto up = right.Cross(m_Direction).Normalize();
  return math::SquareMatrix4x4<float>::LookAt(m_Position,
                                              m_Position + m_Direction, up);
}

math::SquareMatrix4x4<float> Camera::ViewOrthographic() const {
  IgnosiWindowSize size = system::WindowGetSize(m_pWindow);
  return math::SquareMatrix4x4<float>::Orthographic(
      0.0f, static_cast<float>(size.Width), static_cast<float>(size.Height),
      0.0, m_Near, m_Far);
}

void Camera::CameraPosition(const math::Vector3<float>& val) {
  m_Position = val;
}

void Camera::CameraDirection(const math::Vector3<float>& val) {
  m_Direction = val.Normalize();
}

void Camera::WorldUp(const math::Vector3<float>& val) { m_WorldUp = val; }

void Camera::Translate(const math::Vector3<float>& value) {
  m_Position += value;
}

}  // namespace ignosi::render
