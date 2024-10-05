#pragma once

#include <filesystem>
#include <string>

#include "ishader.h"

namespace ignosi::render {
class Shader : public IShader {
 private:
  std::filesystem::path m_ShaderLoc;
  std::string m_ShaderCode;

 protected:
  Shader(const std::filesystem::path& shaderLoc);

 public:
  virtual ~Shader() = default;

  const std::string& ShaderCode() const override { return m_ShaderCode; }
  const std::filesystem::path& ShaderLoc() const override {
    return m_ShaderLoc;
  }
};
}  // namespace ignosi::render
