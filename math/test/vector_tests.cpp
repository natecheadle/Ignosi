#include <gtest/gtest.h>

#include <vector.hpp>

namespace ignosi::math::test {

TEST(Vector_Fixture, ValidateInitialization) {
  Vector3<float> values(1.0f, 2.0f, 3.0f);
  ASSERT_EQ(1.0f, values.X());
  ASSERT_EQ(2.0f, values.Y());
  ASSERT_EQ(3.0f, values.Z());
}

TEST(Vector_Fixture, ValidateXAssignment) {
  Vector4<float> values;
  values.X(2.0);
  ASSERT_EQ(2.0f, values.X());
  ASSERT_EQ(2.0f, values[0]);

  values[0] = 3.0;
  ASSERT_EQ(3.0f, values.X());
  ASSERT_EQ(3.0f, values[0]);
}

TEST(Vector_Fixture, ValidateYAssignment) {
  Vector4<float> values;
  values.Y(2.0);
  ASSERT_EQ(2.0f, values.Y());
  ASSERT_EQ(2.0f, values[1]);

  values[1] = 3.0;
  ASSERT_EQ(3.0f, values.Y());
  ASSERT_EQ(3.0f, values[1]);
}

TEST(Vector_Fixture, ValidateZAssignment) {
  Vector4<float> values;
  values.Z(2.0);
  ASSERT_EQ(2.0f, values.Z());
  ASSERT_EQ(2.0f, values[2]);

  values[2] = 3.0;
  ASSERT_EQ(3.0f, values.Z());
  ASSERT_EQ(3.0f, values[2]);
}

TEST(Vector_Fixture, ValidateWAssignment) {
  Vector4<float> values;
  values.W(2.0);
  ASSERT_EQ(2.0f, values.W());
  ASSERT_EQ(2.0f, values[3]);

  values[3] = 3.0;
  ASSERT_EQ(3.0f, values.W());
  ASSERT_EQ(3.0f, values[3]);
}

TEST(Vector_Fixture, ValidateDotProduct) {
  Vector3<float> vec(1.0f, 2.0f, 3.0f);
  float rslt = vec.Dot(vec);
  ASSERT_EQ(14, rslt);
}

TEST(Vector_Fixture, ValidateCrossProduct) {
  Vector3<float> vec1(1.0f, 2.0f, 3.0f);
  Vector3<float> vec2(-1.0f, -1.0f, -1.0f);
  Vector3<float> rslt = vec1.Cross(vec2);
  ASSERT_EQ(Vector3<float>(1.0f, -2.0f, 1.0f), rslt);
}

TEST(Vector_Fixture, ValidateSubtraction) {
  Vector3<float> vec1(1.0f, 2.0f, 3.0f);
  Vector3<float> vec2(-1.0f, -1.0f, -1.0f);
  Vector3<float> rslt = vec1 - vec2;
  ASSERT_EQ(Vector3<float>(2.0f, 3.0f, 4.0f), rslt);
}

TEST(Vector_Fixture, ValidateDistance) {
  Vector2<float> vec0(0.0f, 0.0f);
  Vector2<float> vec1(1.0f, 1.0f);
  ASSERT_FLOAT_EQ(std::sqrt(2.0f), vec0.Distance(vec1));
}

TEST(Vector_Fixture, ValidateMagnitude) {
  Vector3<float> vec0(1.0f, 1.0f, 1.0f);
  ASSERT_FLOAT_EQ(std::sqrt(3.0f), vec0.Magnitude());
}

TEST(Vector_Fixture, ValidateSubtractionSelf) {
  Vector3<float> vec1(1.0f, 2.0f, 3.0f);
  Vector3<float> vec2(-1.0f, -1.0f, -1.0f);
  vec1 -= vec2;
  ASSERT_EQ(Vector3<float>(2.0f, 3.0f, 4.0f), vec1);
}

TEST(Vector_Fixture, ValidateAddition) {
  Vector3<float> vec1(1.0f, 2.0f, 3.0f);
  Vector3<float> vec2(-1.0f, -1.0f, -1.0f);
  Vector3<float> rslt = vec1 + vec2;
  ASSERT_EQ(Vector3<float>(0.0f, 1.0f, 2.0f), rslt);
}

TEST(Vector_Fixture, ValidateAdditionSelf) {
  Vector3<float> vec1(1.0f, 2.0f, 3.0f);
  Vector3<float> vec2(-1.0f, -1.0f, -1.0f);
  vec1 += vec2;
  ASSERT_EQ(Vector3<float>(0.0f, 1.0f, 2.0f), vec1);
}

TEST(Vector_Fixture, ValidateMultiplication) {
  Vector3<float> vec1(1.0f, 2.0f, 3.0f);
  Vector3<float> rslt1 = vec1 * 2.0f;
  Vector3<float> rslt2 = 2.0f * vec1;
  ASSERT_EQ(Vector3<float>(2.0f, 4.0f, 6.0f), rslt1);
  ASSERT_EQ(rslt1, rslt2);
}

TEST(Vector_Fixture, ValidateMultiplicationSelf) {
  Vector3<float> vec1(1.0f, 2.0f, 3.0f);
  vec1 *= 2.0f;
  ASSERT_EQ(Vector3<float>(2.0f, 4.0f, 6.0f), vec1);
}

TEST(Vector_Fixture, ValidateDivision) {
  Vector3<float> vec1(1.0f, 2.0f, 3.0f);
  Vector3<float> rslt = vec1 / 2.0f;
  ASSERT_EQ(Vector3<float>(0.5f, 1.0f, 1.5f), rslt);
}

TEST(Vector_Fixture, ValidateDivisionSelf) {
  Vector3<float> vec1(1.0f, 2.0f, 3.0f);
  vec1 /= 2.0f;
  ASSERT_EQ(Vector3<float>(0.5f, 1.0f, 1.5f), vec1);
}
}  // namespace ignosi::math::test
