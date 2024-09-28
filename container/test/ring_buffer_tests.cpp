#include <gtest/gtest.h>

#include <ring_buffer.hpp>

namespace ignosi::container::test {
struct TestStruct {
  TestStruct(int value1, double value2) : Value1(value1), Value2(value2) {}

  TestStruct(TestStruct&& other) = default;
  TestStruct& operator=(TestStruct&& other) = default;

  TestStruct(const TestStruct& other) = default;
  TestStruct& operator=(const TestStruct& other) = default;

  friend bool operator==(const TestStruct& lhs,
                         const TestStruct& rhs) = default;

  int Value1;
  double Value2;
};

class RingBufferFixture : public testing::Test {
 protected:
  RingBuffer<int> m_Data{10};
};

TEST_F(RingBufferFixture, ValidateInitialization) {}

TEST_F(RingBufferFixture, ValidateInitiallyEmpty) {
  ASSERT_TRUE(m_Data.empty());
}

TEST_F(RingBufferFixture, ValidatePushPop) {
  m_Data.push(1);
  ASSERT_EQ(m_Data.size(), 1);
  ASSERT_EQ(m_Data.pop(), 1);
  ASSERT_TRUE(m_Data.empty());
}

TEST_F(RingBufferFixture, ValidatePushPopPastEnd) {
  for (int i = 0; i < 20; ++i) {
    m_Data.push(i);
    ASSERT_EQ(m_Data.size(), 1);
    ASSERT_EQ(m_Data.pop(), i);
  }
}

TEST_F(RingBufferFixture, ValidatePushPastEnd) {
  for (int i = 0; i < 20; ++i) {
    m_Data.push(i);
    ASSERT_EQ(m_Data.size(), i + 1);
  }

  for (int i = 0; i < 20; ++i) {
    ASSERT_EQ(m_Data.pop(), i);
    ASSERT_EQ(m_Data.size(), 20 - i - 1);
  }
}

TEST_F(RingBufferFixture, ValidatePushCopy) {
  RingBuffer<TestStruct> buffer(10);
  for (int i = 0; i < 20; ++i) {
    TestStruct newStr(i, i);
    buffer.push(newStr);
    ASSERT_EQ(buffer.size(), 1);
    ASSERT_EQ(buffer.pop(), newStr);
  }
  ASSERT_TRUE(m_Data.empty());
}

TEST_F(RingBufferFixture, ValidatePushMove) {
  RingBuffer<TestStruct> buffer(10);
  for (int i = 0; i < 20; ++i) {
    buffer.push(TestStruct(i, i));
    ASSERT_EQ(buffer.size(), i + 1);
  }
  ASSERT_FALSE(buffer.empty());

  for (int i = 0; i < 20; ++i) {
    ASSERT_EQ(buffer.pop(), TestStruct(i, i));
    ASSERT_EQ(buffer.size(), 20 - i - 1);
  }
  ASSERT_EQ(buffer.size(), 0);
  ASSERT_TRUE(buffer.empty());
}

TEST_F(RingBufferFixture, ValidateWrapAround) {
  for (int i = 0; i < 10; ++i) {
    m_Data.push(i);
    ASSERT_EQ(m_Data.size(), i + 1);
  }

  for (int i = 0; i < 5; ++i) {
    ASSERT_EQ(m_Data.pop(), i);
  }

  for (int i = 10; i < 15; ++i) {
    m_Data.push(i);
    ASSERT_EQ(m_Data.size(), i - 5 + 1);
  }

  for (int i = 5; i < 15; ++i) {
    ASSERT_EQ(m_Data.pop(), i);
  }
}

TEST_F(RingBufferFixture, ValidateBigData) {
  static constexpr int SIZE = 100000;

  for (int i = 0; i < SIZE; ++i) {
    m_Data.push(i);
    ASSERT_EQ(m_Data.size(), i + 1);
  }

  for (int i = 0; i < SIZE; ++i) {
    ASSERT_EQ(m_Data.pop(), i);
    ASSERT_EQ(m_Data.size(), SIZE - i - 1);
  }

  ASSERT_TRUE(m_Data.empty());
}
}  // namespace ignosi::container::test
