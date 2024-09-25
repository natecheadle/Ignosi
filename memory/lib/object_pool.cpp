#include "object_pool.h"

#include "detail/object_pool_impl.h"

using namespace ignosi::memory::detail;

IgnosiMemoryPoolHandle IgnosiMemoryPoolCreate(size_t objectSize,
                                              size_t poolSize) {
  return new ObjectPoolImpl(objectSize, poolSize);
}

void IgnosiMemoryPoolDestroy(IgnosiMemoryPoolHandle obj) {
  delete static_cast<ObjectPoolImpl *>(obj);
}

void *IgnosiMemoryPoolAllocate(IgnosiMemoryPoolHandle pool) {
  if (!pool) {
    return nullptr;
  }

  return static_cast<ObjectPoolImpl *>(pool)->Allocate();
}

void IgnosiMemoryPoolFree(IgnosiMemoryPoolHandle pool, void *pObj) {
  if (!pool) {
    return;
  }

  static_cast<ObjectPoolImpl *>(pool)->Free(pObj);
}

size_t IgnosiMemoryPoolSize(IgnosiMemoryPoolHandle pool) {
  if (!pool) {
    return 0;
  }
  return static_cast<ObjectPoolImpl *>(pool)->PoolSize();
}

size_t IgnosiMemoryPoolAllocatedCount(IgnosiMemoryPoolHandle pool) {
  if (!pool) {
    return 0;
  }
  return static_cast<ObjectPoolImpl *>(pool)->AllocatedCount();
}
