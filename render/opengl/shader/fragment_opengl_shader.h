#pragma once

#include "opengl_shader.h"

namespace ignosi::render {
class Fragment_OpenGL_Shader : public OpenGL_Shader {
 public:
  Fragment_OpenGL_Shader(const std::filesystem::path& shaderLoc);

  ShaderType Type() const override { return ShaderType::Fragment; };

 protected:
  unsigned int CreateGLShader() override;
};
}  // namespace ignosi::render
