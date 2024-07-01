# Variables
BUILD_MODE := dev
LIB_DIR := ../release/$(BUILD_MODE)/lib
OBJ_DIR := ../build/engine
SRC_DIR := src

# SDL2 configuration
SDL2_CFLAGS := $(shell sdl2-config --cflags)
SDL2_LDFLAGS := $(shell sdl2-config --libs)

# Compiler and flags
CXX := g++
CXXFLAGS := -Wall -Wextra -pedantic -Werror -std=c++11 -fPIC $(SDL2_CFLAGS) -Iinclude/
LDFLAGS := -shared $(SDL2_LDFLAGS)

# Find all .cpp files recursively
SRC := $(shell find $(SRC_DIR) -name '*.cpp')
OBJ := $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRC))
DEP := $(OBJ:.o=.d)

# Target library
LIBRARY := $(LIB_DIR)/libsealengine.so

.PHONY: all clean install

all: $(LIBRARY)

$(LIBRARY): $(OBJ)
	@mkdir -p $(LIB_DIR)
	@printf "  LD\t$(notdir $@)\n"
	@$(CXX) $(LDFLAGS) $(OBJ) -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(dir $@)
	@printf "  CXX\t$<\n"
	@$(CXX) $(CXXFLAGS) -c $< -o $@

-include $(DEP)

clean:
	@printf "  CLEAN (engine)\n"
	@rm -rf $(LIBRARY) $(OBJ_DIR)

install: $(LIBRARY)
	@printf "  INSTALL\t$(notdir $(LIBRARY)) to /usr/local/lib\n"
	@install -m 755 $(LIBRARY) /usr/local/lib

.PHONY: all clean install
