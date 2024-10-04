#include <window/window.h>

using namespace ignosi::system;

int main(int argc, char** argv) {
  void* window = CreateWindowGLFW({.Height = 800, .Width = 600});
  while (!ShouldWindowClose(window)) {
    WindowPollEvents(window);
    WindowSwapBuffers(window);
  }
  DestroyWindow(window);
}
