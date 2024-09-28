#include "entity.h"

#include "world.h"

namespace ignosi::ecs {

Entity::Entity(std::uint32_t id, World* pWorld) : m_ID(id), m_pWorld(pWorld) {}

void Entity::RegisterComponent(const IComponent& component) {
  m_Components[component.TypeID()] = true;
}

void Entity::RemoveComponent(const IComponent& component) {
  m_Components[component.TypeID()] = false;
}
IComponent* Entity::GetComponent(std::uint32_t id) const {
  return m_pWorld->GetComponent(*this, id);
}

std::uint32_t Entity::ID() const { return m_ID; }

const std::bitset<64>& Entity::RegisteredComponents() const {
  return m_Components;
}

bool operator==(const Entity& lhs, const Entity& rhs) {
  return lhs.m_ID == rhs.m_ID;
}

bool operator!=(const Entity& lhs, const Entity& rhs) {
  return lhs.m_ID != rhs.m_ID;
}

bool operator<(const Entity& lhs, const Entity& rhs) {
  return lhs.m_ID < rhs.m_ID;
}

bool operator<=(const Entity& lhs, const Entity& rhs) {
  return lhs.m_ID <= rhs.m_ID;
}

bool operator>(const Entity& lhs, const Entity& rhs) {
  return lhs.m_ID > rhs.m_ID;
}

bool operator>=(const Entity& lhs, const Entity& rhs) {
  return lhs.m_ID >= rhs.m_ID;
}
}  // namespace ignosi::ecs
