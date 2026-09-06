#include "document.h"
#include <sstream>
#include <algorithm>
#include <cctype> 
#include <cmath>  
#include <iostream>
#include <iomanip>
#include <tuple>

using namespace std;

void Document::calculateTF(const set<string>& stopwords, const map<string, string>& lemmas) {
    istringstream iss(content_);
    map<string, int> term_counts; 
    string word;
    auto clean_word = [](string& w) {
        w.erase(remove_if(w.begin(), w.end(), [](char c){ return !isalnum(c); }), w.end());
    };
    while (iss >> word) {
        transform(word.begin(), word.end(), word.begin(), ::tolower); 
        clean_word(word); 
        if (word.empty()) continue;
        if (stopwords.count(word)) continue;
        if (lemmas.count(word)) {
            word = lemmas.at(word);
        }
        term_counts[word]++;
        term_frequency_[word] = 1.0 + log10(term_counts[word]); 
    }
}

void Document::calculateTFIDF(const map<string, double>& idf) {
    vector_length_ = 0.0;
    TFIDF_.clear();
    normalized_vector_.clear();
    for (const auto& pair : term_frequency_) {
        const string& term = pair.first;
        double tf = pair.second;
        if (idf.count(term)) {
            double current_idf = idf.at(term);
            double tfidf_value = tf * current_idf;
            
            TFIDF_[term] = tfidf_value;
            vector_length_ += tfidf_value * tfidf_value;
        }
    }
    
    vector_length_ = sqrt(vector_length_);

    if (vector_length_ > 0.0) {
        for (const auto& pair : TFIDF_) {
            normalized_vector_[pair.first] = pair.second / vector_length_;
        }
    }
}

double Document::cosineSimilarity(const Document& other) const {
    double dot_product = 0.0;
    for (const auto& pair : normalized_vector_) {
        const string& term = pair.first;
        if (other.getNormalizedVector().count(term)) {
            dot_product += pair.second * other.getNormalizedVector().at(term);
        }
    }
    return dot_product;
}

void Document::showTFIDF(const map<string,double>& idf_values) const {
    vector<tuple<string, double, double, double>> terms_data;

    for (const auto& pair : TFIDF_) {
        string term = pair.first;
        double tfidf_value = pair.second;
        double tf = term_frequency_.at(term);
        double idf = idf_values.count(term) ? idf_values.at(term) : 0.0;
        
        terms_data.emplace_back(term, tf, idf, tfidf_value);
    }
    
    sort(terms_data.begin(), terms_data.end());


     cout << "| " << setw(5) << "Índice" << " | " << setw(15) << "Término" << " | " 
         << setw(10) << "TF" << " | " << setw(10) << "IDF" << " | " << setw(10) << "TF-IDF" << " |\n";
    cout << "|--------|-----------------|------------|------------|------------|\n";
    
    int index = 1;
    for (const auto& data : terms_data) {
        cout << "| " << setw(5) << index++ << " | " << setw(15) << get<0>(data) 
             << " | " << setw(10) << fixed << setprecision(3) << get<1>(data) 
             << " | " << setw(10) << fixed << setprecision(3) << get<2>(data) 
             << " | " << setw(10) << fixed << setprecision(3) << get<3>(data) << " |\n";
    }
    cout << "\nLongitud del vector (magnitud): " << fixed << setprecision(4) << vector_length_ << "\n" << endl;
}