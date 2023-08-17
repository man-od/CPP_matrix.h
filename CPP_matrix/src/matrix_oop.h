#ifndef CPP1_MATRIXPLUS_1_SRC_MATRIX_OOP_H
#define CPP1_MATRIXPLUS_1_SRC_MATRIX_OOP_H

#include <cmath>
#include <iostream>
#include <stdexcept>

class S21Matrix {
 public:
  S21Matrix();  // Базовый конструктор, инициализирующий матрицу
  S21Matrix(int rows, int cols);  // Параметризированный конструктор
  S21Matrix(const S21Matrix &other);  // Констурктор копирования
  S21Matrix(S21Matrix &&other) noexcept;  // Конструктор переноса
  ~S21Matrix();

  S21Matrix operator+(const S21Matrix &other) const;
  S21Matrix operator-(const S21Matrix &other) const;
  S21Matrix operator*(const S21Matrix &other) const;
  S21Matrix operator*(const double num) const;
  bool operator==(const S21Matrix &other) const noexcept;
  S21Matrix &operator=(const S21Matrix &other);  // оператор присвоение
  S21Matrix &operator=(S21Matrix &&other) noexcept;  // оператор переноса
  S21Matrix &operator+=(const S21Matrix &other);
  S21Matrix &operator-=(const S21Matrix &other);
  S21Matrix &operator*=(const S21Matrix &other);
  S21Matrix &operator*=(const double num);
  double &operator()(int i, int j);
  const double &operator()(int i, int j) const;

  int GetRows() const noexcept;
  int GetCols() const noexcept;
  void SetRows(int new_rows);
  void SetCols(int new_cols);

  bool EqMatrix(const S21Matrix &other) const noexcept;
  void SumMatrix(const S21Matrix &other);
  void SubMatrix(const S21Matrix &other);
  void MulNumber(const double num);
  void MulMatrix(const S21Matrix &other);
  S21Matrix Transpose() const;
  S21Matrix CalcComplements() const;
  double Determinant() const;
  S21Matrix InverseMatrix() const;

 private:
  int rows_, cols_;
  double **matrix_{};

  void CreateMatrix();
  void CopyMatrix(const S21Matrix &other);
  void DeleteMatrix();
  S21Matrix GetMinor(int rows, int cols) const;
  void ThrowMatrixRowsCols(const S21Matrix &other) const;
  void ThrowSizeMatrix() const;
  void SetNull() noexcept;
  static constexpr double kEps = 1e-9;
};

#endif  // CPP1_MATRIXPLUS_1_SRC_MATRIX_OOP_H