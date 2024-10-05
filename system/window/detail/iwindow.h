#pragma once

#include "window/window_size.h"

namespace ignosi::system::detail {
class IWindow {
 public:
  virtual ~IWindow() = default;

  virtual bool ShouldClose() const = 0;
  virtual void SwapBuffers() const = 0;
  virtual void PollEvents() const = 0;
  virtual IgnosiWindowSize GetActualSize() const = 0;
};
}  // namespace ignosi::system::detail
