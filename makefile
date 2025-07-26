CXX = g++

SRC_DIR = src
OBJ_DIR = obj
INCLUDE_DIR = include

EXECUTABLE = ChiBebinam

CXXFLAGS = -std=c++17 -Wall -g -I$(INCLUDE_DIR)

SOURCES = $(wildcard $(SRC_DIR)/*.cpp)

OBJECTS = $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SOURCES))

.PHONY: all clean

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	@echo "Linking objects to create executable..."
	$(CXX) $(CXXFLAGS) -o $@ $^

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(OBJ_DIR)
	@echo "Compiling $< -> $@"
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	@echo "Cleaning up the project..."
	rm -rf $(OBJ_DIR) $(EXECUTABLE)