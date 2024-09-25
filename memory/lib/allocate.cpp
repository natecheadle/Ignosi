#include "allocate.h"

#include <cstdlib>

void *IgnosiMemoryAllocate(size_t size) { return std::malloc(size); }

void IgnosiMemoryFree(void *obj) { return std::free(obj); }
