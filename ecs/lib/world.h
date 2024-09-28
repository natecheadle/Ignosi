#pragma once

#include <allocate.h>

#include <array>
#include <atomic>
#include <cstdint>
#include <memory>
#include <object_pool.hpp>
#include <type_traits>
#include <unordered_map>
#include <vector>

#include "component.h"
#include "ecs_pointer.h"
#include "entity.h"
#include "query.h"
#include "system.h"

namespace ignosi::ecs {
class World {
  class PoolContainer {
   public:
    virtual ~PoolContainer() = default;
    virtual int TypeID() const = 0;
    virtual void Destroy(IComponent* pComponent) = 0;
  };

  template <typename T>
  class ComponentPoolContainer : public PoolContainer {
    memory::ConcreteObjectPool<Component<T>> m_Pool;

   public:
    ComponentPoolContainer(size_t defaultPoolSize) : m_Pool(defaultPoolSize) {}

    int TypeID() const { return Component<T>::StaticTypeIDValue(); }
    Component<T>* Create(const Entity& entity, T&& obj) {
      return m_Pool.Create(Component<T>(entity.ID(), std::forward<T>(obj)));
    }

    Component<T>* Create(const Entity& entity, const T& obj) {
      return m_Pool.Create(Component<T>(entity.ID(), obj));
    }

    void Destroy(Component<T>* pObj) { m_Pool.Destroy(pObj); }
    void Destroy(IComponent* pObj) {
      return Destroy(dynamic_cast<Component<T>*>(pObj));
    }
  };

  const size_t m_DefaultPoolSize;

  std::unordered_map<std::uint32_t, std::unique_ptr<Entity>> m_Entities;
  std::vector<std::unique_ptr<Query>> m_Queries;
  std::vector<std::unique_ptr<System>> m_Systems;
  std::atomic<std::uint32_t> m_NextID;

  std::unordered_map<std::uint32_t, std::unique_ptr<PoolContainer>> m_Pools;
  std::unordered_map<std::uint32_t, std::array<IComponent*, 64>>
      m_EntityComponents;

  std::vector<IComponent*> m_ComponentToFree;
  std::vector<Entity*> m_EntityToFree;
  std::vector<System*> m_SystemsToFree;
  std::vector<Query*> m_QueriesToFree;

 public:
  World(size_t defaultPoolSize);
  virtual ~World();

  void Process(double delta);

  ECSPointer<Entity> CreateEntity();

  template <typename T>
  void RegisterComponent() {
    if (m_Pools.find(Component<T>::StaticTypeIDValue()) == m_Pools.end()) {
      m_Pools.insert(
          {Component<T>::StaticTypeIDValue(),
           std::make_unique<ComponentPoolContainer<T>>(m_DefaultPoolSize)});
    }
  }

  ECSPointer<System> RegisterSystem(std::unique_ptr<System> system);

  IComponent* GetComponent(const Entity& entity, std::uint32_t componentID);

  const IComponent* GetComponent(const Entity& entity,
                                 std::uint32_t componentID) const;

  template <typename T>
  ECSPointer<T> RegisterSystem(std::unique_ptr<T> system) {
    static_assert(std::is_base_of_v<System, T>, "T must derive from System");

    ECSPointer<System> newSystem =
        RegisterSystem(std::unique_ptr<System>(system.release()));
    return ECSPointer<T>(reinterpret_cast<T*>(newSystem.release()),
                         [this](T* pObj) { queueFree(pObj); });
  }

  ECSPointer<Query> RegisterQuery(std::unique_ptr<Query> query);

  template <typename T>
  ECSPointer<Component<T>> CreateComponent(Entity& entity) {
    return CreateComponent<T>(entity, T());
  }

  template <typename T>
  ECSPointer<Component<T>> CreateComponent(Entity& entity, const T& value) {
    return CreateComponent<T>(entity, T(value));
  }

  template <typename T>
  ECSPointer<Component<T>> CreateComponent(Entity& entity, T&& value) {
    ComponentPoolContainer<T>* pPool =
        ((ComponentPoolContainer<T>*)m_Pools[Component<T>::StaticTypeIDValue()]
             .get());
    Component<T>* newComponent = pPool->Create(entity, std::forward<T>(value));

    Component<T>* pNew = newComponent;
    entity.RegisterComponent(*pNew);

    m_EntityComponents[entity.ID()][Component<T>::StaticTypeIDValue()] =
        newComponent;
    return ECSPointer<Component<T>>(
        pNew, [this](Component<T>* pObj) { queueFree(pObj); });
  }

 private:
  void queueFree(IComponent* toFree);
  void queueFree(Entity* toFree);
  void queueFree(Query* toFree);
  void queueFree(System* toFree);

  void freeAll();
};
}  // namespace ignosi::ecs
