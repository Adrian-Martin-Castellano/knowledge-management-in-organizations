#include "similarity.h"

double Similarity::pearson(const Matrix& a, int u, int v) {
  double resultado = 0.0, numerador = 0.0, denominador_A = 0.0, denominador_B = 0.0;
  std::vector<double> medias = mean(a);
  for (int i = 0; i < a.getCols(); ++i) {
    double val_u = a.get(u, i);
    double val_v = a.get(v, i);
    if (!std::isnan(val_u) && !std::isnan(val_v)) {
      numerador += (val_u - medias[u]) * (val_v - medias[v]);
      denominador_A += (val_u - medias[u]) * (val_u - medias[u]);
      denominador_B += (val_v - medias[v]) * (val_v - medias[v]);
    }
  }
  if (denominador_A == 0.0 || denominador_B == 0.0) return 0.0;
  resultado = numerador / (sqrt(denominador_A) * sqrt(denominador_B));
  return resultado; 
}

double Similarity::cosine(const Matrix& a, int u, int v) {
  double num = 0.0, den = 0.0, sum_u = 0.0, sum_v = 0.0;
  std::vector<double> medias = mean(a); 
  for (int i = 0; i < a.getRows(); i++) {
    double r_ui =  a.get(u, i);
    double r_vi = a.get(v, i);
    if (!std::isnan(r_ui) && !std::isnan(r_vi)) {
      num += r_ui * r_vi;
      sum_u += r_ui * r_ui;
      sum_v += r_vi * r_vi;
    }
  }
  if (sum_u == 0.0 || sum_v == 0.0) return 0.0;
  return num / (sqrt(sum_u) * sqrt(sum_v)); 
}

double Similarity::euclidean(const Matrix& a, int u, int v) {
  double resultado = 0.0;
  int cols = a.getCols();
  for (int i = 0; i < cols; i++) {
    double rating_u = a.get(u, i);
    double rating_v = a.get(v, i);
    if (!std::isnan(rating_u) && !std::isnan(rating_v)) {
      resultado += pow(rating_u - rating_v, 2);
    }
  }
  resultado = 1 / (1 + sqrt(resultado));
  return resultado; 
}

std::vector<double> Similarity::mean(const Matrix& a) {
  std::vector<double> medias(a.getRows(), 0.0);
  for (int i = 0; i < a.getRows(); ++i) {
    double suma = 0.0;
    int cuenta = 0;
    for (int j = 0; j < a.getCols(); ++j) {
      double val = a.get(i, j);
      if (!std::isnan(val)) { 
        suma += val;
        ++cuenta;
      }
    }
    medias[i] = (cuenta > 0) ? (suma / cuenta) : 0.0;
  }
  return medias;
}