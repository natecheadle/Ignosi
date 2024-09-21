#pragma once

#include <new>
#include <utility>

#include "dll_object_pool.h"

namespace ignosi::memory {

template <typename T>
class DllObjectPool {
  IgnosiMemoryPool m_pPool;

 public:
  DllObjectPool(size_t poolSize)
      : m_pPool(IgnosiMemoryPoolCreate(sizeof(T), poolSize)) {}

  ~DllObjectPool() { IgnosiMemoryPoolDestroy(m_pPool); }

  T* Create(T&& obj) {
    void* pNew = IgnosiMemoryPoolAllocate(m_pPool);
    if (!pNew) {
      throw std::bad_alloc{};
    }

    try {
      return new (pNew) T(std::forward<T>(obj));
    } catch (...) {
      IgnosiMemoryPoolDeallocate(m_pPool, pNew);
      throw;
    }
    return nullptr;
  }

  T* Create(const T& obj) { return Create(T(obj)); }

  T* Create() { return Create(T()); }

  void Destroy(T* obj) noexcept {
    obj->~T();
    IgnosiMemoryPoolDeallocate(m_pPool, obj);
  }

  size_t PoolSize() const { return IgnosiMemoryPoolSize(m_pPool); }
  size_t AllocatedCount() const {
    return IgnosiMemoryPoolAllocatedCount(m_pPool);
  }
};

}  // namespace ignosi::memory
