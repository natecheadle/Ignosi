#pragma once

namespace ignosi::memory {
class IObjectPool {
 public:
  virtual void *Allocate() = 0;
  virtual void Free(void *pObj) = 0;

  virtual size_t PoolSize() const = 0;
  virtual size_t AllocatedCount() const = 0;
};
}  // namespace ignosi::memory
