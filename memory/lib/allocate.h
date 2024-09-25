#pragma once

#include <cstddef>

extern "C" {
MEMORY_EXPORT_SPEC void *IgnosiMemoryAllocate(size_t size);
MEMORY_EXPORT_SPEC void IgnosiMemoryFree(void *obj);
}

namespace ignosi::memory {
inline void *Allocate(size_t size) { return IgnosiMemoryAllocate(size); }
inline void Free(void *obj) { return IgnosiMemoryFree(obj); }
}  // namespace ignosi::memory
