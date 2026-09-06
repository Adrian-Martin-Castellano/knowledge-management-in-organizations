#include "read_file.h"
#include "menu.h"
#include "prediction.h"

using namespace std;

int main(int argc, char *argv[]) {
  if (argc == 2 && std::string(argv[1]) == "--help") {
    usage(argv[0]);
    return 0;
  }
  if (argc < 9) {
    std::cerr << "Error: Numero incorrecto de argumentos." << std::endl;
    std::cerr << "Uso: " << argv[0] << " <ruta_al_archivo_de_datos>" << std::endl;
    return EXIT_FAILURE;
  }

  string ficheros;
  int metrica = 0;
  int vecinos = 0;
  int prediccion = 0;

  int opt;
  while ((opt = getopt(argc, argv, "f:m:k:p:")) != -1) {
    switch (opt) {
      case 'f':
        ficheros = optarg;
        break;
      case 'm':
        metrica = stoi(optarg);
        break;
      case 'k':
        vecinos = stoi(optarg);
        break;
      case 'p':
        prediccion = stoi(optarg);
        break;
      default:
        std::cerr << "Error: Opcion invalida." << std::endl;
        return 1;
    }
  }

  if (ficheros.empty() || (metrica < 1 || metrica > 3) || (vecinos < 0) || (prediccion < 1 || prediccion > 2)) {
    std::cerr << "Error: Argumentos invalidos." << std::endl;
    return 1;
  }

  Matrix matriz = readFile(ficheros);

  int opcion;
  do {
    showMenu();
    std::cout << "Seleccione una opcion: ";
    std::cin >> opcion;
    switch (opcion) {
      case 1:
        std::cout << "Matriz de utilidad:\n" << matriz;
        break;
      case 2:
        std::cout << "Valor minimo: " << matriz.getValorMin() << std::endl;
        break;
      case 3:
        std::cout << "Valor maximo: " << matriz.getValorMax() << std::endl;
        break;
      case 4:
        std::cout << "Cambiar metrica (1: Pearson, 2: Cosine, 3: Euclidean): ";
        std::cin >> metrica;
        if (metrica < 1 || metrica > 3) {
          std::cerr << "Metrica invalida." << std::endl;
          metrica = 1; 
        }
        break;
      case 5:
        std::cout << "Cambiar numero de vecinos: ";
        std::cin >> vecinos;
        if (vecinos < 0) {
          std::cerr << "Numero de vecinos invalido." << std::endl;
          vecinos = 0;
        }
        break;
      case 6:
        std::cout << "Cambiar tipo de prediccion (1: Simple, 2: Mean): ";
        std::cin >> prediccion;
        if (prediccion < 1 || prediccion > 2) {
          std::cerr << "Tipo de prediccion invalido." << std::endl;
          prediccion = 1;
        }
        break;
      case 7: {
        std::cout << "Calcular similitud" << std::endl;
        Prediction pred(matriz, metrica, vecinos, prediccion);
        pred.compute(matriz);
        break;
      }
      case 8:
        std::cout << "Saliendo..." << std::endl;
        break;
      default:
        std::cerr << "Opcion invalida." << std::endl;
    }
  } while (opcion != 8);
  return 0;
}