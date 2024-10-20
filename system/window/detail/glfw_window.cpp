#include "glfw_window.h"

#include <GLFW/glfw3.h>

namespace ignosi::system::detail {
GLFWWindow::GLFWWindow(const IgnosiWindowSize& size) {
  m_pWindow = glfwCreateWindow(size.Height, size.Width, "", nullptr, nullptr);
}

GLFWWindow::~GLFWWindow() {}

bool GLFWWindow::ShouldClose() const {
  return glfwWindowShouldClose(m_pWindow);
}

void GLFWWindow::SwapBuffers() { glfwSwapBuffers(m_pWindow); }

void GLFWWindow::PollEvents() { glfwPollEvents(); }

IgnosiWindowSize GLFWWindow::GetActualSize() const {
  IgnosiWindowSize rslt{0, 0};
  glfwGetWindowSize(m_pWindow, &rslt.Width, &rslt.Height);
  return rslt;
}
}  // namespace ignosi::system::detail
