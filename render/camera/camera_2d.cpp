#include "camera_2d.h"

#include <numbers>
#include <vector.hpp>

namespace ignosi::render {
Camera2D::Camera2D(void* pWindow)
    : Camera(pWindow), m_Pitch(0.0), m_Yaw(-std::numbers::pi_v<float> / 2.0f) {
  Near(-1.0);
  Far(1.0);
}

void Camera2D::PanUp(float value) { Translate({0, -value, 0}); }

void Camera2D::PanDown(float value) { Translate({0, value, 0}); }

void Camera2D::PanLeft(float value) { Translate({value, 0, 0}); }

void Camera2D::PanRight(float value) { Translate({-value, 0, 0}); }

void Camera2D::ZoomIn(float value) { Translate({0, 0, value}); }

void Camera2D::ZoomOut(float value) { Translate({0, 0, -value}); }
}  // namespace ignosi::render
