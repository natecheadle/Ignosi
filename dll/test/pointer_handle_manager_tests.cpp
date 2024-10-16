#include <gtest/gtest.h>
#include <pointer_handle_manager.h>

namespace ignosi::dll::test {
struct TestStruct {
  TestStruct() : Value1(0), Value2(0.0) {}
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

struct TestStructExport {
  void* Value;
};

using TestStructHandleManager =
    PointerHandleManager<TestStruct, TestStructExport>;
using TestStructHandle = TestStructHandleManager::HANDLE_T;

class PointerHandleManagerFixture : public testing::Test {
 protected:
  TestStructHandleManager m_HandleManager;
};

TEST_F(PointerHandleManagerFixture, ValidateInitialization) {}

TEST_F(PointerHandleManagerFixture, ValidateCreateObject) {
  auto handle = m_HandleManager.AddObject(std::make_unique<TestStruct>());
  ASSERT_TRUE(handle.IsValid());
}

TEST_F(PointerHandleManagerFixture, ValidateCreateDestroyObject) {
  auto handle = m_HandleManager.AddObject(std::make_unique<TestStruct>());
  ASSERT_TRUE(m_HandleManager.DestroyObject(handle));
}

TEST_F(PointerHandleManagerFixture, ValidateModifyObject) {
  auto handle = m_HandleManager.AddObject(std::make_unique<TestStruct>());
  handle.InternalValue()->Value1 = 1;

  auto handle2 = handle;
  ASSERT_EQ(handle2.InternalValue(), handle.InternalValue());
  ASSERT_EQ(handle2.InternalValue(), handle.ExportValue().Value);
  ASSERT_EQ(handle2.InternalValue()->Value1, handle.InternalValue()->Value1);
}
}  // namespace ignosi::dll::test
