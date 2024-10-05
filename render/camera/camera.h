#pragma once

#include <radian.hpp>
#include <square_matrix.hpp>
#include <vector.hpp>

namespace ignosi::render {
class Camera {
  math::Vector3<float> m_Position{0.0, 0.0, 5.0};
  math::Vector3<float> m_Direction{0.0, 0.0, -1.0};
  math::Vector3<float> m_WorldUp{0.0, 1.0, 0.0};

  units::Radian<float> m_FOV{M_PI_4};
  float m_Near{0.1};
  float m_Far{100.0};

  void* m_pWindow;

 public:
  Camera(void* pWindow);
  virtual ~Camera();

  virtual math::SquareMatrix4x4<float> Projection() const;
  virtual math::SquareMatrix4x4<float> ViewPerspective() const;
  virtual math::SquareMatrix4x4<float> ViewOrthographic() const;

  const math::Vector3<float>& CameraPosition() const { return m_Position; }
  const math::Vector3<float>& CameraDirection() const { return m_Direction; }
  const math::Vector3<float>& WorldUp() const { return m_WorldUp; }
  const units::Radian<float>& FOV() const { return m_FOV; }
  float Near() const { return m_Near; }
  float Far() const { return m_Far; }

  void CameraPosition(const math::Vector3<float>& val);
  void CameraDirection(const math::Vector3<float>& val);
  void WorldUp(const math::Vector3<float>& val);
  void FOV(const units::Radian<float>& val) { m_FOV = val; }
  void Near(float val) { m_Near = val; }
  void Far(float val) { m_Far = val; }

  void Translate(const math::Vector3<float>& value);

 protected:
  const void* Window() const { return m_pWindow; }
};
}  // namespace ignosi::render
