#include <window/window.h>

using namespace ignosi::system;

int main(int argc, char** argv) {
  IgnosiWindow window({.Height = 800, .Width = 600});
  while (!window.ShouldClose()) {
    window.PollEvents();
    window.SwapBuffers();
  }
}
