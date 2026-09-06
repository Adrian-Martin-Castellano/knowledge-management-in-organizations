# Recommender Systems

Repository containing practical assignments for the **Recommender Systems** module (*Sistemas de Recomendación*), completed as part of the Computer Engineering degree at **Universidad de La Laguna (ULL)**.

This repository implements two foundational paradigms in recommendation technology: **Collaborative Filtering** and **Content-Based Filtering**. Both projects are developed in **C++** as high-performance command-line interface (CLI) applications.

---

## Repository Architecture

```text
.
├── practice-1-collaborative-filtering/
│   ├── src/                  # C++ source code & Makefile
│   ├── data/                 # Utility matrix inputs (.txt)
│   ├── images/               # Screenshots and execution outputs
│   └── README.md             # Detailed documentation for Practice 1
└── practice-2-content-based/
    ├── src/                  # C++ source code & Makefile
    ├── stop_words/           # Stopwords list (.txt)
    ├── lematización/         # Lemmatization dictionary (.json)
    ├── document_examples/    # Input text documents (.txt)
    └── README.md             # Detailed documentation for Practice 2
  ```

  ## Included Projects

### Practice 1: Collaborative Filtering
Implements a user-user collaborative filtering recommender system that predicts unrated items based on the preferences of similar users.

* **Core Features:**
  * **Similarity Metrics:** Pearson Correlation, Cosine Distance, and Normalized Euclidean Distance.
  * **Prediction Methods:** Simple Weighted Average and Difference-from-Mean.
  * **Interactive Console Interface:** Multi-option interactive menu allowing real-time parameter tweaking ($k$-neighbors, active metric, prediction type) and inspection of utility matrices.
  * **Detailed Logging:** Generates output files detailing pairwise user similarities, completed matrices, and step-by-step recommendation logs.

---

### Practice 2: Content-Based Filtering
Implements a content-based recommender system using Natural Language Processing (NLP) techniques to profile text documents and compute document-to-document similarity.

* **Core Features:**
  * **Text Preprocessing:** Tokenization, lowercase normalization, punctuation stripping, stopword filtering, and dictionary-based lemmatization via JSON mappings.
  * **Vector Space Modeling:** Logarithmic Term Frequency ($\text{TF}$) and Smoothed Inverse Document Frequency ($\text{IDF}$) computation to generate normalized $\text{TF-IDF}$ document vectors.
  * **Content Matching:** Cosine similarity calculation across document profiles to construct document recommendation matrices.
  * **Automated Reports:** Generates full vector tables (Index, Term, $\text{TF}$, $\text{IDF}$, $\text{TF-IDF}$) and pairwise similarity matrices.

---

## Technical Summary & Methods

| Feature / Metric | Practice 1: Collaborative Filtering | Practice 2: Content-Based Filtering |
|---|---|---|
| **Domain** | User rating utility matrices | Unstructured text documents |
| **Core Method** | User-user neighborhood aggregation ($k$-NN) | $\text{TF-IDF}$ vector space modeling |
| **Similarity Metrics** | Pearson, Cosine, Euclidean | Cosine Similarity |
| **Preprocessing** | Missing value (`-`) handling | Stopwords removal & JSON lemmatization |
| **Implementation Language** | C++ | C++ |
| **Output** | Predicted ratings & user similarities | Vector magnitudes & document similarity matrix |

---

## Getting Started

### Prerequisites

* **C++ Compiler:** `g++` with C++11 standard support or higher.
* **Build Tool:** `make`.

### Quick Execution

#### Practice 1: Collaborative Filtering

```bash
cd practice-1-collaborative-filtering/src
make
./sistema_de_recomendacion -f data/fichero_con_matriz_de_utilidad.txt -m 1 -k 3 -p 2
```

#### Practice 2: Content-Based Filtering

```bash
cd practice-2-content-based/src
make
./sistema_de_recomendacion -s stop_words/fichero_stopwords.txt -l lematización/lemas.json -f document_examples/document-01.txt -f document_examples/document-02.txt
```

## Course Information

* **Course:** Sistemas de Recomendación (*Recommender Systems*)
* **Degree:** Computer Engineering (*Grado en Ingeniería Informática*)
* **University:** Universidad de La Laguna (ULL)
* **Language:** C++

---

## Authors

**Adrián Martín Castellano** &rarr; `alu0101547619`