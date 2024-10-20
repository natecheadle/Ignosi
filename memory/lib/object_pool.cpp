#include "object_pool.h"

#include <handle.h>
#include <pointer_handle_manager.h>

#include "detail/object_pool_impl.h"

using namespace ignosi::memory::detail;
using namespace ignosi::dll;

namespace {
using ObjectPoolHandleManager =
    PointerHandleManager<ObjectPoolImpl, IgnosiMemoryPoolHandle>;
using InternalObjectPoolHandle = ObjectPoolHandleManager::HANDLE_T;

ObjectPoolHandleManager HandleManager;
}  // namespace

IgnosiMemoryPoolHandle IgnosiMemoryPoolCreate(size_t objectSize,
                                              size_t poolSize) {
  return HandleManager
      .AddObject(std::make_unique<ObjectPoolImpl>(objectSize, poolSize))
      .ExportValue();
}

void IgnosiMemoryPoolDestroy(IgnosiMemoryPoolHandle obj) {
  HandleManager.DestroyObject(obj);
}

void *IgnosiMemoryPoolAllocate(IgnosiMemoryPoolHandle pool) {
  return HandleManager.Execute<void *>(pool,
                                       [](ObjectPoolImpl *pPool) -> void * {
                                         if (pPool) {
                                           return pPool->Allocate();
                                         }

                                         return nullptr;
                                       });
}

void IgnosiMemoryPoolFree(IgnosiMemoryPoolHandle pool, void *pObj) {
  HandleManager.ExecuteVoid(pool, [&](ObjectPoolImpl *pPool) {
    if (pPool) {
      return pPool->Free(pObj);
    }
  });
}
size_t IgnosiMemoryPoolSize(IgnosiMemoryPoolHandle pool) {
  return HandleManager.Execute<size_t>(pool,
                                       [](ObjectPoolImpl *pPool) -> size_t {
                                         if (pPool) {
                                           return pPool->PoolSize();
                                         }

                                         return 0;
                                       });
}

size_t IgnosiMemoryPoolAllocatedCount(IgnosiMemoryPoolHandle pool) {
  return HandleManager.Execute<size_t>(pool,
                                       [](ObjectPoolImpl *pPool) -> size_t {
                                         if (pPool) {
                                           return pPool->AllocatedCount();
                                         }

                                         return 0;
                                       });
}
