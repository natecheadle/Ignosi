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
  ASSERT_TRUE(m_Data.Empty());
}

TEST_F(RingBufferFixture, ValidatePushPop) {
  m_Data.Push(1);
  ASSERT_EQ(m_Data.Size(), 1);
  ASSERT_EQ(m_Data.Pop(), 1);
  ASSERT_TRUE(m_Data.Empty());
}

TEST_F(RingBufferFixture, ValidatePushPopPastEnd) {
  for (int i = 0; i < 20; ++i) {
    m_Data.Push(i);
    ASSERT_EQ(m_Data.Size(), 1);
    ASSERT_EQ(m_Data.Pop(), i);
  }
}

TEST_F(RingBufferFixture, ValidatePushPastEnd) {
  for (int i = 0; i < 20; ++i) {
    m_Data.Push(i);
    ASSERT_EQ(m_Data.Size(), i + 1);
  }

  for (int i = 0; i < 20; ++i) {
    ASSERT_EQ(m_Data.Pop(), i);
    ASSERT_EQ(m_Data.Size(), 20 - i - 1);
  }
}

TEST_F(RingBufferFixture, ValidatePushCopy) {
  RingBuffer<TestStruct> buffer(10);
  for (int i = 0; i < 20; ++i) {
    TestStruct newStr(i, i);
    buffer.Push(newStr);
    ASSERT_EQ(buffer.Size(), 1);
    ASSERT_EQ(buffer.Pop(), newStr);
  }
  ASSERT_TRUE(m_Data.Empty());
}

TEST_F(RingBufferFixture, ValidatePushMove) {
  RingBuffer<TestStruct> buffer(10);
  for (int i = 0; i < 20; ++i) {
    buffer.Push(TestStruct(i, i));
    ASSERT_EQ(buffer.Size(), i + 1);
  }
  ASSERT_FALSE(buffer.Empty());

  for (int i = 0; i < 20; ++i) {
    ASSERT_EQ(buffer.Pop(), TestStruct(i, i));
    ASSERT_EQ(buffer.Size(), 20 - i - 1);
  }
  ASSERT_EQ(buffer.Size(), 0);
  ASSERT_TRUE(buffer.Empty());
}

TEST_F(RingBufferFixture, ValidateWrapAround) {
  for (int i = 0; i < 10; ++i) {
    m_Data.Push(i);
    ASSERT_EQ(m_Data.Size(), i + 1);
  }

  for (int i = 0; i < 5; ++i) {
    ASSERT_EQ(m_Data.Pop(), i);
  }

  for (int i = 10; i < 15; ++i) {
    m_Data.Push(i);
    ASSERT_EQ(m_Data.Size(), i - 5 + 1);
  }

  for (int i = 5; i < 15; ++i) {
    ASSERT_EQ(m_Data.Pop(), i);
  }
}

TEST_F(RingBufferFixture, ValidateBigData) {
  static constexpr int SIZE = 100000;

  for (int i = 0; i < SIZE; ++i) {
    m_Data.Push(i);
    ASSERT_EQ(m_Data.Size(), i + 1);
  }

  for (int i = 0; i < SIZE; ++i) {
    ASSERT_EQ(m_Data.Pop(), i);
    ASSERT_EQ(m_Data.Size(), SIZE - i - 1);
  }

  ASSERT_TRUE(m_Data.Empty());
}
}  // namespace ignosi::container::test
