#pragma once

#include <cassert>
#include <cstddef>
#include <optional>
#include <vector>

namespace ignosi::container {
template <typename T, typename Allocator = std::allocator<std::optional<T>>>
class RingBuffer {
  std::vector<std::optional<T>, Allocator> m_Data;
  std::size_t m_Head;
  std::size_t m_Tail;

 public:
  RingBuffer() : m_Data(), m_Head(0), m_Tail(0) {}
  RingBuffer(std::size_t size) : RingBuffer() { m_Data.resize(size + 1); }

  void Push(T&& value) {
    if (Size() == m_Data.size() - 1) {
      Reserve((m_Data.size() - 1) * 2);
    }
    m_Data[m_Tail].emplace(std::forward<T>(value));
    m_Tail = (m_Tail + 1) % m_Data.size();
  }

  void Push(const T& value) {
    if (Size() == m_Data.size() - 1) {
      Reserve((m_Data.size() - 1) * 2);
    }
    m_Data[m_Tail].emplace(value);
    m_Tail = (m_Tail + 1) % m_Data.size();
  }

  T Pop() {
    assert(!Empty());
    std::size_t head = m_Head;
    m_Head = (m_Head + 1) % m_Data.size();

    return std::move(m_Data[head].value());
  }

  bool Empty() const { return m_Head == m_Tail; }

  std::size_t Size() const {
    if (m_Tail < m_Head) {
      return m_Tail + m_Data.size() - m_Head;
    }
    return m_Tail - m_Head;
  }

  void Reserve(std::size_t size) {
    if (size <= m_Data.size()) {
      return;
    }

    std::vector<std::optional<T>> newData(size + 1);

    for (size_t i = 0; i < this->Size(); ++i) {
      newData[i] = std::move(m_Data[(m_Head + i) % m_Data.size()]);
    }
    m_Tail = this->Size();
    m_Head = 0;
    m_Data = std::move(newData);
  }

  void MaxSize() const { return m_Data.size() - 1; }
};
}  // namespace ignosi::container
