CXX ?= g++
CXXFLAGS := -Wall -pedantic -Werror -Wshadow -Wstrict-aliasing -Wstrict-overflow -O3
CXXFLAGS += -MMD -MP

BIN_DIR := bin
OBJ_DIR := build
SRC_DIR := src
DESTDIR ?= /usr/local/bin

TARGET_NAME := seal
TARGET := $(BIN_DIR)/$(TARGET_NAME)
SRC := $(wildcard $(SRC_DIR)/*.cpp)
OBJ := $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRC))
DEP := $(OBJ:.o=.d)

LDFLAGS := 

.PHONY: all
all: $(TARGET)

$(TARGET): $(OBJ)
	@mkdir -p $(BIN_DIR)
	@printf "  LD\t$(notdir $@)\n"
	@$(CXX) $(LDFLAGS) $(OBJ) -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(OBJ_DIR)
	@printf "  CXX\t$<\n"
	@$(CXX) $(CXXFLAGS) -c $< -o $@


-include $(DEP)

.PHONY: install
install: $(TARGET)
	@install -m 755 $(TARGET) $(DESTDIR)

.PHONY: clean
clean:
	@rm -rf $(BIN_DIR) $(OBJ_DIR)

.PHONY: all install clean