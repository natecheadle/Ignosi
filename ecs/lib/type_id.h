#pragma once

#include <cstdint>
#include <mutex>
#include <typeindex>
#include <unordered_map>

namespace ignosi::ecs {
template <typename T>
class TypeID {
 public:
  template <typename U>
  static std::uint32_t Value() {
    static std::mutex s_DataLock{};
    static std::uint32_t s_NextID = 0;
    static std::unordered_map<std::type_index, std::uint32_t> s_TypeIDLookup{};

    std::unique_lock<std::mutex> lock(s_DataLock);

    std::type_index index(typeid(U));
    auto it = s_TypeIDLookup.find(index);
    if (it == s_TypeIDLookup.end()) {
      std::uint32_t newID = s_NextID++;
      return s_TypeIDLookup.insert({index, newID}).second;
    }
    return it->second;
  }
};

}  // namespace ignosi::ecs
