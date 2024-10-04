#include <gtest/gtest.h>

#include <glm/ext/matrix_float4x4.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/vector_float3.hpp>
#include <glm/fwd.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <square_matrix.hpp>
#include <vector.hpp>

using namespace std::numbers;
using namespace ignosi::units;

static constexpr float PI_4 = pi_v<float> / 4.0f;

namespace ignosi::math::test {
class MatrixFixture : public testing::Test {
 public:
  SquareMatrix4x4<float> test;
  MatrixFixture()
      : test({{1.0f, 2.0f, 3.0f, 4.0f},
              {5.0f, 6.0f, 7.0f, 8.0f},
              {9.0f, 10.0f, 11.0f, 12.0f},
              {13.0f, 14.0f, 15.0f, 16.0f}}) {}

  static SquareMatrix4x4<float> TranslateMatrix(const glm::mat4& in) {
    SquareMatrix4x4<float> rslt;
    for (size_t i = 0; i < SquareMatrix4x4<float>::size(); ++i) {
      for (size_t j = 0; j < SquareMatrix4x4<float>::size(); ++j) {
        rslt[i][j] = in[int(i)][int(j)];
      }
    }
    return rslt;
  }

  static glm::mat4 TranslateMatrix(const SquareMatrix4x4<float>& in) {
    glm::mat4 rslt;
    for (size_t i = 0; i < SquareMatrix4x4<float>::size(); ++i) {
      for (size_t j = 0; j < SquareMatrix4x4<float>::size(); ++j) {
        rslt[int(i)][int(j)] = in[i][j];
      }
    }
    return rslt;
  }
};

TEST_F(MatrixFixture, ValidateDeterminate) { ASSERT_EQ(0, test.Determinant()); }

TEST_F(MatrixFixture, ValidateTo3x3) {
  SquareMatrix3x3<float> mat3{
      {1.0f, 2.0f, 3.0f}, {5.0f, 6.0f, 7.0f}, {9.0f, 10.0f, 11.0f}};
  ASSERT_EQ(mat3, test.To3x3());
}

TEST_F(MatrixFixture, ValidateAddition) {
  SquareMatrix4x4<float> rslt{{2.0f, 4.0f, 6.0f, 8.0f},
                              {10.0f, 12.0f, 14.0f, 16.0f},
                              {18.0f, 20.0f, 22.0f, 24.0f},
                              {26.0f, 28.0f, 30.0f, 32.0f}};

  ASSERT_EQ(rslt, test + test);
}

TEST_F(MatrixFixture, ValidateSubtraction) {
  SquareMatrix4x4<float> rslt{{0.0f, 0.0f, 0.0f, 0.0f},
                              {0.0f, 0.0f, 0.0f, 0.0f},
                              {0.0f, 0.0f, 0.0f, 0.0f},
                              {0.0f, 0.0f, 0.0f, 0.0f}};

  ASSERT_EQ(rslt, test - test);
}

TEST_F(MatrixFixture, ValidateMultiplication) {
  SquareMatrix4x4<float> rslt{{90.0f, 100.0f, 110.0f, 120.0f},
                              {202.0f, 228.0f, 254.0f, 280.0f},
                              {314.0f, 356.0f, 398.0f, 440.0f},
                              {426.0f, 484.0f, 542.0f, 600.0f}};

  ASSERT_EQ(rslt, test * test);
  ASSERT_EQ(TranslateMatrix(TranslateMatrix(test) * TranslateMatrix(test)),
            test * test);
  auto rot_x = SquareMatrix4x4<float>::CreateRotateZYX({PI_4, 0.0f, 0.0f});

  auto rot_y = SquareMatrix4x4<float>::CreateRotateZYX({0.0, PI_4, 0.0});

  auto rot_x_glm = glm::rotate<float>(glm::mat4(1.0), PI_4, glm::vec3(1, 0, 0));
  auto rot_y_glm = glm::rotate<float>(glm::mat4(1.0), PI_4, glm::vec3(0, 1, 0));

  ASSERT_EQ(TranslateMatrix(rot_x_glm * rot_y_glm), rot_x * rot_y);
  ASSERT_EQ(TranslateMatrix(rot_y_glm * rot_x_glm), rot_y * rot_x);
}

TEST_F(MatrixFixture, ValidateIdentity) {
  SquareMatrix4x4<float> rslt{{1.0f, 0.0f, 0.0f, 0.0f},
                              {0.0f, 1.0f, 0.0f, 0.0f},
                              {0.0f, 0.0f, 1.0f, 0.0f},
                              {0.0f, 0.0f, 0.0f, 1.0f}};
  ASSERT_EQ(rslt, SquareMatrix4x4<float>::Identity());
}

TEST_F(MatrixFixture, ValidateInverse) {
  SquareMatrix3x3<float> input{
      {2.0f, 1.0f, -1.0f}, {-3.0f, -1.0f, 2.0f}, {-2.0f, 1.0f, 2.0f}};
  SquareMatrix3x3<float> rslt{
      {4.0f, 3.0f, -1.0f}, {-2.0f, -2.0f, 1.0f}, {5.0f, 4.0f, -1.0f}};
  ASSERT_EQ(rslt, input.Invert());
}

TEST_F(MatrixFixture, ValidatePerspective) {
  SquareMatrix4x4<float> input(
      SquareMatrix4x4<float>::Perspective(PI_4, 800.0f / 600.0f, 0.1f, 100.0f));
  glm::mat4 projection =
      glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);

  ASSERT_EQ(TranslateMatrix(projection), input);
}

TEST_F(MatrixFixture, ValidateLookAt) {
  SquareMatrix4x4<float> input(SquareMatrix4x4<float>::LookAt(
      {0.0, 0.0, 3.0}, {0.0, 0.0, 0.0}, {0.0, 1.0, 0.0}));
  glm::mat4 look_at =
      glm::lookAt(glm::vec3(0.0, 0.0, 3.0), glm::vec3(0.0, 0.0, 0.0),
                  glm::vec3(0.0, 1.0, 0.0));

  ASSERT_EQ(TranslateMatrix(look_at), input);
}

TEST_F(MatrixFixture, ValidateOrthographic) {
  glm::mat4 ortho_mat = glm::ortho(0.0f, 800.0f, 600.0f, 0.0f, -1.0f, 1.0f);
  SquareMatrix4x4<float> ortho = SquareMatrix4x4<float>::Orthographic(
      0.0f, 800.0f, 600.0f, 0.0f, -1.0f, 1.0f);
  ASSERT_EQ(TranslateMatrix(ortho_mat), ortho);
}

TEST_F(MatrixFixture, ValidateRotationMatrix) {
  auto rot_zyx = SquareMatrix4x4<float>::CreateRotateZYX({PI_4, PI_4, PI_4});

  auto rot_x = SquareMatrix4x4<float>::CreateRotateZYX({PI_4, 0.0, 0.0});

  auto rot_y = SquareMatrix4x4<float>::CreateRotateZYX({0.0, PI_4, 0.0});

  auto rot_z = SquareMatrix4x4<float>::CreateRotateZYX({0.0, 0.0, PI_4});

  auto rot_x_glm = glm::rotate<float>(glm::mat4(1.0), PI_4, glm::vec3(1, 0, 0));
  auto rot_y_glm = glm::rotate<float>(glm::mat4(1.0), PI_4, glm::vec3(0, 1, 0));
  auto rot_z_glm = glm::rotate<float>(glm::mat4(1.0), PI_4, glm::vec3(0, 0, 1));

  ASSERT_EQ(TranslateMatrix(rot_x_glm), rot_x);
  ASSERT_EQ(TranslateMatrix(rot_y_glm), rot_y);
  ASSERT_EQ(TranslateMatrix(rot_z_glm), rot_z);

  ASSERT_EQ(TranslateMatrix(rot_x_glm * rot_y_glm), rot_x * rot_y);
  ASSERT_EQ(TranslateMatrix(rot_x_glm * rot_z_glm), rot_x * rot_z);
  ASSERT_EQ(TranslateMatrix(rot_y_glm * rot_z_glm), rot_y * rot_z);

  ASSERT_EQ(rot_zyx, rot_z * rot_y * rot_x);
}
}  // namespace ignosi::math::test
