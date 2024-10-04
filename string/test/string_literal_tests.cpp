#include <gtest/gtest.h>
#include <string_literal.h>

namespace ignosi::string::test {
TEST(StringLiteralFixture, ValidateConstruction) {
  StringLiteral test_str("This is a \n test string\n");
  ASSERT_EQ(StringLiteral("This is a \n test string\n"), test_str);
}

TEST(StringLiteralFixture, ValidateAddition) {
  StringLiteral str_1("This is a \n ");
  StringLiteral str_2("test string\n");
  auto rslt = str_1 + str_2;
  ASSERT_EQ(StringLiteral("This is a \n test string\n"), rslt);
}

TEST(StringLiteralFixture, ValidateAssignment) {
  StringLiteral str_1("This is a \n ");
  auto str_2 = str_1;
  ASSERT_EQ(str_1, str_2);
}

TEST(StringLiteralFixture, ValidateCopy) {
  StringLiteral str_1("This is a \n ");
  auto str_2(str_1);
  ASSERT_EQ(str_1, str_2);
}

TEST(StringLiteralFixture, ValidateCompare) {
  StringLiteral str_1("This is a \n ");
  StringLiteral str_2("This is a \n ");
  StringLiteral str_3("This is a \n");

  ASSERT_EQ(str_1, str_1);
  ASSERT_EQ(str_1, str_2);
  ASSERT_NE(str_3, str_2);
}

}  // namespace ignosi::string::test
