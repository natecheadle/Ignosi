#include "new.h"

#include <cstdlib>
#include <new>

#include "allocate.h"

using std::bad_alloc;
using namespace ignosi::memory;

void *operator new(std::size_t size) {
  if (size == 0) {
    size++;  // avoid malloc(0)
  }

  if (void *pNew = Allocate(size)) {
    return pNew;
  }

  throw bad_alloc{};
}

void *operator new[](std::size_t size) {
  if (size == 0) {
    size++;  // avoid malloc(0)
  }

  if (void *pNew = Allocate(size)) {
    return pNew;
  }

  throw bad_alloc{};
}

void operator delete(void *ptr) noexcept { Free(ptr); }

void operator delete[](void *ptr) noexcept { Free(ptr); }
