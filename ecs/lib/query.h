#pragma once

#include <functional>
#include <memory>
#include <unordered_map>
#include <vector>

#include "entity.h"

namespace ignosi::ecs {

class Query {
  std::vector<Entity*> m_Result;
  std::function<bool(const Entity&)> m_Query;

 public:
  Query(std::function<bool(const Entity&)> query);
  void Run(const std::unordered_map<std::uint32_t, std::unique_ptr<Entity>>&
               allEntities);

  const std::vector<Entity*>& Result() const;
};
}  // namespace ignosi::ecs
