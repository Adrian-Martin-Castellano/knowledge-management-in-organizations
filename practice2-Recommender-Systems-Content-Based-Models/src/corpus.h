#pragma once

#include "document.h"
#include <vector>
#include <map>
#include <string>
#include <set>

typedef std::vector<std::vector<double>> Matrix;

class Corpus {
public:
    void addDocument(const Document& document);
    void calculateIDF();
    void calculateTFIDFforAllDocuments();

    void showTFIDFforAllDocuments() const;
    void showCosineSimilarities() const;
    void loadDocumentsFromFiles(const std::vector<std::string>& doc_files, 
                                const std::set<std::string>& stopwords, 
                                const std::map<std::string, std::string>& lemmas);
    size_t getDocumentCount() const { return documents_.size(); }

private:
    std::vector<Document> documents_;
    std::map<std::string, int> document_frequency_counts_; 
    std::map<std::string, double> idf_values_;
};