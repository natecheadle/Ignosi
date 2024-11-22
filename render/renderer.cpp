#include "renderer.h"

#include <handle.h>
#include <pointer_handle_manager.h>

#include "irenderer.h"

using namespace ignosi::render;
using namespace ignosi::dll;

namespace {
using RendererHandleManager =
    PointerHandleManager<IRenderer, IgnosiRendererHandle>;
using InternalRendererHandle = RendererHandleManager::HANDLE_T;

RendererHandleManager HandleManager;
}  // namespace

IgnosiRendererHandle IgnosiRendererCreate() {
  return HandleManager.AddObject(IRenderer::Create()).ExportValue();
}

void IgnosiRendererDestroy(IgnosiRendererHandle obj) {
  HandleManager.DestroyObject(obj);
}
