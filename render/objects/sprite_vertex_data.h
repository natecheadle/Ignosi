#pragma once

#include <vector.hpp>

#include "vertex_data_config.h"

namespace ignosi::render {
struct SpriteVertexData {
  math::Vector2<float> Position;
  math::Vector2<float> TextureCoord;

  static VertexDataConfig describe() {
    static VertexDataConfig config;
    if (config.Describe().empty()) {
      config.PushBackConfig<float, 2>();
      config.PushBackConfig<float, 2>();
    }
    return config;
  }
};

static_assert(sizeof(SpriteVertexData) == sizeof(float) * 4,
              "SpriteVertexData must be tightly packed");
}  // namespace ignosi::render
