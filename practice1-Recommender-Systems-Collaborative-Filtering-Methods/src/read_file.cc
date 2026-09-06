#include "read_file.h"

using namespace std;

void usage(const char* appname) {
  cout << "Uso: " << appname << " [opciones]\n\n"
  << "Opciones disponibles:\n"
  << "  -f <ruta>       Ruta al fichero con la matriz de utilidad\n"
  << "  -m <metrica>    Metrica de similitud (1: Pearson, 2: Cosine, 3: Euclidean)\n"
  << "  -k <num>        Numero de vecinos a considerar\n"
  << "  -p <tipo>       Tipo de prediccion (1: Simple, 2: Mean)\n"
  << "  -h --help              Muestra esta ayuda y termina\n\n"
  << "Ejemplo:\n"
  << "  " << appname << " -f data/matrix.txt -m 1 -k 3 -p 2\n"
  << endl;
}

Matrix readFile(const std::string& filepath) {
  std::ifstream file(filepath);
  if (!file.is_open()) {
      std::cerr << "Error: No se pudo abrir el archivo " << filepath << std::endl;
      exit(EXIT_FAILURE);
  }
  double valor_min, valor_max;
  file >> valor_min >> valor_max;
  file.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
  std::vector<std::vector<double>> data;
  std::string line;
  size_t maxCols = 0;
  while (std::getline(file, line)) {
    std::istringstream iss(line);
    std::vector<double> row;
    std::string token;
    while (iss >> token) {
      if (token == "-") {
        row.push_back(std::numeric_limits<double>::quiet_NaN());
      } else {
        row.push_back(std::stod(token));
      }
    }
    if (!row.empty()) {
      maxCols = std::max(maxCols, row.size());
      data.push_back(row);
    }
  }

  file.close();

  int rows = data.size();
  int cols = static_cast<int>(maxCols);
  Matrix matrix(rows, cols);
  matrix.setValorMin(valor_min);
  matrix.setValorMax(valor_max);

  for (int i = 0; i < rows; ++i) {
    for (int j = 0; j < cols; ++j) {
      double value = (j < data[i].size()) ? data[i][j] : std::numeric_limits<double>::quiet_NaN();
      matrix.set(i, j, value);
    }
  }
  return matrix;
}
