# Recommender Systems: Collaborative Filtering Methods

## Introduction

This project implements a ***recommender system based on collaborative filtering*** written in ***C++*** that operates as a ***command-line application***.

The program calculates predictions for unrated items by users based on the ratings of similar users, using three types of ***similarity metrics***:

  - Pearson Correlation
  - Cosine Distance
  - Euclidean Distance

And two types of ***prediction*** methods:

  - Simple Prediction
  - Difference from Mean

The application can be executed from the command line and allows visualizing, calculating, and tweaking recommendation parameters via an interactive menu.

## Dependency Installation Instructions and Program Execution

To run this C++ program in a terminal or command line, your system requires the following dependencies:

  - **Terminal or Command Interpreter:** Serves as the user interface to display output.

  - **C++ Compiler:** Required to compile and build the executable code. On Linux distributions, we recommend using the ```g++``` compiler.
    
  - **Make:** A build automation tool to simplify compilation. Simply enter ```make``` in the terminal to build the project, and ```make clean``` to remove executables and object files.

After installing all dependencies, navigate to the ```src``` directory and run ```make``` in the terminal to compile the program. Once compiled, execute the application by running:

```bash
./sistema_de_recomendacion -f data/fichero_con_matriz_de_utilidad.txt -m 1 -k 3 -p 2
```

## Code Description

The developed codebase is modularized across files with distinct responsibilities:

* **`main_sistema_recomendacion.cc`**: Contains the main entry point (`main()`). Handles parsing command-line input arguments (data file path, metric, number of neighbors, and prediction type), loads the utility matrix, and drives interactive menu navigation.
* **`matrix.h` / `matrix.cc`**: Defines the `class Matrix`, which manages user data and item ratings.
* **`menu.h` / `menu.cc`**: Defines the `showMenu()` function, which renders an interactive console menu with available options:
  * Display the utility matrix
  * Change configuration parameters
  * Run predictions
* **`include.h`**: Header file grouping standard library includes used throughout the project.
* **`prediction.h` / `prediction.cc`**: Contains a `struct Prediction` and functions to calculate missing ratings. Two types are implemented:
  * `predictionSimple()`: Computes predictions for unrated items using a weighted average of the most similar users' ratings. It considers the top `k` nearest neighbors and weights their ratings according to their similarity score with the active user.
  * `predictionDiffMean()`: Implements prediction based on difference from the mean. Adjusts neighbor ratings by subtracting their personal average rating, then compensates by adding the active user's mean rating.
  * `compute()`: Runs the full prediction process across all unrated items for every user, applying the selected prediction strategy.
* **`read_file.h` / `read_file.cc`**: Handles utility matrix file parsing and program usage help:
  * `readFile()`: Parses the input file, interprets numeric ratings, handles empty values (represented by `-`), and builds a `Matrix` object used for similarity and prediction calculations.
  * `usage()`: Displays command-line usage instructions and available parameter options in the terminal.
* **`similarity.h` / `similarity.cc`**: Implements the `class Similarity` featuring the three similarity metrics and a utility function to compute user means:
  * `pearson()`: Calculates the Pearson correlation coefficient between users `u` and `v`. Evaluates the linear relationship between ratings of both users, considering deviations from their respective means.
  * `cosine()`: Calculates Cosine similarity between users `u` and `v`. Measures the angle between user rating vectors to determine their degree of alignment. Returns a value between `0` and `1`, where `1` indicates maximum similarity.
  * `euclidean()`: Calculates the normalized Euclidean distance between user ratings for `u` and `v`. Smaller distances indicate higher similarity. Normalized using `1 / (1 + sqrt(distance))` to map values between `0` and `1`.
  * `mean()`: Computes the average rating for each user in the utility matrix.
* **`Makefile`**: Contains build rules to compile the project automatically. Supports building the executable with `make` and cleaning compiled build artifacts with `make clean`.

---

## Usage Example

The program runs from the terminal using configurable options to select the input data file, similarity metric, neighbor count, and prediction method.

### Option flags available for program execution:

* **`-f <path>`**: Path to the utility matrix input file.
* **`-m <metric>`**: Similarity metric selection:
  * `1` &rarr; Pearson
  * `2` &rarr; Cosine
  * `3` &rarr; Euclidean
* **`-k <num>`**: Number of nearest neighbors to consider.
* **`-p <type>`**: Prediction method selection:
  * `1` &rarr; Simple Prediction
  * `2` &rarr; Difference from Mean
* **`-h`, `--help`**: Displays help output from the `usage()` function.

### Example execution command:

```bash
./sistema_de_recomendacion -f data/fichero_con_matriz_de_utilidad.txt -m 1 -k 3 -p 2
```

Upon launching, an interactive menu with **8 options** appears:

* Selecting **option 1** displays the loaded utility matrix.
* Selecting **options 2 or 3** displays the minimum and maximum calculated rating values, respectively.
* **Options 4, 5, and 6** allow users to dynamically change the active metric, number of neighbors, and prediction type.
* Selecting **option 7** computes similarities and predictions using the parameters specified either via command line or modified dynamically through the menu options.

The calculated predictions and similarities are written to three output files:

* `predicciones.txt` &rarr; Displays the completed utility matrix with filled predictions.
* `similitudes.txt` &rarr; Displays pairwise user similarities and the nearest neighbors for each user.
* `detalle_predicciones.txt` &rarr; Contains a detailed report of the prediction calculation steps and final item recommendations for each user.

Finally, **option 8** terminates program execution and outputs an exit message.

---

## Authors

**Adrián Martín Castellano** &rarr; `alu0101547619`