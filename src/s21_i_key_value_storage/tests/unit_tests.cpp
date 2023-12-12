#include <gtest/gtest.h>

#include "../s21_i_key_value_storage.h"

TEST(ValueEquals, GivesRightAnswer) {
  s21::Value a = {"Ivanov", "Ivan", "2020", "Rostov", "55"};
  s21::Value b = a;
  EXPECT_TRUE(a == a);
  EXPECT_TRUE(a == b);
  EXPECT_TRUE(b == a);

  const s21::Value c = {"-", "Ivan", "-", "Rostov", "-"};
  EXPECT_TRUE(a == c);
  EXPECT_TRUE(c == a);

  const s21::Value d = {"Ivanov", "-", "2020", "-", "55"};
  EXPECT_TRUE(d == c);
  EXPECT_TRUE(c == d);

  s21::Value e = {"-", "-", "-", "-", "-"};
  EXPECT_TRUE(d == e);
  EXPECT_TRUE(e == d);

  s21::Value f = {"Ivanova", "-", "-", "-", "-"};
  EXPECT_FALSE(f == d);
  EXPECT_FALSE(f == a);
}

int main(int argc, char *argv[]) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}