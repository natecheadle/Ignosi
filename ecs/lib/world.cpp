#include "world.h"

#include <algorithm>
#include <cstdlib>
#include <memory>

#include "component.h"
#include "ecs_pointer.h"
#include "entity.h"
#include "query.h"

namespace ignosi::ecs {

World::World(size_t defaultPoolSize) : m_DefaultPoolSize(defaultPoolSize) {}

World::~World() { freeAll(); }

void World::Process(double delta) {
  for (const auto& query : m_Queries) {
    query->Run(m_Entities);
  }

  for (const auto& system : m_Systems) {
    system->Process(delta);
  }
  freeAll();
}

ECSPointer<Query> World::RegisterQuery(std::unique_ptr<Query> query) {
  Query* pNew = query.get();
  m_Queries.push_back(std::move(query));
  return ECSPointer<Query>(pNew, [this](Query* pObj) { queueFree(pObj); });
}

ECSPointer<System> World::RegisterSystem(std::unique_ptr<System> system) {
  System* pNew = system.get();
  m_Systems.push_back(std::move(system));
  std::sort(m_Systems.begin(), m_Systems.end(),
            [](const std::unique_ptr<System>& lhs,
               const std::unique_ptr<System>& rhs) {
              return lhs->Priority() < rhs->Priority();
            });
  return ECSPointer<System>(pNew, [this](System* pObj) { queueFree(pObj); });
}

IComponent* World::GetComponent(const Entity& entity,
                                std::uint32_t componentID) {
  return m_EntityComponents.at(entity.ID()).at(componentID);
}

const IComponent* World::GetComponent(const Entity& entity,
                                      std::uint32_t componentID) const {
  return m_EntityComponents.at(entity.ID()).at(componentID);
}

ECSPointer<Entity> World::CreateEntity() {
  std::unique_ptr<Entity> newEntity{new Entity(m_NextID++, this)};
  Entity* pEntity = newEntity.get();
  m_Entities.insert({pEntity->ID(), std::move(newEntity)});
  return ECSPointer<Entity>(pEntity, [this](Entity* pObj) { queueFree(pObj); });
}

void World::queueFree(IComponent* pToFree) {
  m_ComponentToFree.push_back(pToFree);
}

void World::queueFree(Entity* toFree) { m_EntityToFree.push_back(toFree); }

void World::queueFree(Query* toFree) { m_QueriesToFree.push_back(toFree); }

void World::queueFree(System* toFree) { m_SystemsToFree.push_back(toFree); }

void World::freeAll() {
  for (const auto& system : m_SystemsToFree) {
    auto it = std::find_if(m_Systems.begin(), m_Systems.end(),
                           [system](const std::unique_ptr<System>& sys) {
                             return sys.get() == system;
                           });
    m_Systems.erase(it);
  }

  for (const auto& query : m_QueriesToFree) {
    auto it = std::find_if(
        m_Queries.begin(), m_Queries.end(),
        [query](const std::unique_ptr<Query>& q) { return q.get() == query; });
    m_Queries.erase(it);
  }

  for (const auto& component : m_ComponentToFree) {
    m_Pools[component->TypeID()]->Destroy(
        m_EntityComponents[component->EntityID()][component->TypeID()]);
  }
  m_ComponentToFree.clear();

  for (const Entity* entity : m_EntityToFree) {
    m_EntityComponents.erase(entity->ID());
    m_Entities.erase(entity->ID());
  }
  m_EntityToFree.clear();
}
}  // namespace ignosi::ecs
