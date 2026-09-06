#include "include.h"
#include "matrix.h"
#include "similarity.h"

#pragma once

struct Prediction {
  Matrix& matrix_;
  int metric_;
  int k_;
  int type_;

  Prediction(Matrix& m, int metric, int k, int type) : matrix_(m), metric_(metric), k_(k), type_(type) {}

  void compute(Matrix& a);
  double predictionSimple(int u, int i, std::ofstream& fileSims, std::ofstream& fileDetalle);
  double predictionDiffMean(int u, int i, std::ofstream& fileSims, std::ofstream& fileDetalle);

};