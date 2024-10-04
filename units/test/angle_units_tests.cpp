#include <gtest/gtest.h>

#include <angular_acceleration.hpp>
#include <angular_velocity.hpp>
#include <degree.hpp>
#include <numbers>
#include <radian.hpp>

namespace ignosi::units::test {
TEST(UnitsFixture, ValidateConstruction) {
  Degree<float> deg_val(180.0);
  Radian<float> rad_val(std::numbers::pi_v<float>);

  ASSERT_EQ(deg_val, rad_val);
}

TEST(UnitsFixture, ValidateAddition) {
  Degree<float> deg_val(180.0);
  Radian<float> rad_val(std::numbers::pi_v<float>);

  Radian<float> rslt = deg_val + rad_val;
  ASSERT_EQ(rslt, Radian<float>(std::numbers::pi_v<float> * 2.0f));

  deg_val += rad_val;
  ASSERT_EQ(deg_val, Radian<float>(std::numbers::pi_v<float> * 2.0f));
}

TEST(UnitsFixture, ValidateSubtraction) {
  Degree<float> deg_val(180.0);
  Radian<float> rad_val(std::numbers::pi_v<float>);

  Radian<float> rslt = deg_val - rad_val;
  ASSERT_EQ(rslt, Radian<float>(0.0));

  deg_val -= rad_val;
  ASSERT_EQ(deg_val, Radian<float>(0.0));
}

TEST(UnitsFixture, ValidateDivision) {
  Radian<float> rad_val(std::numbers::pi_v<float>);

  Radian<float> rslt = rad_val / 2.0f;
  ASSERT_EQ(rslt, Radian<float>(std::numbers::pi_v<float> / 2.0f));

  rad_val /= 2.0f;
  ASSERT_EQ(rad_val, Radian<float>(std::numbers::pi_v<float> / 2.0f));
}

TEST(UnitsFixture, ValidateMultiplication) {
  Radian<float> rad_val(std::numbers::pi_v<float>);

  Radian<float> rslt = rad_val * 2.0f;
  ASSERT_EQ(rslt, Radian<float>(std::numbers::pi_v<float> * 2.0f));

  rad_val *= 2.0f;
  ASSERT_EQ(rad_val, Radian<float>(std::numbers::pi_v<float> * 2.0f));
}

TEST(UnitsFixture, ValidateComparison) {
  Radian<float> rad_val(std::numbers::pi_v<float>);
  Degree<float> deg_val(180.0);
  Radian<float> large_val(std::numbers::pi_v<float> +
                          std::numbers::pi_v<float> / 2.0f);
  Radian<float> small_val(std::numbers::pi_v<float> / 2.0f);

  ASSERT_EQ(rad_val, deg_val);
  ASSERT_LT(small_val, rad_val);
  ASSERT_GT(large_val, rad_val);
  ASSERT_LT(small_val, deg_val);
  ASSERT_GT(large_val, deg_val);
}

TEST(UnitsFixture, ValidateVelocityConversion) {
  Radian<float> rad_val(std::numbers::pi_v<float>);
  RadianPerSecond<float> rad_per_sec_val(std::numbers::pi_v<float> * 2.0);
  Second<float> sec_val(0.5);

  ASSERT_EQ(rad_per_sec_val * sec_val, rad_val);
  ASSERT_EQ(rad_val / sec_val, rad_per_sec_val);
}

TEST(UnitsFixture, ValidateAccelConversion) {
  RadianPerSecondPerSecond<float> rad_per_sec_per_sec_val(
      std::numbers::pi_v<float> * 2.0);
  RadianPerSecond<float> rad_per_sec_val(std::numbers::pi_v<float>);
  Second<float> sec_val(0.5);
  RadianPerSecondPerSecond<float> rslt = rad_per_sec_val / sec_val;

  ASSERT_EQ(rad_per_sec_val / sec_val, rad_per_sec_per_sec_val);
  ASSERT_EQ(rad_per_sec_val, rad_per_sec_per_sec_val * sec_val);
}

}  // namespace ignosi::units::test
