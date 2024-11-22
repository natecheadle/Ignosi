#pragma once
#include <window/window.h>

struct IgnosiRendererHandle {
  void *Value;
};

extern "C" {
IgnosiRendererHandle IgnosiRendererCreate();
void IgnosiRendererDestroy(IgnosiRendererHandle obj);
}
