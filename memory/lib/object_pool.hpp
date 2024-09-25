#pragma once

#include <new>
#include <utility>

#include "object_pool.h"

namespace ignosi::memory {

template <typename T>
class ConcreteObjectPool {
  ObjectPool m_Pool;

 public:
  ConcreteObjectPool(size_t poolSize)
      : m_Pool(ObjectPool(sizeof(T), poolSize)) {}

  ~ConcreteObjectPool() = default;

  T *Create(T &&obj) {
    void *pNew = m_Pool.Allocate();
    if (!pNew) {
      throw std::bad_alloc{};
    }

    try {
      return new (pNew) T(std::forward<T>(obj));
    } catch (...) {
      m_Pool.Free(pNew);
      throw;
    }
    return nullptr;
  }

  T *Create(const T &obj) { return Create(T(obj)); }

  T *Create() { return Create(T()); }

  void Destroy(T *obj) noexcept {
    obj->~T();
    m_Pool.Free(obj);
  }

  size_t PoolSize() const { return m_Pool.PoolSize(); }
  size_t AllocatedCount() const { return m_Pool.AllocatedCount(); }
};

}  // namespace ignosi::memory
