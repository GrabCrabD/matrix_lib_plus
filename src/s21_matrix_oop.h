#ifndef SRC_MATRIX_OOP_H_
#define SRC_MATRIX_OOP_H_

#include <cmath>
#include <iostream>
#include <stdexcept>
#include <utility>

#define kEpsilon 10e-7

class S21Matrix {
 public:
  S21Matrix();
  S21Matrix(int rows, int cols);

  S21Matrix(const S21Matrix& other);
  S21Matrix& operator=(const S21Matrix& other);

  S21Matrix(S21Matrix&& other) noexcept;
  S21Matrix& operator=(S21Matrix&& other) noexcept;

  ~S21Matrix();

  double& operator()(int row, int col);
  const double& operator()(int row, int col) const;

  int GetRows() const noexcept;
  int GetCols() const noexcept;
  void SetRows(int newRows);
  void SetCols(int newCols);

  bool EqMatrix(const S21Matrix& other);
  bool operator==(const S21Matrix& other);

  void SumMatrix(const S21Matrix& other);
  S21Matrix& operator+=(const S21Matrix& other);
  S21Matrix operator+(const S21Matrix& other) const;

  void SubMatrix(const S21Matrix& other);
  S21Matrix& operator-=(const S21Matrix& other);
  S21Matrix operator-(const S21Matrix& other) const;

  void MulNumber(const double num) noexcept;
  void MulMatrix(const S21Matrix& other);
  S21Matrix operator*(double num) noexcept;
  friend S21Matrix operator*(double num, S21Matrix& matrix) noexcept;
  S21Matrix& operator*=(double num);
  S21Matrix operator*(const S21Matrix& other);
  S21Matrix& operator*=(const S21Matrix& other);

  S21Matrix Transpose();

  S21Matrix MakeMinor(int current_i, int current_j, int size);
  double Determinant();
  S21Matrix CalcComplements();
  S21Matrix InverseMatrix();

 private:
  int rows_, cols_;
  double** matrix_;
  void ResizeMatrix(int newRows, int newCols);
};

#endif  // SRC_MATRIX_OOP_H_
