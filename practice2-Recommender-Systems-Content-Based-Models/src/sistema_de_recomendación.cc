#include "read_file.h"
#include "corpus.h"
#include "menu.cc"
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>
#include <unistd.h> 

using namespace std;

int main(int argc, char *argv[]) {
    if (argv[1] == string("-h") || argv[1] == string("--help") || argc == 1) {
        print_usage(argv[0]);
        return 1;
    }

    const string output_path = "output_files/results.txt";
    ofstream out_file(output_path); 

    if (!out_file.is_open()) {
        cerr << "Error: No se pudo abrir el archivo de salida: " << output_path << ". Asegúrate de que el directorio 'output_files' exista." << endl;
        return 1; 
    }
    streambuf* cout_buffer = cout.rdbuf();
    cout.rdbuf(out_file.rdbuf());
    string stop_file;
    string lemma_file;
    vector<string> document_files;
    int opt;
    opterr = 0; 
    while ((opt = getopt(argc, argv, "s:l:f:")) != -1) {
         switch (opt) {
            case 's':
                stop_file = optarg;
                break;
            case 'l':
                lemma_file = optarg;
                break;
            case 'f':
                document_files.push_back(optarg);
                break;
            case ':':
                cerr << "Error: La opción -" << (char)optopt << " requiere un argumento." << endl;
                cout.rdbuf(cout_buffer);
                return 1;
            case '?':
                cerr << "Error: Opción desconocida -" << (char)optopt << "." << endl;
                cout.rdbuf(cout_buffer);
                return 1;
            default:
                cout.rdbuf(cout_buffer);
                return 1;
        }
    }
    
    if (stop_file.empty() || lemma_file.empty() || document_files.size() < 2) {
        cerr << "Error: Debes proporcionar el archivo de stopwords (-s), el archivo de lemas (-l) y al menos dos documentos (-f)." << endl;
        cout.rdbuf(cout_buffer);
        return 1;
    }
    try {
        cout << "Archivo de Stopwords: " << stop_file << endl;
        cout << "Archivo de Lemas: " << lemma_file << endl;

        set<string> stopwords = readStopWords(stop_file);
        map<string, string> lemmas = readLemmas(lemma_file);
        Corpus corpus;
        
        corpus.loadDocumentsFromFiles(document_files, stopwords, lemmas);

        if (corpus.getDocumentCount() == 0) {
            cout << "No se cargó ningún documento válido." << endl;
        } else {
            corpus.calculateIDF();
            corpus.calculateTFIDFforAllDocuments();

            cout << "\n========================================";
            cout << "\n TF-IDF de todos los documentos:";
            cout << "\n========================================";
            corpus.showTFIDFforAllDocuments();

            cout << "\n========================================";
            cout << "\n Similitudes coseno entre documentos:";
            cout << "\n========================================\n";
            corpus.showCosineSimilarities();
        }

    } catch (const runtime_error& e) {
        cerr << "Error de tiempo de ejecución: " << e.what() << endl;
        cout.rdbuf(cout_buffer);
        return 1;
    } catch (const exception& e) {
        cerr << "Se produjo un error inesperado: " << e.what() << endl;
        cout.rdbuf(cout_buffer);
        return 1;
    }
    cout.rdbuf(cout_buffer); 
    out_file.close(); 

    return 0;
}