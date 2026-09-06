#include "include.h"

void print_usage(const char *prog_name) {
    cerr << "Uso: " << prog_name << " -s <archivo_stopwords> -l <archivo_lemas> -f <documento1> [-f <documento2> ...]" << endl;
    cerr << "Opciones:" << endl;
    cerr << "  -s <archivo>  Especifica el archivo de stopwords." << endl;
    cerr << "  -l <archivo>  Especifica el archivo de lematización." << endl;
    cerr << "  -f <archivo>  Especifica un archivo de documento (debe haber al menos dos)." << endl;
}