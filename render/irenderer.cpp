#include "irenderer.h"

#include "opengl/opengl_renderer.h"

namespace ignosi::render {
std::unique_ptr<IRenderer> IRenderer::Create() {
  return std::make_unique<OpenGL_Renderer>();
}
}  // namespace ignosi::render
