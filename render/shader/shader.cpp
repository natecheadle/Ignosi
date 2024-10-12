#include "shader.h"

#include <fmt/format.h>

#include <fstream>
#include <sstream>
#include <stdexcept>

namespace ignosi::render {
Shader::Shader(const std::filesystem::path& shaderLoc) {
  const std::ifstream shaderFile(shaderLoc);
  if (!shaderFile.is_open())
    throw std::invalid_argument(
        fmt::format("Shader file [{}] does not exist.", shaderLoc.string()));

  std::stringstream sstream;
  sstream << shaderFile.rdbuf();
  m_ShaderCode = sstream.str();
  m_ShaderLoc = shaderLoc;
}
}  // namespace ignosi::render
