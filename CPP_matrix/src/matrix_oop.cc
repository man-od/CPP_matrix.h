#include "matrix_oop.h"

// Basic constructor
S21Matrix::S21Matrix() : rows_(0), cols_(0) {}

// Parameterized constructor with number of rows and columns
S21Matrix::S21Matrix(int rows, int cols) {
  if (rows < 0 || cols < 0)
    throw std::out_of_range("invalid arguments for create matrix");
  rows_ = rows;
  cols_ = cols;
  CreateMatrix();
}

// Copy constructor
S21Matrix::S21Matrix(const S21Matrix &other)
    : rows_(other.rows_), cols_(other.cols_) {
  CopyMatrix(other);
}

// Move constructor
S21Matrix::S21Matrix(S21Matrix &&other) noexcept
    : rows_(other.rows_), cols_(other.cols_), matrix_(other.matrix_) {
  other.SetNull();
}

// Destructor
S21Matrix::~S21Matrix() { DeleteMatrix(); }

// Сlearing the memory occupied by the matrix
void S21Matrix::DeleteMatrix() {
  if (matrix_ != nullptr) {
    for (int i = 0; i < rows_; i++) {
      delete[] matrix_[i];
    }
  }
  delete[] matrix_;

  rows_ = 0;
  cols_ = 0;
  matrix_ = nullptr;
}

// Move operator
S21Matrix &S21Matrix::operator=(S21Matrix &&other) noexcept {
  if (this != &other) {
    DeleteMatrix();
    rows_ = other.rows_;
    cols_ = other.cols_;
    matrix_ = other.matrix_;
    other.SetNull();
  }
  return *this;
}

// Operator for accessing and changing matrix elements
double &S21Matrix::operator()(int i, int j) {
  if (i < 0 || i >= rows_ || j < 0 || j >= cols_)
    throw std::out_of_range("matrix indices out of bounds");
  return matrix_[i][j];
}

const double &S21Matrix::operator()(int i, int j) const {
  if (i < 0 || i >= rows_ || j < 0 || j >= cols_)
    throw std::out_of_range("matrix indices out of bounds");
  return matrix_[i][j];
}

// Addition operator
S21Matrix S21Matrix::operator+(const S21Matrix &other) const {
  S21Matrix res(*this);
  res.SumMatrix(other);
  return res;
}

// Subtraction operator
S21Matrix S21Matrix::operator-(const S21Matrix &other) const {
  S21Matrix res(*this);
  res.SubMatrix(other);
  return res;
}

// Matrix multiplication operator
S21Matrix S21Matrix::operator*(const S21Matrix &other) const {
  ThrowMatrixRowsCols(other);
  S21Matrix res(*this);
  res.MulMatrix(other);
  return res;
}

// Operator for multiplying a matrix by a number
S21Matrix S21Matrix::operator*(const double num) const {
  S21Matrix res(*this);
  res.MulNumber(num);
  return res;
}

// Matrix equality operator
bool S21Matrix::operator==(const S21Matrix &other) const noexcept {
  return EqMatrix(other);
}

// Matrix assignment operator
S21Matrix &S21Matrix::operator=(const S21Matrix &other) {
  if (this != &other) {
    DeleteMatrix();
    rows_ = other.rows_;
    cols_ = other.cols_;
    CopyMatrix(other);
  }
  return *this;
}

// Addition assignment operator
S21Matrix &S21Matrix::operator+=(const S21Matrix &other) {
  SumMatrix(other);
  return *this;
}

// Subtraction assignment operator
S21Matrix &S21Matrix::operator-=(const S21Matrix &other) {
  SubMatrix(other);
  return *this;
}

// Multiplication assignment operator
S21Matrix &S21Matrix::operator*=(const S21Matrix &other) {
  MulMatrix(other);
  return *this;
}

// Assignment operator for multiplication from num
S21Matrix &S21Matrix::operator*=(const double num) {
  MulNumber(num);
  return *this;
}

// Accessor method on rows
int S21Matrix::GetRows() const noexcept { return rows_; }

// Accessor method on cols
int S21Matrix::GetCols() const noexcept { return cols_; }

// Mtator method on rows
void S21Matrix::SetRows(int new_rows) {
  if (new_rows < 0) throw std::logic_error("Invalid size of matrix");
  S21Matrix result(new_rows, cols_);
  int tmp_rows = rows_ < new_rows ? rows_ : new_rows;
  for (int i = 0; i < tmp_rows; ++i) {
    for (int j = 0; j < cols_; ++j) {
      result.matrix_[i][j] = matrix_[i][j];
    }
  }
  *this = std::move(result);
}

// Mutator method on cols
void S21Matrix::SetCols(int new_cols) {
  if (new_cols < 0) throw std::logic_error("Invalid size of matrix");
  S21Matrix result(rows_, new_cols);
  int tmp_cols = cols_ < new_cols ? cols_ : new_cols;

  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < tmp_cols; ++j) {
      result.matrix_[i][j] = matrix_[i][j];
    }
  }
  *this = std::move(result);
}

// Memory allocation for storing matrix elements
void S21Matrix::CreateMatrix() {
  matrix_ = new double *[rows_]();
  for (int i = 0; i < rows_; i++) {
    matrix_[i] = new double[cols_]();
  }
}

// Function to copy from one matrix to another
void S21Matrix::CopyMatrix(const S21Matrix &other) {
  CreateMatrix();
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] = other.matrix_[i][j];
    }
  }
}

// Checks matrices for equality with each other
int result = 0;
bool S21Matrix::EqMatrix(const S21Matrix &other) const noexcept {
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    return false;
  }
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      if (std::abs(matrix_[i][j] - other.matrix_[i][j]) > kEps) {
        return false;
      }
    }
  }
  return true;
}

// Adds a second matrix to the current one
void S21Matrix::SumMatrix(const S21Matrix &other) {
  if (rows_ != other.rows_ || cols_ != other.cols_)
    throw std::invalid_argument("incorrect_matrix_size");
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] += other.matrix_[i][j];
    }
  }
}

// Subtracts another from the current matrix
void S21Matrix::SubMatrix(const S21Matrix &other) {
  if (rows_ != other.rows_ || cols_ != other.cols_)
    throw std::invalid_argument("incorrect_matrix_size");
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] -= other.matrix_[i][j];
    }
  }
}

// Multiply a matrix by a number
void S21Matrix::MulNumber(const double num) {
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] *= num;
    }
  }
}

// Matrix multiplication by matrix
void S21Matrix::MulMatrix(const S21Matrix &other) {
  ThrowMatrixRowsCols(other);
  S21Matrix result(rows_, other.cols_);
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < other.cols_; j++) {
      for (int k = 0; k < cols_; k++) {
        result.matrix_[i][j] += matrix_[i][k] * other.matrix_[k][j];
      }
    }
  }
  *this = std::move(result);
}

// Matrix Transpose
S21Matrix S21Matrix::Transpose() const {
  S21Matrix transposed(cols_, rows_);
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      transposed.matrix_[j][i] = matrix_[i][j];
    }
  }
  return transposed;
}

// Calculates and returns the determinant of the current matrix
double S21Matrix::Determinant() const {
  ThrowSizeMatrix();
  double det = 0.0;
  if (rows_ == 1) {
    det = matrix_[0][0];
  } else if (rows_ == 2) {
    det = matrix_[0][0] * matrix_[1][1] - matrix_[1][0] * matrix_[0][1];
  } else {
    for (int j = 0; j < cols_; j++) {
      det += pow(-1, j) * GetMinor(0, j).Determinant() * matrix_[0][j];
    }
  }
  return det;
}

// Get Minor Matrix
S21Matrix S21Matrix::GetMinor(int row, int col) const {
  S21Matrix GetMinorMatrix(rows_ - 1, cols_ - 1);
  for (int i = 0, k = 0; i < rows_; i++) {
    if (i == row) continue;
    for (int j = 0, m = 0; j < cols_; j++) {
      if (j == col) continue;
      if (j != cols_ && i != rows_) {
        GetMinorMatrix.matrix_[k][m] = matrix_[i][j];
        m++;
      }
    }
    k++;
  }
  return GetMinorMatrix;
}

// Calculate matrix algebraic complements of current matrix and returns
S21Matrix S21Matrix::CalcComplements() const {
  ThrowSizeMatrix();
  if (rows_ != cols_) throw std::invalid_argument("rows != cols");

  S21Matrix res(cols_, rows_);
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      res.matrix_[i][j] = pow(-1, (j + i)) * GetMinor(i, j).Determinant();
    }
  }
  return res;
}

// Calculates and returns an inverse matrix
S21Matrix S21Matrix::InverseMatrix() const {
  ThrowSizeMatrix();
  double det = Determinant();
  if (fabs(det) < kEps) throw std::length_error("Matrix determinant is 0");
  S21Matrix result(rows_, cols_);
  if (rows_ == 1) {
    result.matrix_[0][0] = 1 / matrix_[0][0];
  } else {
    result = CalcComplements().Transpose();
    result.MulNumber(1 / det);
  }
  return result;
}

// Throw for Determinant, CalcComplements and InverseMatrix
void S21Matrix::ThrowSizeMatrix() const {
  if (cols_ != rows_) throw std::out_of_range("matrix is ​​not square");
  if (!matrix_) throw std::invalid_argument("Matrix is empty!");
}

void S21Matrix::ThrowMatrixRowsCols(const S21Matrix &other) const {
  if (cols_ != other.rows_)
    throw std::out_of_range("Number of columns not equal to rows");
}

void S21Matrix::SetNull() noexcept {
  rows_ = 0;
  cols_ = 0;
  matrix_ = nullptr;
}
