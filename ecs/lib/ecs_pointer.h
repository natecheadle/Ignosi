#pragma once

#include <functional>
#include <memory>

namespace ignosi::ecs {
template <typename T>
using ECSPointer = std::unique_ptr<T, std::function<void(T*)>>;
}
