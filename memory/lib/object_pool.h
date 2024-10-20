#pragma once

#include <cstddef>

#include "i_object_pool.h"

struct IgnosiMemoryPoolHandle {
  void *Value;
};

extern "C" {
IgnosiMemoryPoolHandle IgnosiMemoryPoolCreate(size_t objectSize,
                                              size_t poolSize);
void IgnosiMemoryPoolDestroy(IgnosiMemoryPoolHandle obj);
void *IgnosiMemoryPoolAllocate(IgnosiMemoryPoolHandle pool);
void IgnosiMemoryPoolFree(IgnosiMemoryPoolHandle pool, void *pObj);
size_t IgnosiMemoryPoolSize(IgnosiMemoryPoolHandle pool);
size_t IgnosiMemoryPoolAllocatedCount(IgnosiMemoryPoolHandle pool);
}

namespace ignosi::memory {
class ObjectPool : IObjectPool {
  IgnosiMemoryPoolHandle m_Handle;

 public:
  inline ObjectPool(size_t objectSize, size_t poolSize)
      : m_Handle(IgnosiMemoryPoolCreate(objectSize, poolSize)) {}

  inline ~ObjectPool() { IgnosiMemoryPoolDestroy(m_Handle); }

  inline void *Allocate() override {
    return IgnosiMemoryPoolAllocate(m_Handle);
  }

  inline void Free(void *pObj) override {
    return IgnosiMemoryPoolFree(m_Handle, pObj);
  }

  inline size_t PoolSize() const override {
    return IgnosiMemoryPoolSize(m_Handle);
  }

  inline size_t AllocatedCount() const override {
    return IgnosiMemoryPoolAllocatedCount(m_Handle);
  }
};
}  // namespace ignosi::memory
