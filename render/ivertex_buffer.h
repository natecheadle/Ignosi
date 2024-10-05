#pragma once

namespace ignosi::render {
class IVertexBuffer {
 public:
  IVertexBuffer() = default;
  virtual ~IVertexBuffer() = default;

  virtual void Draw() const = 0;
};
}  // namespace ignosi::render
