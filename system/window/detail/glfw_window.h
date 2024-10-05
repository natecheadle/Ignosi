#pragma once

#include <GLFW/glfw3.h>

#include "../window_size.h"
#include "iwindow.h"

namespace ignosi::system::detail {
class GLFWWindow : public IWindow {
  GLFWwindow* m_pWindow;

 public:
  GLFWWindow(const IgnosiWindowSize& size);
  ~GLFWWindow() override;

  bool ShouldClose() const override;
  void SwapBuffers() const override;
  void PollEvents() const override;
  IgnosiWindowSize GetActualSize() const override;
};
}  // namespace ignosi::system::detail
