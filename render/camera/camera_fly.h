#pragma once

#include <numbers>

#include "camera.h"

namespace ignosi::render {
class Camera_Fly : public Camera {
  float m_ZoomSpeed{0.1};
  float m_PanSpeed{0.1};
  float m_RotateSpeed{(std::numbers::pi_v<float> / 2.0f) / 100.0f};

  units::Radian<float> m_Pitch;
  units::Radian<float> m_Yaw;
  units::Radian<float> m_MaxRot{M_PI_2};

 public:
  Camera_Fly(void* pWindow);
  virtual ~Camera_Fly() = default;

  float ZoomSpeed() const;
  float PanSpeed() const;
  float RotateSpeed() const;

  void ZoomSpeed(float value);
  void PanSpeed(float value);
  void RotateSpeed(float value);

  void PanUp(float value);
  void PanDown(float value);
  void PanLeft(float value);
  void PanRight(float value);

  void RotatePitch(const units::Radian<float>& value);
  void RotateYaw(const units::Radian<float>& value);

  void ZoomIn(float value);
  void ZoomOut(float value);

 private:
  math::Vector3<float> CalcDir() const;

  void PanUp();
  void PanDown();
  void PanLeft();
  void PanRight();

  void RotatePitchPos();
  void RotatePitchNeg();
  void RotateYawPos();
  void RotateYawNeg();

  void ZoomIn();
  void ZoomOut();
};
}  // namespace ignosi::render
