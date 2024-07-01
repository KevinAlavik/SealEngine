CXX ?= g++
CXXFLAGS := -Wall -pedantic -Werror -Wshadow -Wstrict-aliasing -Wstrict-overflow -O3
CXXFLAGS += -MMD -MP
CXXFLAGS += $(shell pkg-config --cflags sdl2)
CXXFLAGS += -Iengine/include

BIN_DIR := bin
OBJ_DIR := build
SRC_DIR := engine/src
DESTDIR ?= /usr/local/bin

TARGET_NAME := seal
TARGET := $(BIN_DIR)/$(TARGET_NAME)

# Find all .cpp files recursively
SRC := $(shell find $(SRC_DIR) -name '*.cpp')
OBJ := $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRC))
DEP := $(OBJ:.o=.d)

LDFLAGS := $(shell pkg-config --libs sdl2)

.PHONY: all
all: $(TARGET)

$(TARGET): $(OBJ)
	@mkdir -p $(BIN_DIR)
	@printf "  LD\t$(notdir $@)\n"
	@$(CXX) $(LDFLAGS) $(OBJ) -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(dir $@)
	@printf "  CXX\t$<\n"
	@$(CXX) $(CXXFLAGS) -c $< -o $@

-include $(DEP)

.PHONY: install
install: $(TARGET)
	@mkdir -p $(DESTDIR)
	@printf "  INSTALL\t$(TARGET_NAME) to $(DESTDIR)\n"
	@install -m 755 $(TARGET) $(DESTDIR)

.PHONY: clean
clean:
	@printf "  CLEAN\n"
	@rm -rf $(BIN_DIR) $(OBJ_DIR)

.PHONY: all install clean
