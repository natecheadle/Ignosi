#include "window.h"

#include "detail/glfw_window.h"

using namespace ignosi::system;

void *IgnosiWindowCreateGLFW(const IgnosiWindowSize &size) {
  if (!glfwInit()) {
    return nullptr;
  }
  return new detail::GLFWWindow(size);
}

void IgnosiWindowDestroy(void *obj) {
  if (obj) {
    delete static_cast<detail::IWindow *>(obj);
  }
}

void IgnosiWindowGLFWTerminate() { glfwTerminate(); }

int IgnosiWindowShouldClose(void *obj) {
  if (!obj) return -1;

  return static_cast<detail::IWindow *>(obj)->ShouldClose() ? 1 : 0;
}
void IgnosiWindowSwapBuffers(void *obj) {
  if (!obj) return;

  static_cast<detail::IWindow *>(obj)->SwapBuffers();
}
void IgnosiWindowPollEvents(void *obj) {
  if (!obj) return;

  static_cast<detail::IWindow *>(obj)->PollEvents();
}

IgnosiWindowSize IgnosiWindowGetActualSize(void *obj) {
  if (!obj) return IgnosiWindowSize{};

  return static_cast<detail::IWindow *>(obj)->GetActualSize();
}

float IgnosiWindowAspectRatio(const IgnosiWindowSize &size) {
  return static_cast<float>(size.Width) / static_cast<float>(size.Height);
}
