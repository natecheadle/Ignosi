#include <fmt/format.h>
#include <gtest/gtest.h>

#include <cassert>
#include <future>
#include <iostream>
#include <memory>
#include <object_pool.hpp>
#include <vector>

#include "object_pool.h"

namespace ignosi::memory::test {
namespace {
struct Data {
  Data() {}

  Data(size_t value1, double value2) : Value1(value1), Value2(value2) {}

  size_t Value1{0};
  double Value2{0.0};

  friend bool operator==(const Data &lhs, const Data &rhs) = default;

  friend std::ostream &operator<<(std::ostream &os, const Data &value) {
    os << fmt::format("Value1: {} Value2: {}", value.Value1, value.Value2);
    return os;
  }

  static void *operator new(std::size_t count) {
    assert(sizeof(Data) == count);
    return s_ObjectPool.Allocate();
  }

  static void *operator new(std::size_t count, void *ptr) {
    assert(sizeof(Data) == count);
    return ptr;
  }

  static void operator delete(void *pObj) { return s_ObjectPool.Free(pObj); }

  static std::size_t AllocatedObjectCount() {
    return s_ObjectPool.AllocatedCount();
  }

  static std::size_t PoolSize() { return s_ObjectPool.PoolSize(); }

  static constexpr size_t kPoolSize = 4;

 private:
  static ObjectPool s_ObjectPool;
};
ObjectPool Data::s_ObjectPool{sizeof(Data), Data::kPoolSize};

}  // namespace

class DllObjectPoolFixture : public testing::Test {
 public:
  DllObjectPoolFixture() {}

 protected:
  std::vector<Data> m_ExpectedData;
  std::vector<std::unique_ptr<Data>> m_ActualData;

  void fillData(size_t fillSize) {
    for (size_t i = 0; i < fillSize; ++i) {
      m_ExpectedData.push_back(Data(i, (double)i * (double)i));
      m_ActualData.push_back(std::make_unique<Data>(m_ExpectedData.back()));
      ASSERT_EQ(Data::AllocatedObjectCount(), i + 1);
    }
  }

  void validateData() {
    ASSERT_EQ(m_ExpectedData.size(), m_ActualData.size());
    for (size_t i = 0; i < m_ExpectedData.size(); ++i) {
      ASSERT_NE(m_ActualData[i], nullptr);
      ASSERT_EQ(*m_ActualData[i], m_ExpectedData[i]);
    }
  }

  void clearData() {
    m_ExpectedData.clear();
    m_ActualData.clear();
  }
};

TEST_F(DllObjectPoolFixture, ValidateConstruction) {}

TEST_F(DllObjectPoolFixture, ValidateCreateDestroyPool) {
  ConcreteObjectPool<Data> pool(10);
  auto pNewObj = pool.Create();
  auto pNewObj1 = pool.Create(Data(1, 2.0));
  ASSERT_EQ(*pNewObj, Data());
  ASSERT_EQ(*pNewObj1, Data(1, 2.0));

  ASSERT_EQ(pool.AllocatedCount(), 2);
  pool.Destroy(pNewObj);
  pool.Destroy(pNewObj1);
  ASSERT_EQ(pool.AllocatedCount(), 0);
}

TEST_F(DllObjectPoolFixture, ValidatePoolSize) {
  ASSERT_EQ(Data::PoolSize(), Data::kPoolSize);
}

TEST_F(DllObjectPoolFixture, ValidateAllocatedCount) {
  fillData(Data::kPoolSize);
}

TEST_F(DllObjectPoolFixture, ValidateCreateDestroyTillFull) {
  fillData(Data::kPoolSize);
  validateData();
}

TEST_F(DllObjectPoolFixture, ValidateCreateDestroyTillFullMultiple) {
  for (int j = 0; j < 2; ++j) {
    fillData(Data::kPoolSize);
    validateData();
    clearData();
  }
}

TEST_F(DllObjectPoolFixture, ValidateCreateDestroyReverseOrder) {
  for (int j = 0; j < 2; ++j) {
    fillData(Data::kPoolSize);
    for (auto it = m_ActualData.rbegin(); it != m_ActualData.rend(); ++it) {
      it->reset();
    }
    clearData();
  }
}

TEST_F(DllObjectPoolFixture, ValidateCreateDestroyOutOfOrder) {
  for (int j = 0; j < 2; ++j) {
    fillData(Data::kPoolSize);
    validateData();
    for (size_t i = 0; i < m_ActualData.size(); ++i) {
      if (i % 2 == 0) {
        m_ActualData[i].reset();
      }
    }

    for (size_t i = 0; i < m_ActualData.size(); ++i) {
      m_ActualData[i] = std::make_unique<Data>(i, (double)i * (double)i);
    }
    validateData();

    clearData();
  }
}

TEST_F(DllObjectPoolFixture, ValidateCreateDestroyTillFullMultipleThreads) {
  auto createDestroy = [&]() -> bool {
    try {
      std::vector<std::unique_ptr<Data>> objs;

      for (size_t i = 0; i < Data::kPoolSize / 2; ++i) {
        objs.push_back(std::make_unique<Data>(i, (double)i));
      }
      for (auto &obj : objs) {
        if (obj == nullptr) {
          return false;
        }
      }
    } catch (...) {
      return false;
    }
    return true;
  };

  for (int i = 0; i < 5; ++i) {
    std::future thread1 = std::async(createDestroy);
    std::future thread2 = std::async(createDestroy);

    ASSERT_TRUE(thread1.get());
    ASSERT_TRUE(thread2.get());
  }
}

TEST_F(DllObjectPoolFixture, ValidateCreateDestroyPastFull) {
  fillData(Data::kPoolSize * 4);
  validateData();
}

TEST_F(DllObjectPoolFixture, ValidateCreateDestroyOutOfOrderPastFull) {
  for (size_t i = 0; i < 2; ++i) {
    fillData(Data::kPoolSize * 4);
    validateData();
    for (size_t j = 0; j < m_ActualData.size(); ++j) {
      if (j % 2 == 0) {
        m_ActualData[j].reset();
      }
    }

    clearData();
  }
}

TEST_F(DllObjectPoolFixture, ValidateCreateDestroyPastFullMultipleThreads) {
  auto createDestroy = [&]() -> bool {
    try {
      std::vector<std::unique_ptr<Data>> objs;

      for (size_t i = 0; i < Data::kPoolSize * 2; ++i) {
        objs.push_back(std::make_unique<Data>(i, (double)i));
      }
      for (auto &obj : objs) {
        if (obj == nullptr) {
          return false;
        }
      }
    } catch (...) {
      return false;
    }
    return true;
  };

  for (int i = 0; i < 5; ++i) {
    std::future thread1 = std::async(createDestroy);
    std::future thread2 = std::async(createDestroy);

    ASSERT_TRUE(thread1.get());
    ASSERT_TRUE(thread2.get());
  }
}

}  // namespace ignosi::memory::test
