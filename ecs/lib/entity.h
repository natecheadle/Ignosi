#pragma once

#include <bitset>
#include <cstdint>

#include "component.h"

namespace ignosi::ecs {

class World;

class Entity {
  friend World;

  std::bitset<64> m_Components;
  std::uint32_t m_ID;
  World* m_pWorld;

  Entity(std::uint32_t id, World* pWorld);

  void RegisterComponent(const IComponent& component);
  void RemoveComponent(const IComponent& component);
  IComponent* GetComponent(std::uint32_t id) const;

 public:
  std::uint32_t ID() const;

  const std::bitset<64>& RegisteredComponents() const;

  template <typename T>
  bool HasComponent() const {
    return RegisteredComponents()[Component<T>::StaticTypeIDValue()];
  }

  template <typename T>
  T* GetComponent() const {
    Component<T>* pComponent = dynamic_cast<Component<T>*>(
        GetComponent(Component<T>::StaticTypeIDValue()));
    return pComponent ? &pComponent->Data : nullptr;
  }

  friend bool operator==(const Entity& lhs, const Entity& rhs);
  friend bool operator!=(const Entity& lhs, const Entity& rhs);
  friend bool operator<(const Entity& lhs, const Entity& rhs);
  friend bool operator<=(const Entity& lhs, const Entity& rhs);
  friend bool operator>(const Entity& lhs, const Entity& rhs);
  friend bool operator>=(const Entity& lhs, const Entity& rhs);
};
}  // namespace ignosi::ecs
