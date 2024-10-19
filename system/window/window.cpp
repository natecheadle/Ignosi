#include "window.h"

#include <handle.h>
#include <pointer_handle_manager.h>

#include "detail/glfw_window.h"

using namespace ignosi::system;
using namespace ignosi::dll;

namespace {
using WindowHandleManager =
    PointerHandleManager<detail::IWindow, IgnosiWindowHandle>;
using InternalWindowHandle = WindowHandleManager::HANDLE_T;

WindowHandleManager HandleManager;
}  // namespace

IgnosiWindowHandle IgnosiWindowCreateGLFW(const IgnosiWindowSize &size) {
  if (!glfwInit()) {
    return {nullptr};
  }
  return HandleManager.AddObject(std::make_unique<detail::GLFWWindow>(size))
      .ExportValue();
}

void IgnosiWindowDestroy(IgnosiWindowHandle obj) {
  HandleManager.DestroyObject(obj);
}

void IgnosiWindowGLFWTerminate() { glfwTerminate(); }

IgnosiBool IgnosiWindowShouldClose(IgnosiWindowHandle obj) {
  return HandleManager.Execute<IgnosiBool>(
      obj, [](detail::IWindow *pWin) -> IgnosiBool {
        if (pWin) {
          return pWin->ShouldClose() ? IgnosiBool::True : IgnosiBool::False;
        }
        return IgnosiBool::True;
      });
}

void IgnosiWindowSwapBuffers(IgnosiWindowHandle obj) {
  HandleManager.ExecuteVoid(obj, [](detail::IWindow *pWin) -> void {
    if (pWin) {
      pWin->SwapBuffers();
    }
  });
}

void IgnosiWindowPollEvents(IgnosiWindowHandle obj) {
  HandleManager.ExecuteVoid(obj, [](detail::IWindow *pWin) -> void {
    if (pWin) {
      pWin->PollEvents();
    }
  });
}
