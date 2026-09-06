#include "corpus.h"
#include <iostream>
#include <stdexcept>
#include <iomanip>
#include <cmath>    
#include <fstream>  
#include <algorithm>

using namespace std;

void Corpus::addDocument(const Document& document) {
    documents_.push_back(document);
    for (const auto& pair : document.getTermFrequency()) {
        document_frequency_counts_[pair.first]++;
    }
}

void Corpus::calculateIDF() {
    int total_documents = documents_.size();
    if (total_documents == 0) return;
    idf_values_.clear();
    
    const double N_plus_1 = static_cast<double>(total_documents) + 1.0;
    
    for (const auto& pair : document_frequency_counts_) {
        const std::string& term = pair.first;
        int df = pair.second;
        
        double df_plus_1 = static_cast<double>(df) + 1.0; 
    
        idf_values_[term] = std::log10(N_plus_1 / df_plus_1) + 1.0; 
    }
}

void Corpus::calculateTFIDFforAllDocuments() {
    for (auto& document : documents_) {
        document.calculateTFIDF(idf_values_);
    }
}

void Corpus::showTFIDFforAllDocuments() const {
    for (size_t i = 0; i < documents_.size(); i++) {
        cout << "\n=== Documento " << i + 1 << " - TF-IDF ===" << endl;
        documents_[i].showTFIDF(idf_values_);
    }
}

void Corpus::showCosineSimilarities() const {
    std::cout << "\n";
    size_t n = documents_.size();
    if (n == 0) return;
    Matrix cosine_matrix(n, vector<double>(n, 0.0));
    for (size_t i = 0; i < n; i++) {
        for (size_t j = i; j < n; j++) {
            double similarity = documents_[i].cosineSimilarity(documents_[j]);
            cosine_matrix[i][j] = similarity;
            cosine_matrix[j][i] = similarity; 
        }
    }
    cout << setw(8) << "Doc \\";
    for (size_t i = 0; i < n; i++) {
        cout << setw(7) << "Doc" << (i + 1);
    }
    cout << endl;

    cout << setw(8) << " ";
    for (size_t i = 0; i < n; i++) {
        cout << "--------";
    }
    cout << endl;

    for (size_t i = 0; i < n; i++) {
        cout << setw(6) << "Doc" << (i + 1) << " |";
        for (size_t j = 0; j < n; j++) {
            cout << setw(8) << fixed << setprecision(3) << cosine_matrix[i][j];
        }
        cout << endl;
    }
}

void Corpus::loadDocumentsFromFiles(const vector<string>& doc_files, 
                                    const set<string>& stopwords, 
                                    const map<string, string>& lemmas) {
    
    for (const string& doc_file : doc_files) {
        ifstream in(doc_file);
        
        if (!in.is_open()) {
            cerr << "Advertencia: No se pudo abrir el archivo de documento: " << doc_file << ". Saltando." << endl;
            continue; 
        }

        stringstream buffer;
        buffer << in.rdbuf(); 
        string document_content = buffer.str();

        if (document_content.empty()) {
            cerr << "Advertencia: El archivo de documento: " << doc_file << " está vacío. Saltando." << endl;
            continue;
        }
        
        Document doc(document_content);
        doc.calculateTF(stopwords, lemmas);
        addDocument(doc);
    }
}