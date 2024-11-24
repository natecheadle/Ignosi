#include "geometry_opengl_shader.h"

#include <glad/glad.h>

namespace ignosi::render {
Geometry_OpenGL_Shader::Geometry_OpenGL_Shader(
    const std::filesystem::path& shaderLoc)
    : OpenGL_Shader(shaderLoc) {}

unsigned int Geometry_OpenGL_Shader::CreateGLShader() {
  return glCreateShader(GL_GEOMETRY_SHADER);
}
}  // namespace ignosi::render
