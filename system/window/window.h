#pragma once

#include <bool.h>

#include <cstddef>

#include "window_size.h"

extern "C" {

struct IgnosiWindowHandle {
  void *Value;
};

IgnosiWindowHandle IgnosiWindowCreateGLFW(const IgnosiWindowSize &size);
void IgnosiWindowDestroy(IgnosiWindowHandle obj);
void IgnosiWindowGLFWTerminate();

IgnosiBool IgnosiWindowShouldClose(const IgnosiWindowHandle obj);
void IgnosiWindowSwapBuffers(IgnosiWindowHandle obj);
IgnosiWindowSize IgnosiWindowGetActualSize(const IgnosiWindowHandle obj);
float IgnosiWindowGetAspectRatio(const IgnosiWindowSize &size);
void IgnosiWindowPollEvents(IgnosiWindowHandle obj);
}

namespace ignosi::system {
class Window {
  IgnosiWindowHandle m_Handle;

 public:
  inline Window() : m_Handle(nullptr) {}
  inline Window(const IgnosiWindowSize &size)
      : m_Handle(IgnosiWindowCreateGLFW(size)) {}

  inline ~Window() { IgnosiWindowDestroy(m_Handle); }

  Window(const Window &other) = delete;
  Window(Window &&other) noexcept = default;

  Window &operator=(const Window &other) = delete;
  Window &operator=(Window &&other) noexcept = default;

  inline bool ShouldClose() const {
    return IgnosiWindowShouldClose(m_Handle) == IgnosiBool::True;
  }
  inline void SwapBuffers() { IgnosiWindowSwapBuffers(m_Handle); }

  inline void PollEvents() { IgnosiWindowPollEvents(m_Handle); }

  inline IgnosiWindowSize GetActualSize() const {
    return IgnosiWindowGetActualSize(m_Handle);
  }
  inline static float GetAspectRatio(IgnosiWindowSize &size) {
    return IgnosiWindowGetAspectRatio(size);
  }
};

}  // namespace ignosi::system
