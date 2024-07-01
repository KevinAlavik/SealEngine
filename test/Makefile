# Variables
GAME_NAME = TestGame

BUILD_MODE := dev
BIN_DIR := ../bin
LIB_DIR := ../release/$(BUILD_MODE)/lib
TARGET := $(BIN_DIR)/$(GAME_NAME)

# Compiler and flags
CXX := g++
CXXFLAGS := -Wall -Wextra -pedantic -Werror -std=c++11 -I../engine/include
LDFLAGS := -L$(LIB_DIR) -lsealengine

# Directories
SRC_DIR := src
OBJ_DIR := ../build

# Source files
SRC := $(wildcard $(SRC_DIR)/*.cpp)
OBJ := $(SRC:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJ) $(LIB_DIR)/libsealengine.so
	@mkdir -p $(BIN_DIR)
	@printf "  LD\t$(notdir $@)\n"
	@$(CXX) $(CXXFLAGS) $(OBJ) $(LDFLAGS) -o $(TARGET)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(OBJ_DIR)
	@printf "  CXX\t$<\n"
	@$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	@printf "  CLEAN (test)\n"
	@rm -rf $(BIN_DIR)
	@rm -rf $(OBJ_DIR)

.PHONY: all clean
