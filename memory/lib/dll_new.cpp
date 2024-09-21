#include "dll_new.h"

#include <cstdlib>
#include <new>

#include "dll_allocate.h"

using std::bad_alloc;

void* operator new(std::size_t size) {
  if (size == 0) {
    size++;  // avoid malloc(0)
  }

  if (void* pNew = IgnosiMemoryAllocate(size)) {
    return pNew;
  }

  throw bad_alloc{};
}

void* operator new[](std::size_t size) {
  if (size == 0) {
    size++;  // avoid malloc(0)
  }

  if (void* pNew = IgnosiMemoryAllocate(size)) {
    return pNew;
  }

  throw bad_alloc{};
}

void operator delete(void* ptr) noexcept { IgnosiMemoryDeallocate(ptr); }

void operator delete[](void* ptr) noexcept { IgnosiMemoryDeallocate(ptr); }
