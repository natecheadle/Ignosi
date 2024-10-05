#include "fragment_opengl_shader.h"

#include <glad/glad.h>

namespace ignosi::render {
Fragment_OpenGL_Shader::Fragment_OpenGL_Shader(
    const std::filesystem::path& shaderLoc)
    : OpenGL_Shader(shaderLoc) {}

unsigned int Fragment_OpenGL_Shader::CreateGLShader() {
  return glCreateShader(GL_FRAGMENT_SHADER);
}
}  // namespace ignosi::render
