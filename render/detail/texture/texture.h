#pragma once

#include "itexture.h"

namespace ignosi::render {
class Texture : public ITexture {
 private:
  const enum TextureUnit m_Unit;

 protected:
  Texture(enum TextureUnit unit);

 public:
  virtual ~Texture() = default;

  enum TextureUnit TextureUnit() const override;
};
}  // namespace ignosi::render
