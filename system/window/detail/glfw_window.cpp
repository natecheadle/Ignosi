#include "glfw_window.h"

namespace ignosi::system::detail {
GLFWWindow::GLFWWindow(const IgnosiWindowSize& size) {
  m_pWindow = glfwCreateWindow(size.Height, size.Width, "", nullptr, nullptr);
}

GLFWWindow::~GLFWWindow() {}

bool GLFWWindow::ShouldClose() const {
  return glfwWindowShouldClose(m_pWindow);
}

void GLFWWindow::SwapBuffers() const { glfwSwapBuffers(m_pWindow); }

void GLFWWindow::PollEvents() const { glfwPollEvents(); }

}  // namespace ignosi::system::detail
