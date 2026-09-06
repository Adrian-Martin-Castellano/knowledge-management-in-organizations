#include "matrix.h"

Matrix::Matrix(int rows, int cols) : rows_(rows), cols_(cols) {
  data_.resize(rows, std::vector<double>(cols, 0.0));
  valor_min_ = 0;
  valor_max_ = 0;
}

double Matrix::get(int row, int col) const {
  if (row < 0 || row >= rows_ || col < 0 || col >= cols_) {
    throw std::out_of_range("Index out of range");
  }
  return data_[row][col];
}

void Matrix::set(int row, int col, double value) {
  if (row < 0 || row >= rows_ || col < 0 || col >= cols_) {
    throw std::out_of_range("Index out of range");
  }
  data_[row][col] = value;
}

int Matrix::getRows() const {
  return rows_;
}

int Matrix::getCols() const {
  return cols_;
}

double Matrix::getValorMin() const {
  return valor_min_;
}

double Matrix::getValorMax() const {
  return valor_max_;
}

void Matrix::setValorMin(double min) {
  valor_min_ = min;
}

void Matrix::setValorMax(double max) {
  valor_max_ = max;
}

std::ostream& operator<<(std::ostream& os, const Matrix& matrix) {
  for (int i = 0; i < matrix.getRows(); ++i) {
    for (int j = 0; j < matrix.getCols(); ++j) {
      double val = matrix.get(i, j);
      if (std::isnan(val)) {
        os << std::setw(7) << "-";
      } else {
        os << std::setw(7) << std::fixed << std::setprecision(3) << val;
      }
    }
    os << "\n";
  }
  return os;
}