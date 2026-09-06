#pragma once

#include <string>
#include <map>
#include <set>
#include <vector>

class Document {
public:
    explicit Document(const std::string& content) : content_(content) {}

    const std::map<std::string, double>& getTermFrequency() const { return term_frequency_; }
    const std::map<std::string, double>& getTFIDF() const { return TFIDF_; }
    const std::map<std::string, double>& getNormalizedVector() const { return normalized_vector_; }


    void calculateTF(const std::set<std::string>& stopwords, const std::map<std::string, std::string>& lemmas);
    void calculateTFIDF(const std::map<std::string, double>& idf);
    double cosineSimilarity(const Document& other) const;
    void showTFIDF(const std::map<std::string, double>& idf_values) const;

private:
    std::string content_;
    std::map<std::string, double> term_frequency_; 
    std::map<std::string, double> TFIDF_;          
    std::map<std::string, double> normalized_vector_; 
    double vector_length_ = 0.0;
};