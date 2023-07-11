#include <gtest/gtest.h>

#include "s21_matrix_oop.h"

TEST(S21MatrixTest, Constructor) {
  S21Matrix matrix(2, 3);
  EXPECT_EQ(matrix.GetRows(), 2);
  EXPECT_EQ(matrix.GetCols(), 3);
}

TEST(S21MatrixTest, Constructor2) {
  S21Matrix matrix(2, 2);
  ASSERT_ANY_THROW(matrix(3, 2));
}

TEST(S21MatrixTest, Move) {
  S21Matrix matrix(2, 3);
  S21Matrix copyMatrix = matrix;
  S21Matrix matrix2 = std::move(matrix);
  EXPECT_EQ(copyMatrix == matrix2, true);
}

TEST(S21MatrixTest, Setters) {
  S21Matrix matrix(2, 2);
  matrix.SetRows(3);
  matrix.SetCols(3);
  EXPECT_EQ(matrix.GetRows(), 3);
  EXPECT_EQ(matrix.GetCols(), 3);
}

TEST(S21MatrixTest, EqMatrix) {
  S21Matrix matrix1(2, 3);
  S21Matrix matrix2(2, 3);
  S21Matrix matrix3(3, 2);
  EXPECT_EQ((matrix1 == matrix2), true);
  EXPECT_NE((matrix1 == matrix3), true);
  EXPECT_NE((matrix2 == matrix3), true);
}

TEST(S21MatrixTest, AssignmentOperator) {
  S21Matrix matrix1(2, 2);
  matrix1(0, 0) = 1.0;
  matrix1(0, 1) = 2.0;
  matrix1(1, 0) = 3.0;
  matrix1(1, 1) = 4.0;

  S21Matrix matrix2;
  matrix2 = matrix1;

  EXPECT_EQ(matrix2.GetRows(), 2);
  EXPECT_EQ(matrix2.GetCols(), 2);
  EXPECT_EQ(matrix2(0, 0), 1.0);
  EXPECT_EQ(matrix2(0, 1), 2.0);
  EXPECT_EQ(matrix2(1, 0), 3.0);
  EXPECT_EQ(matrix2(1, 1), 4.0);
}

TEST(S21MatrixTest, SumMatrix) {
  S21Matrix matrix1(2, 2);
  matrix1(0, 1) = 2.0;
  matrix1(0, 0) = 1.0;
  matrix1(1, 0) = 3.0;
  matrix1(1, 1) = 4.0;

  S21Matrix matrix2(2, 2);
  matrix2(0, 0) = 5.0;
  matrix2(0, 1) = 6.0;
  matrix2(1, 0) = 7.0;
  matrix2(1, 1) = 8.0;

  S21Matrix result = matrix1 + matrix2;

  EXPECT_EQ(result.GetRows(), 2);
  EXPECT_EQ(result.GetCols(), 2);
  EXPECT_EQ(result(0, 0), 6.0);
  EXPECT_EQ(result(0, 1), 8.0);
  EXPECT_EQ(result(1, 0), 10.0);
  EXPECT_EQ(result(1, 1), 12.0);
}

TEST(S21MatrixTest, AdditionAssignment) {
  S21Matrix matrix1(2, 2);
  matrix1(0, 1) = 2.0;
  matrix1(0, 0) = 1.0;
  matrix1(1, 0) = 3.0;
  matrix1(1, 1) = 4.0;

  S21Matrix matrix2(2, 2);
  matrix2(0, 0) = 5.0;
  matrix2(0, 1) = 6.0;
  matrix2(1, 0) = 7.0;
  matrix2(1, 1) = 8.0;

  matrix1 += matrix2;

  EXPECT_EQ(matrix1(0, 0), 6.0);
  EXPECT_EQ(matrix1(0, 1), 8.0);
  EXPECT_EQ(matrix1(1, 0), 10.0);
  EXPECT_EQ(matrix1(1, 1), 12.0);
}

TEST(S21MatrixTest, SumMatrix_NotEq) {
  S21Matrix matrix1(2, 1);
  matrix1(0, 0) = 1.0;
  matrix1(1, 0) = 3.0;

  S21Matrix matrix2(2, 2);
  matrix2(0, 0) = 5.0;
  matrix2(0, 1) = 6.0;
  matrix2(1, 0) = 7.0;
  matrix2(1, 1) = 8.0;

  ASSERT_ANY_THROW(matrix1 + matrix2);
}

TEST(S21MatrixTest, SubMatrix) {
  S21Matrix matrix1(2, 2);
  matrix1(0, 0) = 1.0;
  matrix1(0, 1) = 2.0;
  matrix1(1, 0) = 3.0;
  matrix1(1, 1) = 4.0;

  S21Matrix matrix2(2, 2);
  matrix2(0, 0) = 5.0;
  matrix2(0, 1) = 6.0;
  matrix2(1, 0) = 7.0;
  matrix2(1, 1) = 8.0;

  S21Matrix result = matrix1 - matrix2;

  EXPECT_EQ(result(0, 0), -4.0);
  EXPECT_EQ(result(0, 1), -4.0);
  EXPECT_EQ(result(1, 0), -4.0);
  EXPECT_EQ(result(1, 1), -4.0);
}

TEST(S21MatrixTest, DifferenceAssignment) {
  S21Matrix matrix1(2, 2);
  matrix1(0, 0) = 1.0;
  matrix1(0, 1) = 2.0;
  matrix1(1, 0) = 3.0;
  matrix1(1, 1) = 4.0;

  S21Matrix matrix2(2, 2);
  matrix2(0, 0) = 5.0;
  matrix2(0, 1) = 6.0;
  matrix2(1, 0) = 7.0;
  matrix2(1, 1) = 8.0;

  matrix1 -= matrix2;

  EXPECT_EQ(matrix1(0, 0), -4.0);
  EXPECT_EQ(matrix1(0, 1), -4.0);
  EXPECT_EQ(matrix1(1, 0), -4.0);
  EXPECT_EQ(matrix1(1, 1), -4.0);
}

TEST(S21MatrixTest, SubMatrix_NotEq) {
  S21Matrix matrix1(2, 1);
  matrix1(0, 0) = 1.0;
  matrix1(1, 0) = 3.0;

  S21Matrix matrix2(2, 2);
  matrix2(0, 0) = 5.0;
  matrix2(0, 1) = 6.0;
  matrix2(1, 0) = 7.0;
  matrix2(1, 1) = 8.0;

  ASSERT_ANY_THROW(matrix1 - matrix2);
}

TEST(S21MatrixTest, MulNumber) {
  S21Matrix matrix1(2, 2);
  matrix1(0, 0) = 1.0;
  matrix1(0, 1) = 2.0;
  matrix1(1, 0) = 3.0;
  matrix1(1, 1) = 4.0;

  S21Matrix result = matrix1 * 5.0;

  EXPECT_EQ(result(0, 0), 5.0);
  EXPECT_EQ(result(0, 1), 10.0);
  EXPECT_EQ(result(1, 0), 15.0);
  EXPECT_EQ(result(1, 1), 20.0);
}

TEST(S21MatrixTest, MulNumberFirstNum) {
  S21Matrix matrix1(2, 2);
  matrix1(0, 0) = 1.0;
  matrix1(0, 1) = 2.0;
  matrix1(1, 0) = 3.0;
  matrix1(1, 1) = 4.0;

  S21Matrix result = 5.0 * matrix1;

  EXPECT_EQ(result(0, 0), 5.0);
  EXPECT_EQ(result(0, 1), 10.0);
  EXPECT_EQ(result(1, 0), 15.0);
  EXPECT_EQ(result(1, 1), 20.0);
}

TEST(S21MatrixTest, MulNumberWithAssignment) {
  S21Matrix matrix1(2, 2);
  matrix1(0, 0) = 1.0;
  matrix1(0, 1) = 2.0;
  matrix1(1, 0) = 3.0;
  matrix1(1, 1) = 4.0;

  matrix1 *= 5.0;

  EXPECT_EQ(matrix1(0, 0), 5.0);
  EXPECT_EQ(matrix1(0, 1), 10.0);
  EXPECT_EQ(matrix1(1, 0), 15.0);
  EXPECT_EQ(matrix1(1, 1), 20.0);
}

TEST(S21MatrixTest, MulMatrix) {
  S21Matrix matrix1(2, 2);
  matrix1(0, 0) = 1.0;
  matrix1(0, 1) = 2.0;
  matrix1(1, 0) = 3.0;
  matrix1(1, 1) = 4.0;

  S21Matrix matrix2(2, 2);
  matrix2(0, 0) = 5.0;
  matrix2(0, 1) = 6.0;
  matrix2(1, 0) = 7.0;
  matrix2(1, 1) = 8.0;

  S21Matrix result = matrix1 * matrix2;

  EXPECT_EQ(result(0, 0), 19.0);
  EXPECT_EQ(result(0, 1), 22.0);
  EXPECT_EQ(result(1, 0), 43.0);
  EXPECT_EQ(result(1, 1), 50.0);
}

TEST(S21MatrixTest, MulMatrixWithAssignment) {
  S21Matrix matrix1(2, 2);
  matrix1(0, 0) = 1.0;
  matrix1(0, 1) = 2.0;
  matrix1(1, 0) = 3.0;
  matrix1(1, 1) = 4.0;

  S21Matrix matrix2(2, 2);
  matrix2(0, 0) = 5.0;
  matrix2(0, 1) = 6.0;
  matrix2(1, 0) = 7.0;
  matrix2(1, 1) = 8.0;

  matrix1 *= matrix2;

  EXPECT_EQ(matrix1(0, 0), 19.0);
  EXPECT_EQ(matrix1(0, 1), 22.0);
  EXPECT_EQ(matrix1(1, 0), 43.0);
  EXPECT_EQ(matrix1(1, 1), 50.0);
}

TEST(S21MatrixTest, MulMatrix_NotEqRowsAndCols) {
  S21Matrix matrix1(2, 1);
  matrix1(0, 0) = 1.0;
  matrix1(1, 0) = 3.0;

  S21Matrix matrix2(2, 2);
  matrix2(0, 0) = 5.0;
  matrix2(0, 1) = 6.0;
  matrix2(1, 0) = 7.0;
  matrix2(1, 1) = 8.0;

  ASSERT_ANY_THROW(matrix1 * matrix2);
}

TEST(S21MatrixTest, Determinant) {
  S21Matrix matrix(3, 3);
  matrix(0, 0) = 1.0;
  matrix(0, 1) = 2.0;
  matrix(0, 2) = 3.0;
  matrix(1, 0) = 4.0;
  matrix(1, 1) = 5.0;
  matrix(1, 2) = 6.0;
  matrix(2, 0) = 7.0;
  matrix(2, 1) = 8.0;
  matrix(2, 2) = 9.0;

  double determinant = matrix.Determinant();

  EXPECT_EQ(determinant, 0.0);
}

TEST(S21MatrixTest, Determinant_NonSquareMatrix) {
  S21Matrix matrix(2, 3);
  matrix(0, 0) = 1.0;
  matrix(0, 1) = 2.0;
  matrix(0, 2) = 3.0;
  matrix(1, 0) = 4.0;
  matrix(1, 1) = 5.0;
  matrix(1, 2) = 6.0;

  ASSERT_ANY_THROW(matrix.Determinant());
}

TEST(S21MatrixTest, Transpose) {
  S21Matrix matrix(3, 3);
  matrix(0, 0) = 1.0;
  matrix(0, 1) = 2.0;
  matrix(0, 2) = 3.0;
  matrix(1, 0) = 4.0;
  matrix(1, 1) = 5.0;
  matrix(1, 2) = 6.0;
  matrix(2, 0) = 7.0;
  matrix(2, 1) = 8.0;
  matrix(2, 2) = 9.0;

  S21Matrix result = matrix.Transpose();

  EXPECT_EQ(result(0, 0), 1.0);
  EXPECT_EQ(result(0, 1), 4.0);
  EXPECT_EQ(result(0, 2), 7.0);
  EXPECT_EQ(result(1, 0), 2.0);
  EXPECT_EQ(result(1, 1), 5.0);
  EXPECT_EQ(result(1, 2), 8.0);
  EXPECT_EQ(result(2, 0), 3.0);
  EXPECT_EQ(result(2, 1), 6.0);
  EXPECT_EQ(result(2, 2), 9.0);
}

TEST(S21MatrixTest, CalcComplements) {
  S21Matrix matrix(3, 3);
  matrix(0, 0) = 1.0;
  matrix(0, 1) = 2.0;
  matrix(0, 2) = 3.0;
  matrix(1, 0) = 0.0;
  matrix(1, 1) = 4.0;
  matrix(1, 2) = 2.0;
  matrix(2, 0) = 5.0;
  matrix(2, 1) = 2.0;
  matrix(2, 2) = 1.0;

  S21Matrix complements = matrix.CalcComplements();

  EXPECT_DOUBLE_EQ(complements(0, 0), 0.0);
  EXPECT_DOUBLE_EQ(complements(0, 1), 10.0);
  EXPECT_DOUBLE_EQ(complements(0, 2), -20.0);
  EXPECT_DOUBLE_EQ(complements(1, 0), 4.0);
  EXPECT_DOUBLE_EQ(complements(1, 1), -14.0);
  EXPECT_DOUBLE_EQ(complements(1, 2), 8.0);
  EXPECT_DOUBLE_EQ(complements(2, 0), -8.0);
  EXPECT_DOUBLE_EQ(complements(2, 1), -2.0);
  EXPECT_DOUBLE_EQ(complements(2, 2), 4.0);
}

TEST(S21MatrixTest, CalcComplements_NonSquareMatrix) {
  S21Matrix matrix(2, 3);
  matrix(0, 0) = 1;
  matrix(0, 1) = 2;
  matrix(0, 2) = 3;
  matrix(1, 0) = 4;
  matrix(1, 1) = 5;
  matrix(1, 2) = 6;
  ASSERT_ANY_THROW(matrix.CalcComplements());
}

TEST(S21MatrixTest, CalcComplements_OneRowColMatrix) {
  S21Matrix matrix(1, 1);
  S21Matrix complements = matrix.CalcComplements();
  EXPECT_DOUBLE_EQ(complements(0, 0), 1.0);
}

TEST(S21MatrixTest, InverseMatrix) {
  S21Matrix matrix(2, 2);
  matrix(0, 0) = 1.0;
  matrix(0, 1) = 2.0;
  matrix(1, 0) = 3.0;
  matrix(1, 1) = 4.0;

  S21Matrix inverse = matrix.InverseMatrix();

  EXPECT_EQ(inverse.GetRows(), 2);
  EXPECT_EQ(inverse.GetCols(), 2);
  EXPECT_NEAR(inverse(0, 0), -2.0, 1e-7);
  EXPECT_NEAR(inverse(0, 1), 1.0, 1e-7);
  EXPECT_NEAR(inverse(1, 0), 1.5, 1e-7);
  EXPECT_NEAR(inverse(1, 1), -0.5, 1e-7);
}

TEST(S21MatrixTest, InverseMatrixZeroDeterminant) {
  S21Matrix matrix(3, 3);
  matrix(0, 0) = 1.0;
  matrix(0, 1) = 2.0;
  matrix(0, 2) = 3.0;
  matrix(1, 0) = 4.0;
  matrix(1, 1) = 5.0;
  matrix(1, 2) = 6.0;
  matrix(2, 0) = 7.0;
  matrix(2, 1) = 8.0;
  matrix(2, 2) = 9.0;

  ASSERT_ANY_THROW(matrix.InverseMatrix());
}

TEST(S21MatrixTest, InverseMatrix_NonSquare) {
  S21Matrix matrix(1, 2);
  matrix(0, 0) = 1.0;
  matrix(0, 1) = 2.0;

  ASSERT_ANY_THROW(matrix.InverseMatrix());
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
