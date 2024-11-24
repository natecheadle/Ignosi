#include "texture.h"

namespace ignosi::render {
Texture::Texture(enum TextureUnit unit) : m_Unit(unit) {}

TextureUnit Texture::TextureUnit() const { return m_Unit; }

}  // namespace ignosi::render
