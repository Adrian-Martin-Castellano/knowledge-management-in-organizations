# Recommender Systems: Content-Based Models

## Introduction
This project implements a ***content-based recommender system*** written in `C++` that operates as a ***command-line application***.

Given a collection of text documents, the program constructs vector profiles using ***TF-IDF*** weighting and calculates ***cosine similarity*** to identify and recommend similar contents.

The application accepts the following input files:
  - Stopwords file (`.txt`)
  - Lemmatization dictionary (`JSON`)
  - Two or more text documents (`.txt`)

And produces the following outputs:
  - A structured table containing `Index`, `Term`, `TF`, `IDF`, and `TF-IDF` values dumped to an output text file.
  - A `cosine similarity` matrix between the evaluated documents dumped to an output text file.

## Dependency Installation Instructions and Program Execution

To run this `C++` application in a terminal, ensure your environment has the following dependencies installed:

  - **Terminal or Command Interpreter:** Used as the interface to execute the program and display output.

  - **C++ Compiler:** Required to build the source code. On Linux distributions, we recommend using `g++`.
    
  - **Make:** Build automation tool to streamline compilation. Execute `make` to compile the project and `make clean` to remove compiled binaries and object files.

Once all dependencies are installed, navigate to the `src` directory and run `make` in the terminal. After compilation, run the application using the following command structure:

```bash
./sistema_de_recomendacion -s stop_words/fichero_stopwords.txt -l lematización/lemas.json -f document_examples/document-01.txt -f document_examples/document-02.txt
```

## Code Description

The developed codebase is modularized across files with distinct responsibilities:

* **`sistema_recomendacion.cc`**: Contains the main application entry point (`main()`). Handles parsing command-line input flags (data files, stopwords, and lemmatization path) and orchestrates the program pipeline.
* **`document.h` / `document.cc`**: Defines the `class Document`, which computes the TF, TF-IDF, and cosine similarity for a given file:
  * `calculateTF()`: Calculates the weighted term frequency of the document. Tokenizes the text, converts it to lowercase, strips punctuation and whitespaces, filters out stopwords, and applies lemmatization. Maintains term counts and converts them into logarithmic TF using TF(t,d) = 1 + log10(raw_tf(t,d)), storing results in `term_frequency_`.
  * `calculateTFIDF()`: Calculates $\text{TF-IDF} = \text{TF} \times \text{IDF}$ for each term. It then normalizes the vector by dividing all term weights by the vector magnitude, populating `TFIDF_`, `normalized_vector_`, and `vector_length_`.
  * `cosineSimilarity()`: Compares the active document against another and returns a similarity score between `0` and `1` (values closer to `1` indicate higher similarity).
  * `showTFIDF()`: Renders a table for the document containing Index, Term, TF, and IDF, as well as displaying the overall TF-IDF vector magnitude.
* **`corpus.h` / `corpus.cc`**: Defines the `class Corpus`, which holds a collection of `Document` instances and computes corpus-wide IDF and TF-IDF metrics:
  * `addDocument()`: Appends a `Document` instance to the corpus collection.
  * `calculateIDF()`: Calculates global term importance across the corpus. Uses a smoothed IDF formula to prevent division by zero and extreme values in smaller datasets: $\text{IDF} = \log_{10}\left(\frac{N + 1}{df + 1}\right) + 1$, where $N$ is the total document count and $df$ is the document frequency for that term. Stores resulting scores in `idf_values_`.
  * `calculateTFIDFforAllDocuments()`: Iterates over all corpus documents and computes their TF-IDF vectors by invoking `calculateTFIDF()` from `class Document`.
  * `showTFIDFforAllDocuments()`: Iterates through documents and displays the detailed table with added TF-IDF scores.
  * `showCosineSimilarities()`: Calculates and displays the $\text{Doc} \times \text{Doc}$ cosine similarity matrix.
  * `loadDocumentsFromFiles()`: Receives a list of file paths. For each path: opens and reads the raw text, alerts if empty or unreadable, creates a `Document`, computes its TF (incorporating stopwords and lemmas), and appends it to the Corpus.
* **`include.h`**: Global header grouping standard C++ libraries used throughout the project.
* **`menu.cc`**: Contains `print_usage()`, which displays command-line usage instructions and help menus.
* **`read_file.h` / `read_file.cc`**: Handles reading and parsing input files for stopwords and lemmatization dictionaries:
  * `readStopWords()`: Reads the stopwords file line-by-line and populates a `std::set` container.
  * `readLemmas()`: Parses the JSON lemmatization file assuming single-line format: `{"word1":"lemma1", "word2":"lemma2"}`. Stores mapping entries into a `std::map` container.
* **`Makefile`**: Build instructions to automate project compilation. Generate the executable using `make` and clear build output using `make clean`.

---

## Usage Example

The application executes from the terminal using options to specify required input files.

### Flag Configuration Overview:

* **`-s <file>`**: Path to the stopwords file.
* **`-l <file>`**: Path to the JSON lemmatization file.
* **`-f <file>`**: Path to input text documents (requires at least two files).
* **`-h`, `--help`**: Displays help output from the `print_usage()` function.

### Example Execution Command:

```bash
./sistema_de_recomendacion -s stop_words/fichero_stopwords.txt -l lematización/lemas.json -f document_examples/document-01.txt -f document_examples/document-02.txt
```

Executing this command generates the output file containing:

* Table for Document 1 along with its vector length
* Table for Document 2 along with its vector length
* Cosine similarity matrix comparing both documents

### Output Preview

```text
=== Document 1 - TF-IDF ===
| Index |          Term |    TF |   IDF | TF-IDF |
|-------|---------------|-------|-------|--------|
|     1 |             a | 2.362 | 1.000 |  2.362 |
|     2 |    acceptance | 1.000 | 1.000 |  1.000 |
|     3 |      accepted | 1.000 | 1.176 |  1.176 |
|     4 |        afraid | 1.301 | 1.176 |  1.530 |
|     5 |           air | 1.602 | 1.000 |  1.602 |
|     6 |         alive | 1.301 | 1.000 |  1.301 |
|     7 |       allowed | 1.000 | 1.000 |  1.000 |
|     8 |        asleep | 1.000 | 1.000 |  1.000 |
|     9 |     attention | 1.301 | 1.000 |  1.301 |
|    10 |       balance | 1.000 | 1.000 |  1.000 |
|    11 |     beautiful | 1.000 | 1.000 |  1.000 |
|    12 |        beauty | 1.000 | 1.000 |  1.000 |
|    13 |         began | 1.301 | 1.000 |  1.301 |
|    14 |     beginning | 1.000 | 1.176 |  1.176 |
|    15 |          bend | 1.000 | 1.176 |  1.176 |
...

Vector Length (Magnitude): 19.1363

=== Document 2 - TF-IDF ===
| Index |          Term |    TF |   IDF | TF-IDF |
|-------|---------------|-------|-------|--------|
|     1 |             a | 2.301 | 1.000 |  2.301 |
|     2 |    acceptance | 1.000 | 1.000 |  1.000 |
|     3 |       achieve | 1.000 | 1.176 |  1.176 |
|     4 |       admired | 1.000 | 1.176 |  1.176 |
|     5 |           air | 1.699 | 1.000 |  1.699 |
|     6 |         alive | 1.000 | 1.000 |  1.000 |
|     7 |       allowed | 1.301 | 1.000 |  1.301 |
|     8 |     alongjust | 1.000 | 1.176 |  1.176 |
|     9 |    altogether | 1.000 | 1.176 |  1.176 |
|    10 |      anchored | 1.000 | 1.176 |  1.176 |
|    11 |  appointments | 1.000 | 1.176 |  1.176 |
|    12 |       arrived | 1.000 | 1.176 |  1.176 |
|    13 |         asked | 1.000 | 1.176 |  1.176 |
|    14 |        asleep | 1.000 | 1.000 |  1.000 |
|    15 |     attention | 1.301 | 1.000 |  1.301 |
...

Vector Length (Magnitude): 20.6213
```

## Authors

**Adrián Martín Castellano** &rarr; `alu0101547619`