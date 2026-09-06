#include "include.h"
#include "matrix.h"

class Similarity {
 public:
  double pearson(const Matrix& a, int u, int v);
  double cosine(const Matrix& a, int u, int v);
  double euclidean(const Matrix& a, int u, int v);
  std::vector<double> mean(const Matrix& a);
};