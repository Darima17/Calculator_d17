#include <gtest/gtest.h>

#include <cmath>
#include <string>

#include "model/calc.h"

namespace s21 {
class TestModel : public ::testing::Test {
 public:
  s21::Calc calc;
  void SetUp() override {}
  void TearDown() override {}
};

TEST_F(TestModel, number_test) {
  double result = 0;
  int status = 0;

  // test 1
  char string_1[255] = "12.3+4=";
  char polish[MAX] = {0};
  status = calc.check_and_parcer(string_1, polish);
  status = calc.m_calc(string_1, &result, 0);
  char postfix[255] = "12.3 4 +";
  ASSERT_TRUE(strcmp(postfix, polish) == 0);
  EXPECT_EQ(status, OK);
  ASSERT_NEAR(result, 16.3, 1e-7);

  // test 2
  char string_2[255] = "(12)=";
  status = calc.m_calc(string_2, &result, 0);

  EXPECT_EQ(status, OK);
  ASSERT_NEAR(result, 12, 1e-7);

  // test 3
  char string_3[255] = "(12.)=";
  status = calc.m_calc(string_3, &result, 0);

  EXPECT_EQ(status, ERROR);

  // test 4
  char string_4[255] = ".12=";
  status = calc.m_calc(string_4, &result, 0);

  EXPECT_EQ(status, ERROR);

  // test 5
  char string_5[255] = "1.12.=";
  status = calc.m_calc(string_5, &result, 0);

  EXPECT_EQ(status, ERROR);

  // test 6
  char string_6[255] = "1.12.1=";
  status = calc.m_calc(string_6, &result, 0);

  EXPECT_EQ(status, ERROR);

  // test 7
  char string_7[255] = "(1.12.)=";
  status = calc.m_calc(string_7, &result, 0);

  EXPECT_EQ(status, ERROR);

  // test 8
  char string_8[255] = "x+1.1=";
  status = calc.m_calc(string_8, &result, 2.2);

  EXPECT_EQ(status, OK);
  ASSERT_NEAR(result, 3.3, 1e-7);

  // test 9
  char string_9[255] = "x=";
  status = calc.m_calc(string_9, &result, 2.2);

  EXPECT_EQ(status, OK);
  ASSERT_NEAR(result, 2.2, 1e-7);

  // test 10
  char string_10[255] = "-x=";
  status = calc.m_calc(string_10, &result, 2.2);

  EXPECT_EQ(status, OK);
  ASSERT_NEAR(result, -2.2, 1e-7);

  // test 11
  char string_11[255] = ".x+1=";
  status = calc.m_calc(string_11, &result, 2.2);

  EXPECT_EQ(status, ERROR);

  // test 12
  char string_12[255] = "1.x+1=";
  status = calc.m_calc(string_12, &result, 2.2);

  EXPECT_EQ(status, ERROR);

  // test 13
  char string_13[255] = "x.1+1=";
  status = calc.m_calc(string_13, &result, 2.2);

  EXPECT_EQ(status, ERROR);
}

// plus test
TEST_F(TestModel, plus_test) {
  double result = 0;
  int status = 0;

  // test 1
  char string_1[255] = "-12.3+4=";
  status = calc.m_calc(string_1, &result, 0);

  EXPECT_EQ(status, OK);
  ASSERT_NEAR(result, -8.3, 1e-7);

  // test 2
  char string_2[255] = "(12)+(-12.00006)=";
  status = calc.m_calc(string_2, &result, 0);

  EXPECT_EQ(status, OK);
  ASSERT_NEAR(result, -0.00006, 1e-7);

  // test 3
  char string_3[255] = "(12.02)++12.2=";
  status = calc.m_calc(string_3, &result, 0);

  EXPECT_EQ(status, ERROR);

  // test 4
  char string_4[255] = "12+=";
  status = calc.m_calc(string_4, &result, 0);

  EXPECT_EQ(status, ERROR);

  // test 5
  char string_5[255] = "+1.12=";
  status = calc.m_calc(string_5, &result, 0);

  EXPECT_EQ(status, OK);
  EXPECT_DOUBLE_EQ(result, 1.12);

  // test 6
  char string_6[255] = "+(+(+10))+(+(+10))=";
  status = calc.m_calc(string_6, &result, 0);

  EXPECT_EQ(status, OK);
  EXPECT_DOUBLE_EQ(result, 20);

  // test 7
  char string_7[255] = "++1.12=";
  status = calc.m_calc(string_7, &result, 0);

  EXPECT_EQ(status, ERROR);

  // test 8
  char string_8[255] = "1.2+1.2+2.4+4.8=";
  status = calc.m_calc(string_8, &result, 2.2);

  EXPECT_EQ(status, OK);
  ASSERT_NEAR(result, 9.6, 1e-7);
}

// sub test
TEST_F(TestModel, sub_test) {
  double result = 0;
  int status = 0;

  // test 1
  char string_1[255] = "-12.3-4=";
  status = calc.m_calc(string_1, &result, 0);

  EXPECT_EQ(status, OK);
  ASSERT_NEAR(result, -16.3, 1e-7);

  // test 2
  char string_2[255] = "(12)-(-12.00006)=";
  status = calc.m_calc(string_2, &result, 0);

  EXPECT_EQ(status, OK);
  ASSERT_NEAR(result, 24.00006, 1e-7);
  EXPECT_DOUBLE_EQ(result, 24.00006);

  // test 3
  char string_3[255] = "(12.02)--12.2=";
  status = calc.m_calc(string_3, &result, 0);

  EXPECT_EQ(status, ERROR);

  // test 4
  char string_4[255] = "12-=";
  status = calc.m_calc(string_4, &result, 0);

  EXPECT_EQ(status, ERROR);

  // test 5
  char string_5[255] = "-1.12=";
  status = calc.m_calc(string_5, &result, 0);

  EXPECT_EQ(status, OK);
  ASSERT_NEAR(result, -1.12, 1e-7);
  // test 6
  char string_6[255] = "-(-(-10))-(-(-10))=";
  status = calc.m_calc(string_6, &result, 0);

  EXPECT_EQ(status, OK);
  ASSERT_NEAR(result, -20, 1e-7);

  // test 7
  char string_7[255] = "--1.12=";
  status = calc.m_calc(string_7, &result, 0);

  EXPECT_EQ(status, ERROR);

  // test 8
  char string_8[255] = "-1.2-1.2-2.4-4.8=";
  status = calc.m_calc(string_8, &result, 2.2);

  EXPECT_EQ(status, OK);
  ASSERT_NEAR(result, -9.6, 1e-7);
}

// mul test
TEST_F(TestModel, mul_test) {
  double result = 0;
  int status = 0;

  // test 1
  char string_1[255] = "-1.3*4=";
  status = calc.m_calc(string_1, &result, 0);

  EXPECT_EQ(status, OK);
  ASSERT_NEAR(result, -5.2, 1e-7);

  // test 2
  char string_2[255] = "(12)*(-1.0006)=";
  status = calc.m_calc(string_2, &result, 0);

  EXPECT_EQ(status, OK);
  ASSERT_NEAR(result, -12.0072, 1e-7);

  // test 3
  char string_3[255] = "(12.02)**12.2=";
  status = calc.m_calc(string_3, &result, 0);

  EXPECT_EQ(status, ERROR);

  // test 4
  char string_4[255] = "12*=";
  status = calc.m_calc(string_4, &result, 0);

  EXPECT_EQ(status, ERROR);

  // test 5
  char string_5[255] = "*1.12=";
  status = calc.m_calc(string_5, &result, 0);

  EXPECT_EQ(status, ERROR);

  // test 6
  char string_6[255] = "-(-(-10))*(-(-10))=";
  status = calc.m_calc(string_6, &result, 0);

  EXPECT_EQ(status, OK);
  ASSERT_NEAR(result, -100, 1e-7);

  // test 8
  char string_8[255] = "(+12*)13=";
  status = calc.m_calc(string_8, &result, 2.2);

  EXPECT_EQ(status, ERROR);
}

// div test
TEST_F(TestModel, DivTest) {
  double result = 0;
  int status = 0;

  // test 1
  char string_1[255] = "-1.3/4=";
  status = calc.m_calc(string_1, &result, 0);

  EXPECT_EQ(status, OK);
  ASSERT_NEAR(result, -0.325, 1e-7);

  // test 2
  char string_2[255] = "(12)/(-1.0006)=";
  status = calc.m_calc(string_2, &result, 0);

  EXPECT_EQ(status, OK);
  ASSERT_NEAR(result, -11.9928043, 1e-7);

  // test 3
  char string_3[255] = "(12.02)//12.2=";
  status = calc.m_calc(string_3, &result, 0);
  EXPECT_EQ(status, ERROR);

  // test 4
  char string_4[255] = "12/=";
  status = calc.m_calc(string_4, &result, 0);
  EXPECT_EQ(status, ERROR);

  // test 5
  char string_5[255] = "/1.12=";
  status = calc.m_calc(string_5, &result, 0);
  EXPECT_EQ(status, ERROR);

  // test 6
  char string_6[255] = "-(-(-10))/(-(-10))=";
  status = calc.m_calc(string_6, &result, 0);
  EXPECT_EQ(status, OK);
  ASSERT_NEAR(result, -1, 1e-7);

  // test 8
  char string_8[255] = "(+12/)13=";
  status = calc.m_calc(string_8, &result, 2.2);
  EXPECT_EQ(status, ERROR);
}

// mod test
TEST_F(TestModel, ModTest) {
  double result = 0;
  int status = 0;

  // test 1
  char string_1[255] = "-1.3mod4=";
  status = calc.m_calc(string_1, &result, 0);

  EXPECT_EQ(status, OK);
  ASSERT_NEAR(result, -1.3, 1e-7);
  EXPECT_DOUBLE_EQ(result, -1.3);

  // test 2
  char string_2[255] = "(12)mod(-1.0006)=";
  status = calc.m_calc(string_2, &result, 0);
  EXPECT_EQ(status, OK);
  ASSERT_NEAR(result, 0.9934000000000007, 1e-7);
  // test 3
  char string_3[255] = "(12.2)mod12.02=";
  status = calc.m_calc(string_3, &result, 0);

  EXPECT_EQ(status, OK);
  ASSERT_NEAR(result, 0.17999999999999972, 1e-7);

  // test 4
  char string_4[255] = "12mod=";
  status = calc.m_calc(string_4, &result, 0);
  EXPECT_EQ(status, ERROR);

  // test 5
  char string_5[255] = "mod1.12=";
  status = calc.m_calc(string_5, &result, 0);
  EXPECT_EQ(status, ERROR);

  // test 6
  char string_6[255] = "-(-(-10))mod(-(-10))=";
  status = calc.m_calc(string_6, &result, 0);
  EXPECT_EQ(status, OK);
  ASSERT_NEAR(result, 0, 1e-7);

  // test 8
  char string_8[255] = "(+12mod)13=";
  status = calc.m_calc(string_8, &result, 2.2);
  EXPECT_EQ(status, ERROR);
}

// deg test
TEST_F(TestModel, DegTest) {
  double result = 0;
  int status = 0;

  // test 1
  char string_1[255] = "-1.3^4=";
  status = calc.m_calc(string_1, &result, 0);
  EXPECT_EQ(status, OK);
  ASSERT_NEAR(result, -2.8561, 1e-7);
  // test 2
  char string_2[255] = "(12)^(-1.0006)=";
  status = calc.m_calc(string_2, &result, 0);
  EXPECT_EQ(status, OK);
  ASSERT_NEAR(result, 0.08320918057, 1e-7);

  // test 3
  char string_3[255] = "(12.2)^2.02=";
  status = calc.m_calc(string_3, &result, 0);
  EXPECT_EQ(status, OK);
  ASSERT_NEAR(result, 156.475683751, 1e-7);

  // test 4
  char string_4[255] = "12^=";
  status = calc.m_calc(string_4, &result, 0);
  EXPECT_EQ(status, ERROR);

  // test 5
  char string_5[255] = "^1.12=";
  status = calc.m_calc(string_5, &result, 0);
  EXPECT_EQ(status, ERROR);

  // test 6
  char string_6[255] = "-(-(-10))^(-(-1))=";
  status = calc.m_calc(string_6, &result, 0);
  EXPECT_EQ(status, OK);
  ASSERT_NEAR(result, -10, 1e-7);
  // test 8
  char string_8[255] = "(+12^)13=";
  status = calc.m_calc(string_8, &result, 2.2);
  EXPECT_EQ(status, ERROR);

  // test 9
  char string_9[255] = "2^2^3=";
  status = calc.m_calc(string_9, &result, 2.2);
  EXPECT_EQ(status, OK);
  ASSERT_NEAR(result, 256, 1e-7);
}

// sqrt test
TEST_F(TestModel, SqrtTest) {
  double result = 0;
  int status = 0;

  // test 1
  char string_1[255] = "sqrt(4)=";
  status = calc.m_calc(string_1, &result, 0);

  EXPECT_EQ(status, OK);
  ASSERT_NEAR(result, 2, 1e-7);
  // test 2
  char string_2[255] = "sqrt(-4)=";
  status = calc.m_calc(string_2, &result, 0);

  EXPECT_EQ(status, OK);
  ASSERT_TRUE(std::isnan(result));

  // test 3
  char string_3[255] = "-sqrt(4)=";
  status = calc.m_calc(string_3, &result, 0);

  EXPECT_EQ(status, OK);
  ASSERT_NEAR(result, -2, 1e-7);
  // test 4
  char string_4[255] = "sqrt()=";
  status = calc.m_calc(string_4, &result, 0);
  EXPECT_EQ(status, ERROR);

  // test 5
  char string_5[255] = "sqrt=";
  status = calc.m_calc(string_5, &result, 0);
  EXPECT_EQ(status, ERROR);

  // test 6
  char string_6[255] = "sqrt((((((4))))))=";
  status = calc.m_calc(string_6, &result, 0);
  EXPECT_EQ(status, OK);
  ASSERT_NEAR(result, 2, 1e-7);

  // test 7
  char string_7[255] = "sqrt(=";
  status = calc.m_calc(string_7, &result, 0);
  EXPECT_EQ(status, ERROR);

  // test 8
  char string_8[255] = "sqrt)=";
  status = calc.m_calc(string_8, &result, 0);

  EXPECT_EQ(status, ERROR);

  // test 9
  char string_9[255] = "sqrt(12=";
  status = calc.m_calc(string_9, &result, 0);

  EXPECT_EQ(status, ERROR);
}

// sin test
TEST_F(TestModel, SinTest) {
  double result = 0;
  int status = 0;

  // test 1
  char string_1[255] = "sin(3.14*2)=";
  status = calc.m_calc(string_1, &result, 0);

  EXPECT_EQ(status, OK);
  ASSERT_NEAR(result, -0.00318530179, 1e-7);

  // test 2
  char string_2[255] = "sin(1)=";
  status = calc.m_calc(string_2, &result, 0);

  EXPECT_EQ(status, OK);
  ASSERT_NEAR(result, 0.841470984807897, 1e-7);
  // test 3
  char string_3[255] = "-sin(1)=";
  status = calc.m_calc(string_3, &result, 0);

  EXPECT_EQ(status, OK);
  ASSERT_NEAR(result, -0.841470984807897, 1e-7);

  // test 4
  char string_4[255] = "sin()=";
  status = calc.m_calc(string_4, &result, 0);

  EXPECT_EQ(status, ERROR);

  // test 5
  char string_5[255] = "sin=";
  status = calc.m_calc(string_5, &result, 0);

  EXPECT_EQ(status, ERROR);

  // test 6
  char string_6[255] = "sin((((((4))))))=";
  status = calc.m_calc(string_6, &result, 0);

  EXPECT_EQ(status, OK);
  ASSERT_NEAR(result, -0.7568024953, 1e-7);

  // test 7
  char string_7[255] = "sin(=";
  status = calc.m_calc(string_7, &result, 0);

  EXPECT_EQ(status, ERROR);

  // test 8
  char string_8[255] = "sin)=";
  status = calc.m_calc(string_8, &result, 0);

  EXPECT_EQ(status, ERROR);

  // test 9
  char string_9[255] = "sin(12=";
  status = calc.m_calc(string_9, &result, 0);

  EXPECT_EQ(status, ERROR);
}

// cos test
TEST_F(TestModel, CosTest) {
  double result = 0;
  int status = 0;

  // test 1
  char string_1[255] = "cos(3.14*2)=";
  status = calc.m_calc(string_1, &result, 0);

  EXPECT_EQ(status, OK);
  ASSERT_NEAR(result, 0.99999492691, 1e-7);

  // test 2
  char string_2[255] = "cos(1)=";
  status = calc.m_calc(string_2, &result, 0);

  EXPECT_EQ(status, OK);
  ASSERT_NEAR(result, 0.54030230586, 1e-7);

  // test 3
  char string_3[255] = "-cos(1)=";
  status = calc.m_calc(string_3, &result, 0);

  EXPECT_EQ(status, OK);
  ASSERT_NEAR(result, -0.54030230586, 1e-7);

  // test 4
  char string_4[255] = "cos()=";
  status = calc.m_calc(string_4, &result, 0);

  EXPECT_EQ(status, ERROR);

  // test 5
  char string_5[255] = "cos=";
  status = calc.m_calc(string_5, &result, 0);

  EXPECT_EQ(status, ERROR);

  // test 6
  char string_6[255] = "cos((((((4))))))=";
  status = calc.m_calc(string_6, &result, 0);

  EXPECT_EQ(status, OK);
  ASSERT_NEAR(result, -0.65364362086, 1e-7);

  // test 7
  char string_7[255] = "cos(=";
  status = calc.m_calc(string_7, &result, 0);

  EXPECT_EQ(status, ERROR);

  // test 8
  char string_8[255] = "cos)=";
  status = calc.m_calc(string_8, &result, 0);

  EXPECT_EQ(status, ERROR);

  // test 9
  char string_9[255] = "cos(12=";
  status = calc.m_calc(string_9, &result, 0);

  EXPECT_EQ(status, ERROR);
}

// tan test
TEST_F(TestModel, tan_test) {
  double result = 0;
  int status = 0;

  // test 1
  char string_1[255] = "tan(3.14*2)=";
  status = calc.m_calc(string_1, &result, 0);

  EXPECT_EQ(status, OK);
  ASSERT_NEAR(result, -0.00318531795, 1e-7);

  // test 2
  char string_2[255] = "tan(1)=";
  status = calc.m_calc(string_2, &result, 0);

  EXPECT_EQ(status, OK);
  ASSERT_NEAR(result, 1.55740772465, 1e-7);

  // test 3
  char string_3[255] = "-tan(1)=";
  status = calc.m_calc(string_3, &result, 0);

  EXPECT_EQ(status, OK);
  ASSERT_NEAR(result, -1.55740772465, 1e-7);

  // test 4
  char string_4[255] = "tan()=";
  status = calc.m_calc(string_4, &result, 0);

  EXPECT_EQ(status, ERROR);

  // test 5
  char string_5[255] = "tan=";
  status = calc.m_calc(string_5, &result, 0);

  EXPECT_EQ(status, ERROR);

  // test 6
  char string_6[255] = "tan((((((4))))))=";
  status = calc.m_calc(string_6, &result, 0);

  EXPECT_EQ(status, OK);
  ASSERT_NEAR(result, 1.15782128235, 1e-7);

  // test 7
  char string_7[255] = "tan(=";
  status = calc.m_calc(string_7, &result, 0);

  EXPECT_EQ(status, ERROR);

  // test 8
  char string_8[255] = "tan)=";
  status = calc.m_calc(string_8, &result, 0);

  EXPECT_EQ(status, ERROR);

  // test 9
  char string_9[255] = "tan(12=";
  status = calc.m_calc(string_9, &result, 0);
  EXPECT_EQ(status, ERROR);
}

// asin test
TEST_F(TestModel, asin_test) {
  double result = 0;
  int status = 0;

  // test 1
  char string_1[255] = "asin(3.14*2)=";
  status = calc.m_calc(string_1, &result, 0);
  EXPECT_EQ(status, OK);
  ASSERT_TRUE(std::isnan(result));

  // test 2
  char string_2[255] = "asin(0.9)=";
  status = calc.m_calc(string_2, &result, 0);
  EXPECT_EQ(status, OK);
  ASSERT_NEAR(result, 1.11977, 1e-6);

  // test 3
  char string_3[255] = "-asin(0.9)=";
  status = calc.m_calc(string_3, &result, 0);

  EXPECT_EQ(status, OK);
  ASSERT_NEAR(result, -1.119770, 1e-6);

  // test 4
  char string_4[255] = "asin()=";
  status = calc.m_calc(string_4, &result, 0);

  EXPECT_EQ(status, ERROR);

  // test 5
  char string_5[255] = "asin=";
  status = calc.m_calc(string_5, &result, 0);

  EXPECT_EQ(status, ERROR);

  // test 6
  char string_6[255] = "asin((((((-0.0001))))))=";
  status = calc.m_calc(string_6, &result, 0);

  EXPECT_EQ(status, OK);
  ASSERT_NEAR(result, -0.000100, 1e-6);

  // test 7
  char string_7[255] = "asin(=";
  status = calc.m_calc(string_7, &result, 0);

  EXPECT_EQ(status, ERROR);

  // test 8
  char string_8[255] = "asin)=";
  status = calc.m_calc(string_8, &result, 0);

  EXPECT_EQ(status, ERROR);

  // test 9
  char string_9[255] = "asin(12=";
  status = calc.m_calc(string_9, &result, 0);

  EXPECT_EQ(status, ERROR);
}

// acos test
TEST_F(TestModel, acos_test) {
  double result = 0;
  int status = 0;

  // test 1
  char string_1[255] = "acos(3.14*2)=";
  status = calc.m_calc(string_1, &result, 0);

  EXPECT_EQ(status, OK);
  ASSERT_TRUE(std::isnan(result));

  // test 2
  char string_2[255] = "acos(0.9)=";
  status = calc.m_calc(string_2, &result, 0);

  EXPECT_EQ(status, OK);
  ASSERT_NEAR(result, 0.451027, 1e-6);

  // test 3
  char string_3[255] = "-acos(0.9)=";
  status = calc.m_calc(string_3, &result, 0);

  EXPECT_EQ(status, OK);
  ASSERT_NEAR(result, -0.451027, 1e-6);

  // test 4
  char string_4[255] = "acos()=";
  status = calc.m_calc(string_4, &result, 0);

  EXPECT_EQ(status, ERROR);

  // test 5
  char string_5[255] = "acos=";
  status = calc.m_calc(string_5, &result, 0);

  EXPECT_EQ(status, ERROR);

  // test 6
  char string_6[255] = "acos((((((-0.0001))))))=";
  status = calc.m_calc(string_6, &result, 0);
  EXPECT_EQ(status, OK);
  ASSERT_NEAR(result, 1.570896, 1e-6);

  // test 7
  char string_7[255] = "acos(=";
  status = calc.m_calc(string_7, &result, 0);
  EXPECT_EQ(status, ERROR);

  // test 8
  char string_8[255] = "acos)=";
  status = calc.m_calc(string_8, &result, 0);
  EXPECT_EQ(status, ERROR);

  // test 9
  char string_9[255] = "acos(12=";
  status = calc.m_calc(string_9, &result, 0);
  EXPECT_EQ(status, ERROR);
}

// atan test
TEST_F(TestModel, atan_test) {
  double result = 0;
  int status = 0;

  // test 1
  char string_1[255] = "atan(3.14*2)=";
  status = calc.m_calc(string_1, &result, 0);

  EXPECT_EQ(status, OK);
  ASSERT_NEAR(result, 1.412886, 1e-6);

  // test 2
  char string_2[255] = "atan(0.9)=";
  status = calc.m_calc(string_2, &result, 0);

  EXPECT_EQ(status, OK);
  ASSERT_NEAR(result, 0.732815, 1e-6);

  // test 3
  char string_3[255] = "-atan(0.9)=";
  status = calc.m_calc(string_3, &result, 0);

  EXPECT_EQ(status, OK);
  ASSERT_NEAR(result, -0.732815, 1e-6);

  // test 4
  char string_4[255] = "atan()=";
  status = calc.m_calc(string_4, &result, 0);

  EXPECT_EQ(status, ERROR);

  // test 5
  char string_5[255] = "atan=";
  status = calc.m_calc(string_5, &result, 0);

  EXPECT_EQ(status, ERROR);

  // test 6
  char string_6[255] = "atan((((((-0.0001))))))=";
  status = calc.m_calc(string_6, &result, 0);

  EXPECT_EQ(status, OK);
  ASSERT_NEAR(result, -0.000100, 1e-6);

  // test 7
  char string_7[255] = "atan(=";
  status = calc.m_calc(string_7, &result, 0);
  EXPECT_EQ(status, ERROR);

  // test 8
  char string_8[255] = "atan)=";
  status = calc.m_calc(string_8, &result, 0);
  EXPECT_EQ(status, ERROR);

  // test 9
  char string_9[255] = "atan(12=";
  status = calc.m_calc(string_9, &result, 0);
  EXPECT_EQ(status, ERROR);
}

// ln test
TEST_F(TestModel, ln_test) {
  double result = 0;
  int status = 0;

  // test 1
  char string_1[255] = "ln(3.14*2)=";
  status = calc.m_calc(string_1, &result, 0);

  EXPECT_EQ(status, OK);
  ASSERT_NEAR(result, 1.837370, 1e-6);

  // test 2
  char string_2[255] = "ln(0.9)=";
  status = calc.m_calc(string_2, &result, 0);

  EXPECT_EQ(status, OK);
  ASSERT_NEAR(result, -0.105361, 1e-6);
  // test 3
  char string_3[255] = "-ln(0.9)=";
  status = calc.m_calc(string_3, &result, 0);

  EXPECT_EQ(status, OK);
  ASSERT_NEAR(result, 0.105361, 1e-6);

  // test 4
  char string_4[255] = "ln()=";
  status = calc.m_calc(string_4, &result, 0);

  EXPECT_EQ(status, ERROR);

  // test 5
  char string_5[255] = "ln=";
  status = calc.m_calc(string_5, &result, 0);

  EXPECT_EQ(status, ERROR);

  // test 6
  char string_6[255] = "ln((((((-0.0001))))))=";
  status = calc.m_calc(string_6, &result, 0);

  EXPECT_EQ(status, OK);
  ASSERT_TRUE(std::isnan(result));

  // test 7
  char string_7[255] = "ln(=";
  status = calc.m_calc(string_7, &result, 0);

  EXPECT_EQ(status, ERROR);

  // test 8
  char string_8[255] = "ln)=";
  status = calc.m_calc(string_8, &result, 0);

  EXPECT_EQ(status, ERROR);

  // test 9
  char string_9[255] = "ln(12=";
  status = calc.m_calc(string_9, &result, 0);

  EXPECT_EQ(status, ERROR);
}

// log test
TEST_F(TestModel, log_test) {
  double result = 0;
  int status = 0;

  // test 1
  char string_1[255] = "log(3.14*2)=";
  status = calc.m_calc(string_1, &result, 0);
  EXPECT_EQ(status, OK);
  ASSERT_NEAR(result, 0.797960, 1e-6);

  // test 2
  char string_2[255] = "log(0.9)=";
  status = calc.m_calc(string_2, &result, 0);
  EXPECT_EQ(status, OK);
  ASSERT_NEAR(result, -0.045757, 1e-6);
  // test 3
  char string_3[255] = "-log(0.9)=";
  status = calc.m_calc(string_3, &result, 0);
  EXPECT_EQ(status, OK);
  ASSERT_NEAR(result, 0.045757, 1e-6);

  // test 4
  char string_4[255] = "log()=";
  status = calc.m_calc(string_4, &result, 0);

  EXPECT_EQ(status, ERROR);

  // test 5
  char string_5[255] = "log=";
  status = calc.m_calc(string_5, &result, 0);

  EXPECT_EQ(status, ERROR);

  // test 6
  char string_6[255] = "log((((((-0.0001))))))=";
  status = calc.m_calc(string_6, &result, 0);
  EXPECT_EQ(status, OK);
  EXPECT_TRUE(std::isnan(result));

  // test 7
  char string_7[255] = "log(=";
  status = calc.m_calc(string_7, &result, 0);
  EXPECT_EQ(status, ERROR);

  // test 8
  char string_8[255] = "log)=";
  status = calc.m_calc(string_8, &result, 0);
  EXPECT_EQ(status, ERROR);

  // test 9
  char string_9[255] = "log(12=";
  status = calc.m_calc(string_9, &result, 0);
  EXPECT_EQ(status, ERROR);
}

//  test
TEST_F(TestModel, algebraic_equation_test) {
  double result = 0;
  int status = 0;

  // test 1
  char string_1[255] = "sin(1.0009-12.53)*cos(1.25*2^3)=";
  status = calc.m_calc(string_1, &result, 0);

  EXPECT_EQ(status, OK);
  ASSERT_NEAR(result, -0.722457, 1e-6);

  // test 2
  char string_2[255] = "log(15.3)*log(-10)+15-1*15/14=";
  status = calc.m_calc(string_2, &result, 0);

  EXPECT_EQ(status, OK);
  ASSERT_TRUE(std::isnan(result));

  // test 3
  char string_3[255] = "2^2^3*3^2^3=";
  status = calc.m_calc(string_3, &result, 0);

  EXPECT_EQ(status, OK);
  ASSERT_NEAR(result, 1679616.000000, 1e-6);

  // test 4
  char string_4[255] = "1/0=";
  status = calc.m_calc(string_4, &result, 0);
  ASSERT_TRUE(std::isinf(result));
  EXPECT_EQ(status, OK);

  // test 5
  char string_5[255] = "0/0=";
  status = calc.m_calc(string_5, &result, 0);
  EXPECT_EQ(status, OK);
  ASSERT_TRUE(std::isnan(result));

  // test 6
  char string_6[255] =
      "sin(30)+cos(30)*tan(30)/acos(0.15)^asin(0.15)+(-atan(0.15))=";
  status = calc.m_calc(string_6, &result, 0);
  EXPECT_EQ(status, OK);
  ASSERT_NEAR(result, -2.074118, 1e-6);

  // test 7
  char string_7[255] = "17mod13mod5=";
  status = calc.m_calc(string_7, &result, 0);
  EXPECT_EQ(status, OK);
  ASSERT_NEAR(result, 4, 1e-6);
}

// credit_calc test
TEST_F(TestModel, credit_calc_test) {
  // test 1
  double total_sum = 2400000;
  int time = 20;
  double procent_rate = 9.5;
  int type = 1;
  double month_pay_1[10] = {0};
  double overpay = 0;
  double total_pay = 0;

  int status = calc.credit_calc(total_sum, time, procent_rate, type,
                                month_pay_1, &overpay, &total_pay);

  EXPECT_EQ(status, OK);
  ASSERT_NEAR(month_pay_1[0], 130223.98, 1e-2);
  ASSERT_NEAR(overpay, 204479.60, 1e-2);
  ASSERT_NEAR(total_pay, 2604479.60, 1e-2);

  // test 2
  total_sum = 2400000;
  time = -5;
  procent_rate = 9.5;
  type = 1;
  double month_pay_2[10] = {0};
  overpay = 0;
  total_pay = 0;

  status = calc.credit_calc(total_sum, time, procent_rate, type, month_pay_2,
                            &overpay, &total_pay);

  EXPECT_EQ(status, ERROR);

  // test 3
  total_sum = 2400000;
  time = 25;
  procent_rate = -5;
  type = 1;
  double month_pay_3[10] = {0};
  overpay = 0;
  total_pay = 0;

  status = calc.credit_calc(total_sum, time, procent_rate, type, month_pay_3,
                            &overpay, &total_pay);

  EXPECT_EQ(status, ERROR);

  // test 4
  total_sum = -2400000;
  time = 25;
  procent_rate = 5;
  type = 1;
  double month_pay_4[10] = {0};
  overpay = 0;
  total_pay = 0;

  status = calc.credit_calc(total_sum, time, procent_rate, type, month_pay_4,
                            &overpay, &total_pay);

  EXPECT_EQ(status, ERROR);

  // test 5
  total_sum = 2400000;
  time = 25;
  procent_rate = 5;
  type = 3;
  double month_pay_5[10] = {0};
  overpay = 0;
  total_pay = 0;

  status = calc.credit_calc(total_sum, time, procent_rate, type, month_pay_5,
                            &overpay, &total_pay);

  EXPECT_EQ(status, ERROR);

  // test 6
  total_sum = 240000;
  time = 7;
  procent_rate = 9.5;
  type = 2;
  double month_pay_6[10] = {0};
  overpay = 0;
  total_pay = 0;

  status = calc.credit_calc(total_sum, time, procent_rate, type, month_pay_6,
                            &overpay, &total_pay);

  EXPECT_EQ(status, OK);
  ASSERT_NEAR(month_pay_6[0], 36185.71, 1e-2);
  ASSERT_NEAR(month_pay_6[1], 35914.29, 1e-2);
  ASSERT_NEAR(month_pay_6[2], 35642.86, 1e-2);
  ASSERT_NEAR(month_pay_6[3], 35371.43, 1e-2);
  ASSERT_NEAR(month_pay_6[4], 35100.00, 1e-2);
  ASSERT_NEAR(month_pay_6[5], 34828.57, 1e-2);
  ASSERT_NEAR(month_pay_6[6], 34557.14, 1e-2);
  ASSERT_NEAR(overpay, 7600, 1e-2);
  ASSERT_NEAR(total_pay, 247600, 1e-2);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

}  // namespace s21