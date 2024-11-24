#include <window/window.h>

using namespace ignosi::system;

int main(int argc, char** argv) {
  Window window({.Height = 800, .Width = 600});
  while (!window.ShouldClose()) {
    window.PollEvents();
    window.SwapBuffers();
  }
}
