#pragma once

#include <cstdint>

namespace ignosi::ecs {

class System {
 public:
  virtual ~System() = default;
  virtual void Process(double delta) = 0;
  virtual std::uint32_t Priority() const = 0;
};
}  // namespace ignosi::ecs
