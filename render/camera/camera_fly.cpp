#include "camera_fly.h"

#include <angle.hpp>
#include <vector.hpp>

namespace ignosi::render {

Camera_Fly::Camera_Fly(const system::Window& window)
    : Camera(window), m_Pitch(0.0), m_Yaw(-M_PI_2) {}

float Camera_Fly::ZoomSpeed() const { return m_ZoomSpeed; }

float Camera_Fly::PanSpeed() const { return m_PanSpeed; }

float Camera_Fly::RotateSpeed() const { return m_RotateSpeed; }

void Camera_Fly::ZoomSpeed(float value) { m_ZoomSpeed = value; }

void Camera_Fly::PanSpeed(float value) { m_PanSpeed = value; }

void Camera_Fly::RotateSpeed(float value) { m_RotateSpeed = value; }

void Camera_Fly::PanUp(float value) { Translate({0, -value, 0}); }

void Camera_Fly::PanDown(float value) { Translate({0, value, 0}); }

void Camera_Fly::PanLeft(float value) { Translate({value, 0, 0}); }

void Camera_Fly::PanRight(float value) { Translate({-value, 0, 0}); }

void Camera_Fly::RotatePitch(const units::Radian<float>& value) {
  m_Pitch += value;
  m_Pitch = m_Pitch >= m_MaxRot ? m_MaxRot : m_Pitch;
  CameraDirection(CalcDir());
}

void Camera_Fly::RotateYaw(const units::Radian<float>& value) {
  m_Yaw += value;
  m_Yaw = m_Yaw >= m_MaxRot ? m_MaxRot : m_Yaw;
  CameraDirection(CalcDir());
}

void Camera_Fly::ZoomIn(float value) { Translate({0, 0, value}); }

void Camera_Fly::ZoomOut(float value) { Translate({0, 0, -value}); }

math::Vector3<float> Camera_Fly::CalcDir() const {
  math::Vector3<float> dir;
  dir.X(cos(m_Yaw) * cos(m_Pitch));
  dir.Y(sin(m_Pitch));
  dir.Z(sin(m_Yaw) * cos(m_Pitch));

  return dir;
}

void Camera_Fly::PanUp() { PanUp(m_PanSpeed); }

void Camera_Fly::PanDown() { PanDown(m_PanSpeed); }

void Camera_Fly::PanLeft() { PanLeft(m_PanSpeed); }

void Camera_Fly::PanRight() { PanRight(m_PanSpeed); }

void Camera_Fly::RotatePitchPos() { RotatePitch(m_RotateSpeed); }

void Camera_Fly::RotatePitchNeg() { RotatePitch(-m_RotateSpeed); }

void Camera_Fly::RotateYawPos() { RotateYaw(m_RotateSpeed); }

void Camera_Fly::RotateYawNeg() { RotateYaw(-m_RotateSpeed); }

void Camera_Fly::ZoomIn() { ZoomIn(m_ZoomSpeed); }

void Camera_Fly::ZoomOut() { ZoomOut(m_ZoomSpeed); }

}  // namespace ignosi::render
