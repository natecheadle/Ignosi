#pragma once

#include <vector.hpp>

#include "vertex_data_config.h"

namespace ignosi::render {
struct VertexData {
  math::Vector3<float> Position;
  math::Vector3<float> Normal;
  math::Vector2<float> TextureCoord;
  math::Vector3<float> TextureTangent;
  math::Vector3<float> TextureBitangent;

  static VertexDataConfig describe() {
    static VertexDataConfig config;
    if (config.Describe().empty()) {
      config.PushBackConfig<float, 3>();
      config.PushBackConfig<float, 3>();
      config.PushBackConfig<float, 2>();
      config.PushBackConfig<float, 3>();
      config.PushBackConfig<float, 3>();
    }
    return config;
  }
};

static_assert(sizeof(VertexData) == sizeof(float) * 14,
              "VertexData must be tightly packed");
}  // namespace ignosi::render
