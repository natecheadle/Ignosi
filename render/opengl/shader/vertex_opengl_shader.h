#pragma once

#include "opengl_shader.h"

namespace ignosi::render {
class Vertex_OpenGL_Shader : public OpenGL_Shader {
 public:
  Vertex_OpenGL_Shader(const std::filesystem::path& shaderLoc);

  ShaderType Type() const override { return ShaderType::Vertex; };

 protected:
  unsigned int CreateGLShader() override;
};
}  // namespace ignosi::render
