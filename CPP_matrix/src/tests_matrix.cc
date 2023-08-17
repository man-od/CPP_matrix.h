#include <gtest/gtest.h>

#include <utility>

#include "matrix_oop.h"

// Проверка размеров матрицы по умолчанию
TEST(Constructor, DefaultConstructor) {
  S21Matrix matrix;
  ASSERT_EQ(matrix.GetRows(), 0);
  ASSERT_EQ(matrix.GetCols(), 0);
}

// Проверка на throw к обращению матрицы
TEST(Constructor, DefaultConstructorEXPECT) {
  S21Matrix matrix;
  EXPECT_ANY_THROW(matrix(4, 4));
}

// Проверка на использование конструктора с параметрами
TEST(Constructor, parameterizedCconstructor) {
  S21Matrix matrix(2, 3);
  EXPECT_EQ(matrix.GetRows(), 2);
  EXPECT_EQ(matrix.GetCols(), 3);
}

// Проверка на throw конструктора с параметрами
TEST(Constructor, parameterizedCconstructorEx) {
  EXPECT_ANY_THROW(S21Matrix matrix(0, -2));
}

// Проверка на копирование
TEST(Constructor, copyConstructor) {
  S21Matrix matrix(2, 3);
  S21Matrix res(matrix);
  EXPECT_EQ(res.GetRows(), 2);
  EXPECT_EQ(res.GetCols(), 3);
  EXPECT_EQ(matrix == res, true);
}

// Проверка на перемещение
TEST(Constructor, moveConstructor) {
  S21Matrix matrix(2, 3);
  S21Matrix res(std::move(matrix));
  EXPECT_EQ(res.GetRows(), 2);
  EXPECT_EQ(res.GetCols(), 3);
  EXPECT_EQ(matrix.GetRows(), 0);
  EXPECT_EQ(matrix.GetCols(), 0);
}

// Проверка на set
TEST(GetterAndSetter, SetRows) {
  S21Matrix matrix(2, 3);
  matrix.SetRows(3);
  matrix.SetCols(3);
  matrix(0, 0) = 1.1;
  matrix(0, 1) = -2.0;
  matrix(1, 0) = 10;
  matrix(1, 1) = 3.1415;
  EXPECT_EQ(matrix(1, 1), 3.1415);
  EXPECT_EQ(matrix.GetRows(), 3);
  EXPECT_EQ(matrix.GetCols(), 3);
}

// Проверка на throw в set
TEST(GetterAndSetter, SetRowsEx2) {
  S21Matrix matrix;
  matrix.SetRows(2);
  EXPECT_ANY_THROW(matrix(0, 1));
}

// Проверка на set
TEST(GetterAndSetter, setCols) {
  S21Matrix matrix(2, 3);
  matrix(1, 1) = 4.4;
  EXPECT_EQ(matrix(1, 1), 4.4);
  EXPECT_EQ(matrix.GetRows(), 2);
  EXPECT_EQ(matrix.GetCols(), 3);
}

// Проверка на throw в set
TEST(GetterAndSetter, SetRowsEx3) {
  S21Matrix matrix;
  matrix.SetCols(2);
  EXPECT_ANY_THROW(matrix(0, 1));
}

TEST(assignmentOperator, braketsTrow) {
  S21Matrix m(2, 3);
  EXPECT_ANY_THROW(m(1, 5));
}

// Проверка на копирование
TEST(functionalTest, copy) {
  S21Matrix a(2, 2);
  S21Matrix b(2, 2);
  a(1, 1) = 1.1;
  b(1, 1) = 2.2;
  a = b;
  EXPECT_DOUBLE_EQ(a(1, 1), 2.2);
}

TEST(functionalTest, MulMatrixOp2) {
  S21Matrix a(3, 2);
  a(0, 0) = 1;
  a(0, 1) = 4;
  a(1, 0) = 2;
  a(1, 1) = 5;
  a(2, 0) = 3;
  a(2, 1) = 6;
  S21Matrix b(2, 3);
  b(0, 0) = 1;
  b(0, 1) = -1;
  b(0, 2) = 1;
  b(1, 0) = 2;
  b(1, 1) = 3;
  b(1, 2) = 4;
  S21Matrix res(3, 3);
  res(0, 0) = 9;
  res(0, 1) = 11;
  res(0, 2) = 17;
  res(1, 0) = 12;
  res(1, 1) = 13;
  res(1, 2) = 22;
  res(2, 0) = 15;
  res(2, 1) = 15;
  res(2, 2) = 27;
  EXPECT_TRUE(a * b == res);
}

TEST(functionalTest, LeftSum1) {
  S21Matrix a(2, 2);
  a(0, 0) = 4;
  a(0, 1) = 3;
  a(1, 0) = 1;
  a(1, 1) = -1;
  S21Matrix b(2, 2);
  b(0, 0) = 9;
  b(0, 1) = 0;
  b(1, 0) = -5;
  b(1, 1) = 6;
  S21Matrix res(2, 2);
  res(0, 0) = 13;
  res(0, 1) = 3;
  res(1, 0) = -4;
  res(1, 1) = 5;
  EXPECT_TRUE((a += b) == res);
}

// Проверка на сравнение
TEST(functionalTest, EqMatrix1) {
  S21Matrix m1(3, 3);
  S21Matrix m2(3, 3);
  m1(0, 0) = 4.3;
  m1(0, 1) = 3;
  m1(1, 0) = 11.3;
  m1(1, 1) = -1.3;
  m2(0, 0) = 4.3;
  m2(0, 1) = 3;
  m2(1, 0) = 11.3;
  m2(1, 1) = -1.3;
  EXPECT_TRUE(m1.EqMatrix(m2));
}

// Проверка на сравнение
TEST(functionalTest, EqMatrix2) {
  S21Matrix a(2, 2);
  S21Matrix b(2, 2);
  a(0, 0) = 4.3;
  a(0, 1) = 3;
  a(1, 0) = 11.3;
  a(1, 1) = -1.3;
  b(0, 0) = 4.3;
  b(0, 1) = 3;
  b(1, 0) = 10;
  b(1, 1) = -1.3;
  EXPECT_FALSE(a.EqMatrix(b));
}

TEST(functionalTest, Plus) {
  S21Matrix a(2, 2);
  S21Matrix b(2, 2);
  a(1, 1) = 1.1;
  b(1, 1) = 2.2;
  S21Matrix res = a + b;
  EXPECT_DOUBLE_EQ(res(1, 1), 3.3);
}

TEST(functionalTest, PlusEx) {
  S21Matrix a(2, 3);
  S21Matrix b(2, 2);
  a(1, 1) = 1.1;
  b(1, 1) = 2.2;
  EXPECT_ANY_THROW(S21Matrix res = a + b);
}

TEST(functionalTest, SubMatrix1) {
  S21Matrix a(2, 3);
  S21Matrix b(2, 2);
  a(0, 0) = 4.3;
  a(0, 1) = 3;
  a(0, 2) = 7;
  a(1, 0) = 11.3;
  a(1, 1) = -1.3;
  a(1, 2) = -1;
  b(0, 0) = 4.3;
  b(0, 1) = 3;
  b(1, 0) = 11.3;
  b(1, 1) = -1.3;
  EXPECT_THROW(a.SumMatrix(b), std::invalid_argument);
}

TEST(functionalTest, SubMatrix) {
  S21Matrix a(2, 2);
  S21Matrix b(2, 2);
  a(1, 1) = 1.1;
  b(1, 1) = 2.2;
  S21Matrix res = a - b;
  EXPECT_DOUBLE_EQ(res(1, 1), -1.1);
}

TEST(functionalTest, MulNumber) {
  S21Matrix a(2, 2);
  a(0, 0) = 4;
  a(0, 1) = 3;
  a(1, 0) = 0;
  a(1, 1) = -1;
  const double num = 2.5;
  S21Matrix res(2, 2);
  res(0, 0) = 10;
  res(0, 1) = 7.5;
  res(1, 0) = 0;
  res(1, 1) = -2.5;
  a.MulNumber(num);
  EXPECT_TRUE(a.EqMatrix(res));
}

TEST(functionalTest, MultMatrixNum2) {
  S21Matrix a(3, 2);
  a(1, 1) = 1.1;
  a.MulNumber(2);
  EXPECT_DOUBLE_EQ(a(1, 1), 2.2);
}

TEST(functionalTest, MulMatrix) {
  S21Matrix a(3, 2);
  a(1, 1) = 1.1;
  a(0, 1) = 4;
  a(1, 0) = 2;
  a(1, 1) = 5;
  a(2, 0) = 3;
  a(2, 1) = 6;
  S21Matrix b(3, 4);
  a(1, 1) = 1.1;
  b(0, 1) = -1;
  b(0, 2) = 1;
  b(0, 3) = 4;
  b(1, 0) = 2;
  b(1, 1) = 3;
  b(1, 2) = 4;
  b(1, 3) = -5;
  b(2, 0) = 1;
  b(2, 1) = 1;
  b(2, 2) = 1;
  b(2, 3) = 1;
  EXPECT_THROW(a.MulMatrix(b), std::out_of_range);
}

TEST(functionalTest, Transponse) {
  S21Matrix a(3, 2);
  a(0, 0) = 1;
  a(0, 1) = 4;
  a(1, 0) = 2;
  a(1, 1) = 5;
  a(2, 0) = 3;
  a(2, 1) = 6;
  S21Matrix res(2, 3);
  res(0, 0) = 1;
  res(0, 1) = 2;
  res(0, 2) = 3;
  res(1, 0) = 4;
  res(1, 1) = 5;
  res(1, 2) = 6;
  S21Matrix temp(2, 3);
  temp = a.Transpose();
  EXPECT_TRUE(res.EqMatrix(temp));
}

TEST(functionalTest, calcComplements) {
  S21Matrix m(3, 3);
  m(0, 0) = 1;
  m(0, 1) = 2;
  m(0, 2) = 3;

  m(1, 0) = 0;
  m(1, 1) = 4;
  m(1, 2) = 2;

  m(2, 0) = 5;
  m(2, 1) = 2;
  m(2, 2) = 1;

  m = m.CalcComplements();

  EXPECT_EQ(m(0, 0), 0);
  EXPECT_EQ(m(0, 1), 10);
  EXPECT_EQ(m(0, 2), -20);
  EXPECT_EQ(m(1, 0), 4);
  EXPECT_EQ(m(1, 1), -14);
  EXPECT_EQ(m(1, 2), 8);
  EXPECT_EQ(m(2, 0), -8);
  EXPECT_EQ(m(2, 1), -2);
  EXPECT_EQ(m(2, 2), 4);
}

TEST(functionalTest, calcComplementsEx) {
  S21Matrix m(4, 3);

  EXPECT_ANY_THROW(m.CalcComplements());
}

TEST(functionalTest, determinant) {
  S21Matrix m(4, 4);
  m(0, 0) = 9;
  m(0, 1) = 2;
  m(0, 2) = 2;
  m(0, 3) = 4;

  m(1, 0) = 3;
  m(1, 1) = 4;
  m(1, 2) = 4;
  m(1, 3) = 4;

  m(2, 0) = 4;
  m(2, 1) = 4;
  m(2, 2) = 9;
  m(2, 3) = 9;

  m(3, 0) = 1;
  m(3, 1) = 1;
  m(3, 2) = 5;
  m(3, 3) = 1;
  EXPECT_EQ(m.Determinant(), -578);
  S21Matrix m1(1, 1);
  m1(0, 0) = 10;
  EXPECT_EQ(m1.Determinant(), 10);
  S21Matrix m2(2, 2);
  m2(0, 0) = 1.1;
  m2(0, 1) = 3.5;
  m2(1, 0) = -2;
  m2(1, 1) = 4;
  EXPECT_DOUBLE_EQ(m2.Determinant(), 11.4);
}

TEST(functionalTest, determinant2) {
  S21Matrix a(3, 3);
  a(0, 0) = 1;
  a(0, 1) = 2;
  a(0, 2) = 3;
  a(1, 0) = 4;
  a(1, 1) = 5;
  a(1, 2) = 6;
  a(2, 0) = 7;
  a(2, 1) = 8;
  a(2, 2) = 10;
  EXPECT_DOUBLE_EQ(a.Determinant(), -3);
}

TEST(functionalTest, determinantEx) {
  S21Matrix m(4, 3);

  EXPECT_ANY_THROW(m.Determinant());
}

TEST(functionalTest, inverseMatrix) {
  S21Matrix m(3, 3);
  m(0, 0) = 4;
  m(0, 1) = -2;
  m(0, 2) = 1;
  m(1, 0) = 1;
  m(1, 1) = 6;
  m(1, 2) = -2;
  m(2, 0) = 1;
  m(2, 1) = 0;
  m(2, 2) = 0;

  m = m.InverseMatrix();

  EXPECT_EQ(m(0, 1), 0);
  EXPECT_EQ(m(0, 2), 1);
  EXPECT_EQ(m(1, 0), 1);
  EXPECT_EQ(m(2, 0), 3);
  EXPECT_EQ(m(2, 1), 1);
  EXPECT_EQ(m(2, 2), -13);
}

TEST(functionalTest, inverseMatrixEx) {
  S21Matrix m(3, 3);
  m(0, 0) = 1;
  m(0, 1) = 1;
  m(0, 2) = 3;
  m(1, 0) = 4;
  m(1, 1) = 4;
  m(1, 2) = 6;
  m(2, 0) = 4;
  m(2, 1) = 4;
  m(2, 2) = 9;
  EXPECT_EQ(m.Determinant(), 0);
  EXPECT_ANY_THROW(m.InverseMatrix());
}

TEST(functionalTest, inverseMatrixEx2) {
  S21Matrix m(6, 3);
  m(0, 0) = 1;
  m(0, 1) = 1;
  m(0, 2) = 3;
  m(1, 0) = 4;
  m(1, 1) = 4;
  m(1, 2) = 6;
  m(2, 0) = 4;
  m(2, 1) = 4;
  m(2, 2) = 9;
  EXPECT_ANY_THROW(m.Determinant());
}

TEST(functionalTest, braketEx) {
  S21Matrix m(1, 1);
  EXPECT_ANY_THROW(m(5, 0) = 5);
}

TEST(functionalTest, braketEx2) {
  S21Matrix m(3, 3);
  m(1, 1) = 1;
  EXPECT_EQ(m(1, 1), 1);
  EXPECT_ANY_THROW(m(-1, -1));
  EXPECT_ANY_THROW(m(0, -1));
  EXPECT_ANY_THROW(m(-1, 0));
  EXPECT_ANY_THROW(m(-1, 1));
}

TEST(functionalTest, Eq) {
  S21Matrix a(2, 2);
  a(0, 0) = 4.3;
  a(0, 1) = 3;
  a(1, 0) = 11.3;
  a(1, 1) = -1.3;
  S21Matrix b(2, 2);
  b(0, 0) = 4.3;
  b(0, 1) = 3;
  b(1, 0) = 11.3;
  b(1, 1) = -1.3;
  EXPECT_TRUE(a == b);
}

TEST(functionalTest, Eq2) {
  S21Matrix a(2, 2);
  a(0, 0) = 4.3;
  a(0, 1) = 3;
  a(1, 0) = 11.5;
  a(1, 1) = -1.3;
  S21Matrix b(2, 2);
  b(0, 0) = 4.3;
  b(0, 1) = 3;
  b(1, 0) = 11.3;
  b(1, 1) = -1.3;

  EXPECT_FALSE(a == b);
}

TEST(functionalTest, Sum) {
  S21Matrix a(2, 2);
  a(0, 0) = 4;
  a(0, 1) = 3;
  a(1, 0) = 1;
  a(1, 1) = -1;
  S21Matrix b(2, 2);
  b(0, 0) = 9;
  b(0, 1) = 0;
  b(1, 0) = -5;
  b(1, 1) = 6;

  S21Matrix res(2, 2);
  res(0, 0) = 13;
  res(0, 1) = 3;
  res(1, 0) = -4;
  res(1, 1) = 5;

  EXPECT_TRUE((a + b) == res);
}

TEST(functionalTest, Minus) {
  S21Matrix a(2, 2);
  S21Matrix b(2, 2);
  a(1, 1) = 1.1;
  b(1, 1) = 2.2;
  S21Matrix res = a - b;
  EXPECT_DOUBLE_EQ(res(1, 1), -1.1);
}

TEST(functionalTest, MinusEx) {
  S21Matrix a(2, 3);
  S21Matrix b(2, 2);
  a(1, 1) = 1.1;
  b(1, 1) = 2.2;
  EXPECT_ANY_THROW(S21Matrix res = a + b);
}

TEST(functionalTest, Minus2) {
  S21Matrix a(2, 2);
  S21Matrix b(2, 2);
  a(1, 1) = 1.1;
  b(1, 1) = 2.2;
  a -= b;
  EXPECT_DOUBLE_EQ(a(1, 1), -1.1);
}

TEST(functionalTest, MinusEx2) {
  S21Matrix a(2, 3);
  S21Matrix b(2, 2);
  a(1, 1) = 1.1;
  b(1, 1) = 2.2;
  EXPECT_ANY_THROW(a -= b);
}

TEST(functionalTest, MinusEx3) {
  S21Matrix a(2, 3);
  S21Matrix b(2, 2);
  a(1, 1) = 1.1;
  b(1, 1) = 2.2;
  EXPECT_ANY_THROW(a.SubMatrix(b));
}

TEST(functionalTest, MinusEx33) {
  S21Matrix a(2, 3);
  S21Matrix b(2, 2);
  a(1, 1) = 1.1;
  b(1, 1) = 2.2;
  EXPECT_ANY_THROW(a - b);
}

TEST(functionalTest, MultMatrix) {
  S21Matrix a(3, 2);
  S21Matrix b(2, 3);
  a(1, 1) = 1.1;
  b(1, 1) = 2;
  S21Matrix res = a * b;
  EXPECT_DOUBLE_EQ(res(1, 1), 2.2);
}

TEST(functionalTest, MultMatrixEx) {
  S21Matrix a(2, 3);
  S21Matrix b(2, 2);
  a(1, 1) = 1.1;
  b(1, 1) = 2.2;
  EXPECT_ANY_THROW(S21Matrix res = a * b);
}

TEST(functionalTest, MultMatrix4) {
  S21Matrix a(3, 2);
  S21Matrix b(2, 3);
  a(1, 1) = 1.1;
  b(1, 1) = 2;
  a *= b;
  EXPECT_DOUBLE_EQ(a(1, 1), 2.2);
}

TEST(functionalTest, MultMatrixEx5) {
  S21Matrix a(2, 3);
  S21Matrix b(2, 2);
  a(1, 1) = 1.1;
  b(1, 1) = 2.2;
  EXPECT_ANY_THROW(a *= b);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}