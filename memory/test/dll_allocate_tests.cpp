#include <allocate.h>
#include <fmt/format.h>
#include <gtest/gtest.h>
#include <new.h>

#include <allocator.hpp>
#include <memory>
#include <stdexcept>

namespace ignosi::memory::test {
namespace {

struct TestObject {
  TestObject() : Value1(0.0), Value2(0.0) {}
  TestObject(double value1, double value2) : Value1(value1), Value2(value2) {}

  TestObject(const TestObject &other) = default;
  TestObject(TestObject &&other) = default;

  TestObject &operator=(const TestObject &other) = default;
  TestObject &operator=(TestObject &&other) = default;

  double Value1;
  double Value2;

  friend bool operator==(const TestObject &lhs,
                         const TestObject &rhs) = default;
  friend bool operator!=(const TestObject &lhs,
                         const TestObject &rhs) = default;

  friend std::ostream &operator<<(std::ostream &os, const TestObject &value) {
    os << fmt::format("Value1 = {}, Value2 = {}", value.Value1, value.Value2);
    return os;
  }
};

struct ThrowingTestObject : public TestObject {
  ThrowingTestObject() { throw std::runtime_error("ERROR"); }
};

struct DerivedTestObject : public TestObject {
  DerivedTestObject() = default;

  DerivedTestObject(double value1, double value2, double value3)
      : TestObject(value1, value2) {
    Value3 = value3;
  }

  DerivedTestObject(const DerivedTestObject &other) = default;
  DerivedTestObject(DerivedTestObject &&other) = default;

  DerivedTestObject &operator=(const DerivedTestObject &other) = default;
  DerivedTestObject &operator=(DerivedTestObject &&other) = default;

  double Value3;

  friend bool operator==(const DerivedTestObject &lhs,
                         const DerivedTestObject &rhs) = default;
  friend bool operator!=(const DerivedTestObject &lhs,
                         const DerivedTestObject &rhs) = default;

  friend std::ostream &operator<<(std::ostream &os,
                                  const DerivedTestObject &value) {
    os << static_cast<const TestObject &>(value)
       << fmt::format(", Value3 = {}", value.Value3);
    return os;
  }
};

};  // namespace

class DllAllocateFixture : public testing::Test {};

TEST_F(DllAllocateFixture, validate_new_delete) {
  TestObject *pObj = nullptr;

  ASSERT_NO_THROW(pObj = new TestObject());
  ASSERT_NO_THROW(delete pObj;);
}

TEST_F(DllAllocateFixture, validate_create_destroy) {
  ASSERT_NO_THROW(auto pNew{std::make_unique<TestObject>()});
}

TEST_F(DllAllocateFixture, validate_create_destroy_args) {
  auto pNew{std::make_unique<TestObject>(1.0, 2.0)};

  ASSERT_EQ(*pNew, TestObject(1.0, 2.0));
}

TEST_F(DllAllocateFixture, validate_create_throwing_object) {
  ASSERT_THROW(auto pNew{std::make_unique<ThrowingTestObject>()},
               std::runtime_error);
}

TEST_F(DllAllocateFixture, validate_create_derived) {
  std::unique_ptr<TestObject> pObj{std::make_unique<DerivedTestObject>()};
}

TEST_F(DllAllocateFixture, validate_create_shared_derived) {
  std::shared_ptr<DerivedTestObject> pObjShared1(
      std::make_shared<DerivedTestObject>(1.0, 2.0, 3.0));
  std::shared_ptr<TestObject> pObjShared2(pObjShared1);

  pObjShared1->Value1 = 10.0;
  pObjShared1->Value2 = 20.0;
  pObjShared1->Value3 = 30.0;

  ASSERT_EQ(pObjShared2->Value1, 10.0);
  ASSERT_EQ(pObjShared2->Value2, 20.0);
}

TEST_F(DllAllocateFixture, validate_create_dll_allocator) {
  std::vector<TestObject, DllAllocator<TestObject>> testVector;
  for (int i = 0; i < 10; ++i) {
    ASSERT_NO_THROW(testVector.push_back(TestObject(i, i * 2.0)));
  }
}
}  // namespace ignosi::memory::test
