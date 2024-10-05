#pragma once

#include <filesystem>

#include "texture/iimage_file.h"
#include "texture/texture.h"

namespace ignosi::render {
class OpenGL_Texture : public Texture {
 public:
 private:
  const unsigned int m_ID;
  const unsigned int m_UnitID;

 public:
  OpenGL_Texture(const std::filesystem::path& imagePath, enum TextureUnit unit);
  OpenGL_Texture(const IImageFile& image, enum TextureUnit unit);

  ~OpenGL_Texture() override;

  unsigned int GetID() const { return m_ID; }

  void Activate() const override;
  void Bind() const override;

 protected:
  static unsigned int CreateTexture();
  void InitializeFromImage(const IImageFile& image) const;

 private:
  static unsigned int TranslateTextureUnit(enum TextureUnit unit);
};
}  // namespace ignosi::render
