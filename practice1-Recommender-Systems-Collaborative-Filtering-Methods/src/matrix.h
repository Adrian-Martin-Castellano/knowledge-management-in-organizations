#include "include.h"

#pragma once

class Matrix {
 public:
  Matrix(int rows, int cols);
  double get(int row, int col) const;
  void set(int row, int col, double value);
  int getRows() const;
  int getCols() const;
  double getValorMin() const;
  double getValorMax() const;
  void setValorMin(double min);
  void setValorMax(double max); 

 private:
  std::vector<std::vector<double>> data_;
  int rows_;
  int cols_;
  double valor_min_;
  double valor_max_;

};

// sobrecarga del operador de flujo para imprimir la matriz
std::ostream& operator<<(std::ostream& os, const Matrix& matrix);