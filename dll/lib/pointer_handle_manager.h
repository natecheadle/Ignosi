#pragma once

#include <cassert>
#include <functional>
#include <memory>
#include <mutex>
#include <unordered_map>

#include "handle.h"

namespace ignosi::dll {

template <typename T, typename EXPORT_TYPE, typename MUTEX = std::mutex>
class PointerHandleManager {
 public:
  using HANDLE_T = Handle<EXPORT_TYPE, T*, nullptr>;

 private:
  mutable MUTEX m_DataMutex;
  std::unordered_map<void*, std::unique_ptr<T>> m_Objects;

 public:
  PointerHandleManager() = default;
  ~PointerHandleManager() = default;

  PointerHandleManager(const PointerHandleManager& other) = delete;
  PointerHandleManager(PointerHandleManager&& other) noexcept = default;

  PointerHandleManager& operator=(const PointerHandleManager& other) = delete;
  PointerHandleManager& operator=(PointerHandleManager&& other) noexcept =
      default;

  auto AddObject(std::unique_ptr<T> obj) -> HANDLE_T {
    std::scoped_lock lock(m_DataMutex);
    HANDLE_T handle = HANDLE_T::Create(obj.get());
    m_Objects.insert({handle.InternalValue(), std::move(obj)});
    return handle;
  }

  auto DestroyObject(HANDLE_T handle) -> bool {
    std::scoped_lock lock(m_DataMutex);
    return m_Objects.erase(handle.InternalValue()) > 0;
  }

  template <typename RETURN_TYPE>
  static auto Execute(HANDLE_T handle,
                      std::function<RETURN_TYPE(T*)> func) -> RETURN_TYPE {
    return func(static_cast<T*>(handle.InternalValue()));
  }

  static auto ExecuteVoid(HANDLE_T handle,
                          std::function<void(T*)> func) -> void {
    func(static_cast<T*>(handle.InternalValue()));
  }
};
}  // namespace ignosi::dll
