#include "compute_opengl_shader.h"

#include <glad/glad.h>

namespace ignosi::render {
Compute_OpenGL_Shader::Compute_OpenGL_Shader(
    const std::filesystem::path& shaderLoc)
    : OpenGL_Shader(shaderLoc) {}

unsigned int Compute_OpenGL_Shader::CreateGLShader() {
  return glCreateShader(GL_COMPUTE_SHADER);
}
}  // namespace ignosi::render
