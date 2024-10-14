#pragma once

#include <cstddef>

#include "window_size.h"

extern "C" {

void *IgnosiWindowCreateGLFW(const IgnosiWindowSize &size);
void IgnosiWindowDestroy(void *obj);
void IgnosiWindowGLFWTerminate();

int IgnosiWindowShouldClose(void *obj);
void IgnosiWindowSwapBuffers(void *obj);
void IgnosiWindowPollEvents(void *obj);
}

namespace ignosi::system {
inline void *CreateWindowGLFW(const IgnosiWindowSize &size) {
  return IgnosiWindowCreateGLFW(size);
}
inline void DestroyWindow(void *obj) { return IgnosiWindowDestroy(obj); }

inline bool ShouldWindowClose(void *obj) {
  return IgnosiWindowShouldClose(obj) != 0;
}

inline void WindowSwapBuffers(void *obj) { IgnosiWindowSwapBuffers(obj); }

inline void WindowPollEvents(void *obj) { IgnosiWindowPollEvents(obj); }

}  // namespace ignosi::system
