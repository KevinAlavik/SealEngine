MAKEFLAGS += --no-print-directory

# Variables
BUILD_MODE := dev
BIN_DIR := bin
RELEASE_DIR := release/$(BUILD_MODE)
LIB_DIR := $(RELEASE_DIR)/lib
TARGET := $(BIN_DIR)/TestGame

# Directories
ENGINE_DIR := engine
TEST_DIR := test

.PHONY: all engine test clean

all: engine test

engine:
	@$(MAKE) -C $(ENGINE_DIR)

test: $(TARGET)

$(TARGET): engine
	@mkdir -p $(BIN_DIR)
	@$(MAKE) -C $(TEST_DIR)

clean:
	@printf "  CLEAN\n"
	@$(MAKE) -C $(ENGINE_DIR) clean
	@$(MAKE) -C $(TEST_DIR) clean
	@rm -rf $(BIN_DIR) $(RELEASE_DIR)

.PHONY: all engine test clean
