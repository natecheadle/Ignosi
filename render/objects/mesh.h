#pragma once

#include <radian.hpp>

#include "ivertex_buffer.h"
#include "shader/ishader_program.h"
#include "texture/imaterial.h"
#include "vertex_data.h"

namespace ignosi::render {
class IRenderer;

class Mesh {
  static const VertexData s_CubePoints[];

  const IVertexBuffer* m_Vertexes;
  const IShaderProgram* m_Shader;
  const IMaterial* m_Material;

  math::Vector3<float> m_Translation;
  math::Vector3<units::Radian<float>> m_Rotation;

 public:
  Mesh(const IVertexBuffer* vertexes, const IShaderProgram* shader,
       const IMaterial* material);
  virtual ~Mesh() = default;

  Mesh(const Mesh& other) = default;
  Mesh(Mesh&& other) = default;

  Mesh& operator=(const Mesh& other) = default;
  Mesh& operator=(Mesh&& other) = default;

  const IVertexBuffer* Vertexes() const { return m_Vertexes; }
  const IShaderProgram* Shader() const { return m_Shader; }
  const IMaterial* Material() const { return m_Material; }

  const math::Vector3<float>& Translation() const { return m_Translation; }
  const math::Vector3<units::Radian<float>>& Rotation() const {
    return m_Rotation;
  }

  void Translation(const math::Vector3<float>& value) { m_Translation = value; }
  void Rotation(const math::Vector3<units::Radian<float>>& value) {
    m_Rotation = value;
  }

  static std::unique_ptr<IVertexBuffer> CreateCubeVertexes(
      const IRenderer* pRenderer);

  math::SquareMatrix4x4<float> ModelMatrix() const;
  math::SquareMatrix3x3<float> NormalMatrix() const;
};
}  // namespace ignosi::render
