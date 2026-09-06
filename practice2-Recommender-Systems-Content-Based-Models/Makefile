CXX = g++
CXXFLAGS = -std=c++17

SRC_DIR = src
SOURCES = $(SRC_DIR)/document.cc $(SRC_DIR)/corpus.cc $(SRC_DIR)/read_file.cc $(SRC_DIR)/sistema_de_recomendación.cc \

TARGET = sistema_de_recomendacion

all: $(TARGET)

$(TARGET): $(SOURCES)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SOURCES)

clean:
	rm -f $(TARGET)

.PHONY: all clean