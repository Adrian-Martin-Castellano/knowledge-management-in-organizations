CXX = g++
CXXFLAGS = -std=c++17

SRC_DIR = src
SOURCES = $(SRC_DIR)/matrix.cc $(SRC_DIR)/read_file.cc $(SRC_DIR)/main_sistema_recomendacion.cc \
          $(SRC_DIR)/menu.cc $(SRC_DIR)/similariry.cc $(SRC_DIR)/prediction.cc
TARGET = sistema_de_recomendacion

all: $(TARGET)

$(TARGET): $(SOURCES)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SOURCES)

clean:
	rm -f $(TARGET)

.PHONY: all clean