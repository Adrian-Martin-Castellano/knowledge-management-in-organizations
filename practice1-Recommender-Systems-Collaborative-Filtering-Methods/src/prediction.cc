#include "prediction.h"

void Prediction::compute(Matrix& a) {
  std::ofstream filePred("predicciones.txt");
  std::ofstream fileSims("similitudes.txt");
  std::ofstream fileDetalle("detalle_predicciones.txt");

  if (!filePred.is_open() || !fileSims.is_open() || !fileDetalle.is_open()) {
    std::cerr << "Error: no se pudieron crear los archivos de salida.\n";
    return;
  }

  filePred << "===========================================\n";
  filePred << " MATRIZ DE UTILIDAD COMPLETADA\n";
  filePred << "===========================================\n";

  fileSims << "===========================================\n";
  fileSims << " SIMILITUDES ENTRE USUARIOS\n";
  fileSims << "===========================================\n";

  fileDetalle << "===========================================\n";
  fileDetalle << " DETALLE DE PREDICCIONES Y RECOMENDACIONES\n";
  fileDetalle << "===========================================\n";
  fileDetalle << "Métrica: " 
              << (metric_ == 1 ? "Pearson" : metric_ == 2 ? "Cosine" : "Euclidean") 
              << " | Vecinos k = " << k_ 
              << " | Tipo = " << (type_ == 1 ? "Simple" : "Media Diferencial") << "\n\n";

  Similarity sim;
  std::vector<std::vector<double>> matriz_pred(matrix_.getRows(), std::vector<double>(matrix_.getCols(), 0.0));

  for (int u = 0; u < matrix_.getRows(); u++) {
    fileDetalle << "\n-------------------------------------------\n";
    fileDetalle << "Usuario " << u + 1 << ":\n";

    for (int i = 0; i < matrix_.getCols(); i++) {
      if (std::isnan(matrix_.get(u, i))) {
        double prediction = 0.0;
        fileDetalle << "\n  Item " << i + 1 << "\n";
        if (type_ == 1)
          prediction = predictionSimple(u, i, fileSims, fileDetalle);
        else
          prediction = predictionDiffMean(u, i, fileSims, fileDetalle);
        matriz_pred[u][i] = prediction;
        matrix_.set(u, i, prediction);
        fileDetalle << "  Predicción final para (U" << u + 1 << ", I" << i + 1 << "): " << prediction ;
        std::string nivel;
        if (prediction < 1.0)
          nivel = "No recomendado";
        else if (prediction < 2.0)
          nivel = "Poco recomendado";
        else if (prediction < 3.5)
          nivel = "Recomendación media";
        else if (prediction < 4.5)
          nivel = "Recomendado";
        else
          nivel = "Muy recomendado";
        fileDetalle << " → " << nivel << "\n";
      }
    }
  }
  filePred << matrix_;
  fileDetalle << "\n===========================================\n";
  fileDetalle << " RECOMENDACIONES BASADAS EN PREDICCIONES\n";
  fileDetalle << "===========================================\n";

  for (int u = 0; u < matrix_.getRows(); u++) {
    double maxPred = -1;
    int bestItem = -1;
    for (int i = 0; i < matrix_.getCols(); i++) {
      if (matriz_pred[u][i] > maxPred) {
        maxPred = matriz_pred[u][i];
        bestItem = i;
      }
    }
    if (bestItem != -1)
      fileDetalle << "Usuario " << u + 1 << " → recomendar Ítem " << bestItem + 1 << " (valor predicho = " << maxPred << ")\n";
  }
  filePred.close();
  fileSims.close();
  fileDetalle.close();

  std::cout << "\n→ Archivos generados:\n" << "   - predicciones.txt\n" << "   - similitudes.txt\n" << "   - detalle_predicciones.txt\n\n";
}


double Prediction::predictionSimple(int u, int i, std::ofstream& fileSims, std::ofstream& fileDetalle) {
  Similarity similarity;
  std::vector<std::pair<int, double>> similitudes;
  double num = 0.0, den = 0.0;

  for (int v = 0; v < matrix_.getRows(); v++) {
    if (u == v) continue;
    double sim_uv = 0.0;
    switch (metric_) {
      case 1: sim_uv = similarity.pearson(matrix_, u, v); break;
      case 2: sim_uv = similarity.cosine(matrix_, u, v); break;
      case 3: sim_uv = similarity.euclidean(matrix_, u, v); break;
    }
    similitudes.push_back({v, sim_uv});
  }

  std::sort(similitudes.begin(), similitudes.end(), [](auto& a, auto& b) {
    return a.second > b.second;
  });

  fileSims << "Usuario " << u + 1 << " - Item " << i + 1 << ":\n";
  for (auto& s : similitudes)
    fileSims << "  Sim(U" << u + 1 << ", U" << s.first + 1 << ") = " << s.second << "\n";

  fileSims << "  Vecinos más cercanos (" << k_ << "): ";
  for (int idx = 0; idx < std::min(k_, (int)similitudes.size()); idx++)
    fileSims << "U" << similitudes[idx].first + 1 << " ";
  fileSims << "\n\n";

  for (int idx = 0; idx < std::min(k_, (int)similitudes.size()); idx++) {
    int v = similitudes[idx].first;
    double sim_uv = similitudes[idx].second;
    double value_v = matrix_.get(v, i);
    if (!std::isnan(value_v)) {
      num += sim_uv * value_v;
      den += std::abs(sim_uv);
      fileDetalle << "    * U" << v + 1 << " vecino: " << sim_uv << " * " << value_v << "\n";
    }
  }

  double result = (den != 0) ? num / den : 0.0;
  fileDetalle << "    → Numerador = " << num << ", Denominador = " << den 
              << " → Predicción = " << result << "\n";
  return result;
}



double Prediction::predictionDiffMean(int u, int i, std::ofstream& fileSims, std::ofstream& fileDetalle) {
  Similarity similarity;
  std::vector<double> averages = similarity.mean(matrix_);
  std::vector<std::pair<int, double>> similitudes;
  double num = 0.0, den = 0.0;

  for (int v = 0; v < matrix_.getRows(); v++) {
    if (u == v) continue;
    double sim_uv = 0.0;
    switch (metric_) {
      case 1: sim_uv = similarity.pearson(matrix_, u, v); break;
      case 2: sim_uv = similarity.cosine(matrix_, u, v); break;
      case 3: sim_uv = similarity.euclidean(matrix_, u, v); break;
    }

    similitudes.push_back({v, sim_uv});
  }

  std::sort(similitudes.begin(), similitudes.end(), [](const auto& a, const auto& b) {
    return a.second > b.second;
  });

  fileSims << "Usuario " << u + 1 << " - Item " << i + 1 << ":\n";
  for (const auto& s : similitudes)
    fileSims << "  Sim(U" << u + 1 << ", U" << s.first + 1 << ") = " << s.second << "\n";
  fileSims << "  Vecinos más cercanos (" << k_ << "): ";
  for (int idx = 0; idx < std::min(k_, static_cast<int>(similitudes.size())); idx++)
    fileSims << "U" << similitudes[idx].first + 1 << " ";
  fileSims << "\n\n";

  for (int idx = 0; idx < std::min(k_, static_cast<int>(similitudes.size())); idx++) {
    int v = similitudes[idx].first;
    double sim_uv = similitudes[idx].second;
    double value_v = matrix_.get(v, i);

    if (!std::isnan(value_v)) {
      num += sim_uv * (value_v - averages[v]);
      den += std::abs(sim_uv);

      fileDetalle << "    * Contribución de U" << v + 1 << ": " << sim_uv << " * (" << value_v << " - " << averages[v] << ")\n";
    }
  }

  double prediction = averages[u];
  if (den != 0)
    prediction += num / den;
  fileDetalle << "    Media del usuario U" << u + 1 << " = " << averages[u] << "\n";
  fileDetalle << "    Numerador = " << num << ", Denominador = " << den << "\n";
  fileDetalle << "    → Predicción final = " << prediction << "\n";

  return prediction;
}