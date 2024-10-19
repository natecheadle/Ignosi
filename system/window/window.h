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
void IgnosiWindowPollEvents(IgnosiWindowHandle obj);
}

namespace ignosi::system {
class IgnosiWindow {
  IgnosiWindowHandle m_Handle;

 public:
  inline IgnosiWindow(const IgnosiWindowSize &size)
      : m_Handle(IgnosiWindowCreateGLFW(size)) {}

  ~IgnosiWindow() { IgnosiWindowDestroy(m_Handle); }

  inline bool ShouldClose() const {
    return IgnosiWindowShouldClose(m_Handle) == IgnosiBool::True;
  }
  inline void SwapBuffers() { IgnosiWindowSwapBuffers(m_Handle); }

  inline void PollEvents() { IgnosiWindowPollEvents(m_Handle); }
};

}  // namespace ignosi::system
