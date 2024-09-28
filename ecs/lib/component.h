#pragma once

#include <cstdint>

#include "type_id.h"

namespace ignosi::ecs {
class World;

class IComponent {
 public:
  virtual ~IComponent() = default;
  virtual std::uint32_t EntityID() const = 0;
  virtual std::uint32_t TypeID() const = 0;
};

template <typename T>
class Component : public IComponent {
  friend World;

  static const std::uint32_t m_TypeIDValue;
  std::uint32_t m_EntityID;

  Component(std::uint32_t entityID, T&& data)
      : m_EntityID(entityID), Data(std::forward<T>(data)) {}

  Component(std::uint32_t entityID, const T& data)
      : m_EntityID(entityID), Data(data) {}

 public:
  ~Component() override = default;

  std::uint32_t TypeID() const override { return m_TypeIDValue; }
  std::uint32_t EntityID() const override { return m_EntityID; }

  static std::uint32_t StaticTypeIDValue() { return m_TypeIDValue; }

  T Data;

  friend bool operator==(const Component& lhs, const Component& rhs) {
    return lhs.EntityID() == rhs.EntityID();
  }
};

template <typename T>
const std::uint32_t Component<T>::m_TypeIDValue =
    ecs::TypeID<IComponent>::template Value<T>();

}  // namespace ignosi::ecs
