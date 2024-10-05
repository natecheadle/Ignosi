#include "vertex_opengl_shader.h"

#include <glad/glad.h>

namespace ignosi::render {
Vertex_OpenGL_Shader::Vertex_OpenGL_Shader(
    const std::filesystem::path& shaderLoc)
    : OpenGL_Shader(shaderLoc) {}

unsigned int Vertex_OpenGL_Shader::CreateGLShader() {
  return glCreateShader(GL_VERTEX_SHADER);
}
}  // namespace ignosi::render
