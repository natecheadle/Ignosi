#pragma once

#include <cstddef>

#include "window_size.h"

extern "C" {

SYSTEM_EXPORT_SPEC void *IgnosiWindowCreateGLFW(const IgnosiWindowSize &size);
SYSTEM_EXPORT_SPEC void IgnosiWindowDestroy(void *obj);
SYSTEM_EXPORT_SPEC void IgnosiWindowGLFWTerminate();

SYSTEM_EXPORT_SPEC int IgnosiWindowShouldClose(void *obj);
SYSTEM_EXPORT_SPEC void IgnosiWindowSwapBuffers(void *obj);
SYSTEM_EXPORT_SPEC void IgnosiWindowPollEvents(void *obj);
SYSTEM_EXPORT_SPEC IgnosiWindowSize IgnosiWindowGetActualSize(void *obj);
SYSTEM_EXPORT_SPEC float IgnosiWindowAspectRatio(const IgnosiWindowSize &size);
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

inline IgnosiWindowSize WindowGetSize(void *obj) {
  return IgnosiWindowGetActualSize(obj);
}

inline float WindowGetAspectRatio(IgnosiWindowSize &size) {
  return IgnosiWindowAspectRatio(size);
}

}  // namespace ignosi::system
