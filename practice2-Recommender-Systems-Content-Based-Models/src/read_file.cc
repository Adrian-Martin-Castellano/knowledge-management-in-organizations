#include "read_file.h"
#include <fstream>
#include <sstream>
#include <algorithm>
#include <iostream>
#include <cctype>

using namespace std; 

/**
 * Lee palabras de un archivo de texto, una palabra por línea o separadas por espacio.
 */
set<string> readStopWords(const string& filepath) {
    set<string> stopwords;
    ifstream file(filepath);

    if (!file.is_open()) {
        cerr << "Error: No se pudo abrir el archivo de stop words en: " << filepath << endl;
        return stopwords;
    }

    string word;
   while (file >> word) {
        transform(word.begin(), word.end(), word.begin(), ::tolower);
        word.erase(remove_if(word.begin(), word.end(), [](char c){ return !isalnum(c); }), word.end());
        if (!word.empty()) {
            stopwords.insert(word);
        }
    }
    return stopwords;
}

/**
 * Lee lemas asumiendo un formato de línea única como: {"palabra1":"lema1", "palabra2":"lema2"}
 */
map<string, string> readLemmas(const string& filepath) {
    map<string, string> lemmas;
    ifstream file(filepath);

    if (!file.is_open()) {
        cerr << "Error: No se pudo abrir el archivo de lemas en: " << filepath << endl;
        return lemmas;
    }

    string word, lemma;
    while (file >> word >> lemma) {
        lemmas[word] = lemma;
    }
    return lemmas;
}