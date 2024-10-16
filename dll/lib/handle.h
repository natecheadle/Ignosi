#pragma once

#include <limits>

namespace ignosi::dll {
template <typename EXPORT_TYPE, typename UNDERLYING_TYPE,
          UNDERLYING_TYPE DefaultValue>
class Handle {
  UNDERLYING_TYPE m_Value{DefaultValue};

  Handle() = default;
  Handle(UNDERLYING_TYPE value) : m_Value(value) {}

 public:
  Handle(const Handle& other) = default;
  Handle(Handle&& other) noexcept = default;

  Handle& operator=(const Handle& other) = default;
  Handle& operator=(Handle&& other) noexcept = default;

  static auto Create(UNDERLYING_TYPE value) -> Handle { return Handle(value); }
  static auto Create(EXPORT_TYPE value) -> Handle {
    return Handle(value.Value);
  }
  static auto CreateInvalid() -> Handle { return Handle(); }

  auto IsValid() const -> bool { return m_Value != DefaultValue; }
  auto InternalValue() const -> UNDERLYING_TYPE { return m_Value; }
  auto ExportValue() const -> EXPORT_TYPE { return {m_Value}; }

  void Reset() { m_Value = DefaultValue; }
};

}  // namespace ignosi::dll

#ifndef DECLARE_POINTER_HANDLE
#define DECLARE_POINTER_HANDLE(name, T) \
                                        \
  struct name {                         \
    void* Value;                        \
  };                                    \
  using name##_Handle = Handle<name, T*, nullptr>;

#endif

#ifndef DECLARE_INDEX_HANDLE
#define DECLARE_INDEX_HANDLE(name) \
                                   \
  struct name {                    \
    size_t Value;                  \
  };                               \
  using name##_Handle =            \
      Handle<name, size_t, std::numeric_limits<size_t>::max()>;

#endif
