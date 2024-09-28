#include "query.h"

#include "entity.h"

namespace ignosi::ecs {

Query::Query(std::function<bool(const Entity&)> query)
    : m_Query(std::move(query)) {}

void Query::Run(
    const std::unordered_map<std::uint32_t, std::unique_ptr<Entity>>&
        allEntities) {
  m_Result.clear();
  m_Result.reserve(allEntities.size());

  for (const std::pair<const std::uint32_t, std::unique_ptr<Entity>>& entity :
       allEntities) {
    if (m_Query(*entity.second)) {
      m_Result.push_back(entity.second.get());
    }
  }
}

const std::vector<Entity*>& Query::Result() const { return m_Result; }
}  // namespace ignosi::ecs
