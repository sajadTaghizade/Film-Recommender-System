
CXX = g++
SRC_DIR = src
OBJ_DIR = obj
INCLUDE_DIR = include

EXEC_CLI = ChiBebinam
EXEC_SFML = ChiBebinam_sfml

CXXFLAGS = -std=c++17 -Wall -g -I$(INCLUDE_DIR)

SFML_LIBS = -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

COMMON_SRCS = $(filter-out $(SRC_DIR)/main_cli.cpp $(SRC_DIR)/main_sfml.cpp, $(wildcard $(SRC_DIR)/*.cpp))
COMMON_OBJS = $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(COMMON_SRCS))

CLI_OBJS = $(COMMON_OBJS) $(OBJ_DIR)/main_cli.o
SFML_OBJS = $(COMMON_OBJS) $(OBJ_DIR)/main_sfml.o


.PHONY: all clean

all: $(EXEC_CLI) $(EXEC_SFML)

$(EXEC_CLI): $(CLI_OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

$(EXEC_SFML): $(SFML_OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(SFML_LIBS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR) $(EXEC_CLI) $(EXEC_SFML)