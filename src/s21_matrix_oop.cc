#include "s21_matrix_oop.h"

S21Matrix::S21Matrix() : rows_(0), cols_(0), matrix_(nullptr) {}

S21Matrix::~S21Matrix() {
  RemoveMatrix();
  rows_ = 0;
  cols_ = 0;
}

S21Matrix::S21Matrix(int rows, int cols) : rows_(rows), cols_(cols) {
  if (rows <= 0 || cols <= 0)
    throw std::invalid_argument("Invalid parameter for rows or cols.");
  CreateMatrix();
}

S21Matrix::S21Matrix(const S21Matrix &other)
    : rows_(other.rows_), cols_(other.cols_) {
  CreateMatrix();
  CopyMatrix(other);
}

S21Matrix::S21Matrix(S21Matrix &&other)
    : rows_(other.rows_), cols_(other.cols_), matrix_(other.matrix_) {
  other.MoveMatrix();
}

S21Matrix S21Matrix::operator+(const S21Matrix &other) {
  if (!SameMatrixSize(other))
    throw std::logic_error(
        "Error: Matrices should be the same size of rows and columns.");
  S21Matrix result = *this;
  result.SumMatrix(other);
  return result;
}

S21Matrix S21Matrix::operator-(const S21Matrix &other) {
  if (!SameMatrixSize(other))
    throw std::logic_error(
        "Error: Matrices should be the same size of rows and columns.");
  S21Matrix result = *this;
  result.SubMatrix(other);
  return result;
}

S21Matrix &S21Matrix::operator=(S21Matrix &&other) {
  if (this != &other) {
    RemoveMatrix();
    std::swap(rows_, other.rows_);
    std::swap(cols_, other.cols_);
    std::swap(matrix_, other.matrix_);
    other.MoveMatrix();
  }
  return *this;
}

S21Matrix &S21Matrix::operator=(S21Matrix &other) {
  if (this != &other) {
    RemoveMatrix();
    rows_ = other.rows_;
    cols_ = other.cols_;
    CreateMatrix();
    CopyMatrix(other);
  }
  return *this;
}

S21Matrix S21Matrix::operator*(const double num) noexcept {
  S21Matrix result(rows_, cols_);
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      result.matrix_[i][j] = matrix_[i][j] * num;
    }
  }
  return result;
}

S21Matrix S21Matrix::operator*(const S21Matrix &other) {
  MulMatrix(other);
  return *this;
}

S21Matrix S21Matrix::operator+=(const S21Matrix &other) {
  if (!SameMatrixSize(other))
    throw std::logic_error("Error: You can't sum matrices of different size");
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] += other.matrix_[i][j];
    }
  }
  return *this;
}

S21Matrix S21Matrix::operator-=(const S21Matrix &other) {
  if (!SameMatrixSize(other))
    throw std::logic_error("Error: You can't sub matrices of different size");
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] -= other.matrix_[i][j];
    }
  }
  return *this;
}

S21Matrix S21Matrix::operator*=(const double num) noexcept {
  *this = *this * num;
  return *this;
}

S21Matrix S21Matrix::operator*=(const S21Matrix &other) {
  *this = *this * other;
  return *this;
}

double &S21Matrix::operator()(int rows, int cols) {
  if (rows < 0 || cols < 0 || rows >= rows_ || cols >= cols_)
    throw std::range_error("Error: You try to put value out of matrix.");
  return matrix_[rows][cols];
}

double &S21Matrix::operator()(int rows, int cols) const {
  if (rows < 0 || cols < 0 || rows >= rows_ || cols >= cols_)
    throw std::range_error("Error: You try to put value out of matrix.");
  return matrix_[rows][cols];
}

bool S21Matrix::operator==(const S21Matrix &other) const noexcept {
  if (!SameMatrixSize(other)) return false;
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      if (std::abs(matrix_[i][j] - other.matrix_[i][j]) > pow(10, -7))
        return false;
    }
  }
  return true;
}

int S21Matrix::GetRows() const noexcept { return rows_; }

int S21Matrix::GetCols() const noexcept { return cols_; }

void S21Matrix::SetRows(int rows) {
  if (rows <= 0)
    throw std::logic_error("Error: Rows can't be less or equal 0.");
  if (matrix_) {
    S21Matrix tmp(rows, cols_);
    int limit_row = rows > rows_ ? rows_ : rows;
    for (int i = 0; i < limit_row; i++) {
      for (int j = 0; j < cols_; j++) {
        tmp.matrix_[i][j] = matrix_[i][j];
      }
    }
    *this = std::move(tmp);
  }
  rows_ = rows;
  if (!matrix_ && cols_ > 0) {
    CreateMatrix();
  }
}

void S21Matrix::SetCols(int cols) {
  if (cols <= 0)
    throw std::logic_error("Error: Cols can't be less or equal 0.");
  if (matrix_) {
    S21Matrix tmp(rows_, cols);
    int limit_col = cols > cols_ ? cols_ : cols;
    for (int i = 0; i < rows_; i++) {
      for (int j = 0; j < limit_col; j++) {
        tmp.matrix_[i][j] = matrix_[i][j];
      }
    }
    *this = std::move(tmp);
  }
  cols_ = cols;
  if (!matrix_ && rows_ > 0) {
    CreateMatrix();
  }
}

bool S21Matrix::EqMatrix(const S21Matrix &other) const noexcept {
  return *this == other;
}

void S21Matrix::SumMatrix(const S21Matrix &other) { *this += other; }

void S21Matrix::SubMatrix(const S21Matrix &other) { *this -= other; }

void S21Matrix::MulNumber(const double num) noexcept { *this *= num; }

void S21Matrix::MulMatrix(const S21Matrix &other) {
  if (cols_ != other.rows_)
    throw std::logic_error(
        "Error: Rows of first matrix should be equal with columns of second "
        "matrix.");
  S21Matrix tmp(rows_, other.cols_);
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < other.cols_; j++) {
      for (int k = 0; k < cols_; k++) {
        tmp.matrix_[i][j] += matrix_[i][k] * other.matrix_[k][j];
      }
    }
  }
  *this = std::move(tmp);
}

S21Matrix S21Matrix::Transpose() const noexcept {
  S21Matrix res(cols_, rows_);
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      res.matrix_[j][i] = matrix_[i][j];
    }
  }
  return res;
}

double S21Matrix::Determinant() const {
  if (!SquareMatrix())
    throw std::length_error("Error: Matrix should be square.");
  double determinant = 0.0;
  if (rows_ == 1) {
    determinant = matrix_[0][0];
  } else if (rows_ == 2) {
    determinant =
        (matrix_[0][0] * matrix_[1][1] - matrix_[1][0] * matrix_[0][1]);
  } else {
    int index = 1;
    for (int i = 0; i < rows_; i++) {
      S21Matrix Minor = MinorMatrix(i, 0);
      determinant += index * matrix_[i][0] * Minor.Determinant();
      index = -index;
    }
  }
  return determinant;
}

S21Matrix S21Matrix::CalcComplements() const {
  if (!SquareMatrix() && rows_ > 1 && cols_ > 1)
    throw std::logic_error("Error: Matrix should be square.");
  S21Matrix result(rows_, cols_);
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      S21Matrix Minor = MinorMatrix(i, j);
      result.matrix_[i][j] = ((i + j) % 2 ? -1 : 1) * Minor.Determinant();
    }
  }
  return result;
}

S21Matrix S21Matrix::InverseMatrix() const {
  double determinant = Determinant();
  if (!determinant)
    throw std::logic_error("Error: Matrix is not square or determinant is 0.");
  S21Matrix result(rows_, cols_);
  if (rows_ == 1 && cols_ == 1) {
    result.matrix_[0][0] = 1 / determinant;
  } else {
    S21Matrix transpose = CalcComplements().Transpose();
    for (int i = 0; i < rows_; i++) {
      for (int j = 0; j < cols_; j++) {
        result.matrix_[i][j] = transpose.matrix_[i][j] / determinant;
      }
    }
  }
  return result;
}

S21Matrix S21Matrix::MinorMatrix(int rows, int cols) const {
  S21Matrix minor(rows_ - 1, cols_ - 1);
  int minor_row = 0, minor_col = 0;
  for (int i = 0; i < rows_; i++) {
    if (i != rows) {
      for (int j = 0; j < cols_; j++) {
        if (j != cols) {
          minor.matrix_[minor_row][minor_col] = matrix_[i][j];
          minor_col++;
        }
      }
      if (minor_col > cols_ - 2) {
        minor_row++;
        minor_col = 0;
      }
    }
  }
  return minor;
}

bool S21Matrix::SameMatrixSize(const S21Matrix &other) const noexcept {
  return (rows_ == other.rows_ && cols_ == other.cols_);
}

bool S21Matrix::SquareMatrix() const { return rows_ == cols_; }

void S21Matrix::FillMatrix(double num) noexcept {
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] += num;
    }
  }
}

bool S21Matrix::CheckNullptr() { return matrix_ == nullptr; }

void S21Matrix::CopyMatrix(const S21Matrix &other) {
  for (int i = 0; i < rows_; i++)
    std::copy(other.matrix_[i], other.matrix_[i] + other.cols_, matrix_[i]);
}

void S21Matrix::MoveMatrix() {
  rows_ = 0;
  cols_ = 0;
  matrix_ = nullptr;
}

void S21Matrix::CreateMatrix() {
  matrix_ = new double *[rows_]();
  for (int i = 0; i < rows_; i++) matrix_[i] = new double[cols_]();
}

void S21Matrix::RemoveMatrix() {
  if (matrix_) {
    for (int i = 0; i < rows_; i++) delete[] matrix_[i];
    delete[] matrix_;
    matrix_ = nullptr;
  }
}