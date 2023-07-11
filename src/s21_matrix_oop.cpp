#include "s21_matrix_oop.h"

S21Matrix::S21Matrix() : rows_(0), cols_(0), matrix_(nullptr) {}
S21Matrix::S21Matrix(int rows, int cols)
    : rows_(rows), cols_(cols), matrix_(nullptr) {
  if (cols_ <= 0 || rows_ <= 0) {
    throw std::length_error("Размер матрицы должен быть больше или равен нулю");
  }
  matrix_ = new double*[rows_];
  for (int i = 0; i < rows_; ++i) {
    matrix_[i] = new double[cols_]();
  }
}

S21Matrix::S21Matrix(const S21Matrix& other)
    : rows_(other.rows_), cols_(other.cols_), matrix_(nullptr) {
  matrix_ = new double*[rows_];
  for (int i = 0; i < rows_; ++i) {
    matrix_[i] = new double[cols_];
    for (int j = 0; j < cols_; ++j) {
      matrix_[i][j] = other.matrix_[i][j];
    }
  }
}

S21Matrix& S21Matrix::operator=(const S21Matrix& other) {
  if (this != &other) {
    this->~S21Matrix();

    rows_ = other.rows_;
    cols_ = other.cols_;
    matrix_ = new double*[rows_];
    for (int i = 0; i < rows_; ++i) {
      matrix_[i] = new double[cols_];
      for (int j = 0; j < cols_; ++j) {
        matrix_[i][j] = other.matrix_[i][j];
      }
    }
  }
  return *this;
}

S21Matrix::S21Matrix(S21Matrix&& other) noexcept
    : rows_(other.rows_), cols_(other.cols_), matrix_(other.matrix_) {
  other.matrix_ = nullptr;
  other.cols_ = 0;
  other.rows_ = 0;
}

S21Matrix& S21Matrix::operator=(S21Matrix&& other) noexcept {
  if (this != &other) {
    std::swap(rows_, other.rows_);
    std::swap(cols_, other.cols_);
    std::swap(matrix_, other.matrix_);

    // Освобождаем ресурсы объекта other
    for (int i = 0; i < other.rows_; ++i) {
      delete[] other.matrix_[i];
    }
    delete[] other.matrix_;

    other.rows_ = 0;
    other.cols_ = 0;
    other.matrix_ = nullptr;
  }
  return *this;
}

S21Matrix::~S21Matrix() {
  for (int i = 0; i < rows_; ++i) {
    delete[] matrix_[i];
  }
  delete[] matrix_;
}

int S21Matrix::GetRows() const noexcept { return rows_; }
int S21Matrix::GetCols() const noexcept { return cols_; };
void S21Matrix::SetRows(int newRows) { ResizeMatrix(newRows, cols_); }
void S21Matrix::SetCols(int newCols) { ResizeMatrix(rows_, newCols); }

void S21Matrix::ResizeMatrix(int newRows, int newCols) {
  if (newRows < 0 || newCols < 0) {
    throw std::length_error("Размер матрицы должен быть больше или равен нулю");
  }
  double** newMatrix = new double*[newRows];
  for (int i = 0; i < newRows; ++i) {
    newMatrix[i] = new double[newCols];
  }

  for (int i = 0; i < std::min(rows_, newRows); ++i) {
    for (int j = 0; j < std::min(cols_, newCols); ++j) {
      newMatrix[i][j] = matrix_[i][j];
    }
  }

  if (rows_ < newRows) {
    for (int i = rows_; i < newRows; ++i) {
      for (int j = 0; j < newCols; ++j) {
        newMatrix[i][j] = 0.0;  // заполняем нулями
      }
    }
  } else if (cols_ < newCols) {
    for (int i = 0; i < newRows; ++i) {
      for (int j = cols_; j < newCols; ++j) {
        newMatrix[i][j] = 0.0;  // заполняем нулями
      }
    }
  }

  for (int i = 0; i < rows_; ++i) {
    delete[] matrix_[i];
  }
  delete[] matrix_;

  rows_ = newRows;
  cols_ = newCols;
  matrix_ = newMatrix;
}

bool S21Matrix::EqMatrix(const S21Matrix& other) {
  if ((rows_ == other.rows_) && (cols_ == other.cols_)) {
    for (int i = 0; i < rows_; ++i) {
      for (int j = 0; j < cols_; ++j) {
        if (std::abs(other(i, j) - (*this)(i, j)) >= kEpsilon) {
          return false;
        }
      }
    }
    return true;
  }
  return false;
}

bool S21Matrix::operator==(const S21Matrix& other) { return EqMatrix(other); }

void S21Matrix::SumMatrix(const S21Matrix& other) {
  if (cols_ != other.cols_ || rows_ != other.rows_) {
    throw std::length_error("матрицы разных размеров");
  }
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      matrix_[i][j] += other.matrix_[i][j];
    }
  }
}

S21Matrix& S21Matrix::operator+=(const S21Matrix& other) {
  SumMatrix(other);
  return *this;
}

S21Matrix S21Matrix::operator+(const S21Matrix& other) const {
  S21Matrix result{*this};
  result.SumMatrix(other);
  return result;
}

void S21Matrix::SubMatrix(const S21Matrix& other) {
  if (cols_ != other.cols_ || rows_ != other.rows_) {
    throw std::length_error("матрицы разных размеров");
  }
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      matrix_[i][j] -= other.matrix_[i][j];
    }
  }
}

S21Matrix& S21Matrix::operator-=(const S21Matrix& other) {
  SubMatrix(other);
  return *this;
}

S21Matrix S21Matrix::operator-(const S21Matrix& other) const {
  S21Matrix result{*this};
  result.SubMatrix(other);
  return result;
}

void S21Matrix::MulNumber(const double num) noexcept {
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      matrix_[i][j] = matrix_[i][j] * num;
    }
  }
}

void S21Matrix::MulMatrix(const S21Matrix& other) {
  if (cols_ != other.rows_) {
    throw std::length_error(
        "число столбцов первой матрицы не равно числу строк второй матрицы");
  }
  S21Matrix result{rows_, other.cols_};
  for (int i = 0; i < result.rows_; ++i) {
    for (int j = 0; j < result.cols_; ++j) {
      for (int k = 0; k < cols_; ++k) {
        result(i, j) += (*this)(i, k) * other(k, j);
      }
    }
  }
  *this = std::move(result);
}

S21Matrix S21Matrix::operator*(double num) noexcept {
  S21Matrix result{*this};
  result.MulNumber(num);
  return result;
}

S21Matrix operator*(double num, S21Matrix& matrix) noexcept {
  S21Matrix result = matrix * num;
  return result;
}

S21Matrix& S21Matrix::operator*=(double num) {
  MulNumber(num);
  return *this;
}

S21Matrix& S21Matrix::operator*=(const S21Matrix& other) {
  MulMatrix(other);
  return *this;
}

S21Matrix S21Matrix::operator*(const S21Matrix& other) {
  S21Matrix result{*this};
  result.MulMatrix(other);
  return result;
}

double& S21Matrix::operator()(int i, int j) {
  if (i < 0 || i >= rows_ || j < 0 || j >= cols_) {
    throw std::out_of_range("Индекс выходит за пределы матрицы");
  }
  return matrix_[i][j];
}

const double& S21Matrix::operator()(int i, int j) const {
  if (i < 0 || i >= rows_ || j < 0 || j >= cols_) {
    throw std::out_of_range("Индекс выходит за пределы матрицы");
  }
  return matrix_[i][j];
}

S21Matrix S21Matrix::Transpose() {
  S21Matrix result(cols_, rows_);
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      result(i, j) = (*this)(j, i);
    }
  }
  return result;
}

S21Matrix S21Matrix::MakeMinor(int current_i, int current_j, int size) {
  S21Matrix result{rows_ - 1, cols_ - 1};
  for (int i = 0, r = 0; i < size; i++) {
    for (int j = 0, c = 0; j < size; j++) {
      if (i != current_i && j != current_j) {
        result(r, c++) = (*this)(i, j);
        if (c == size - 1) {
          c = 0;
          r++;
        }
      }
    }
  }
  return result;
}

double S21Matrix::Determinant() {
  if (rows_ != cols_) {
    throw std::logic_error("матрица не является квадратной");
  }

  if (rows_ == 1) {
    return matrix_[0][0];
  }

  double result = 0.0;
  int sign = 1;

  S21Matrix minor(rows_ - 1, cols_ - 1);
  for (int i = 0; i < cols_; ++i) {
    minor = MakeMinor(0, i, rows_);
    result += sign * matrix_[0][i] * minor.Determinant();
    sign *= -1;
  }

  return result;
}

S21Matrix S21Matrix::CalcComplements() {
  if (rows_ != cols_) {
    throw std::logic_error("матрица не является квадратной");
  }

  S21Matrix result{rows_, cols_};

  if (rows_ == 1) {
    result(0, 0) = 1.0;
    return result;
  }

  S21Matrix minor{rows_ - 1, cols_ - 1};
  double minorDeterminant;
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      minor = MakeMinor(i, j, rows_);
      int sign = ((i + j) % 2 == 0) ? 1 : -1;
      minorDeterminant = minor.Determinant();
      result(i, j) = sign * minorDeterminant;
    }
  }

  return result;
}

S21Matrix S21Matrix::InverseMatrix() {
  if (rows_ != cols_) {
    throw std::logic_error("матрица не является квадратной");
  }
  double determ = Determinant();
  if (std::abs(determ) < kEpsilon) {
    throw std::logic_error("определитель матрицы равен 0");
  }

  return Transpose().CalcComplements() * (1.0 / determ);
}