#pragma once

#include <atomic>
#include <boost/lockfree/stack.hpp>
#include <memory>

#include "../i_object_pool.h"

namespace ignosi::memory::detail {

class ObjectPoolImpl : public IObjectPool {
  const size_t m_ObjectSize;
  const size_t m_PoolSize;

  boost::lockfree::stack<void *> m_FreeObjects;
  boost::lockfree::stack<std::shared_ptr<std::uint8_t[]>> m_Buffers;

  std::atomic<size_t> m_AllocatedCount{0};
  std::atomic<size_t> m_BuffersSize{0};

 public:
  ObjectPoolImpl(size_t objectSize, size_t poolSize);
  ~ObjectPoolImpl() = default;

  ObjectPoolImpl(const ObjectPoolImpl &other) = delete;
  ObjectPoolImpl(ObjectPoolImpl &&other) noexcept = delete;

  ObjectPoolImpl &operator=(const ObjectPoolImpl &other) = delete;
  ObjectPoolImpl &operator=(ObjectPoolImpl &&other) noexcept = delete;

  void *Allocate() override;
  void Free(void *pObj) override;

  size_t PoolSize() const override;
  size_t AllocatedCount() const override;

 private:
  void initializeNewBufferBlock();
};

}  // namespace ignosi::memory::detail
