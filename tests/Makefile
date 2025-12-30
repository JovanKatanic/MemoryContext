# tests/Makefile
CC = gcc
CFLAGS = -Wall -Wextra -std=c17 -g -I../include -I./unity
LDFLAGS =

# Directories
SRC_DIR = ../src
OBJ_DIR = obj
BIN_DIR = bin
UNITY_DIR = unity

# Library sources (exclude main.c)
LIB_SRCS = $(filter-out $(SRC_DIR)/main.c, $(wildcard $(SRC_DIR)/*.c))
LIB_OBJS = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(LIB_SRCS))

# Unity
UNITY_SRC = $(UNITY_DIR)/unity.c
UNITY_OBJ = $(OBJ_DIR)/unity.o

# Test files
TEST_SRCS = $(wildcard test_*.c)
TEST_EXES = $(patsubst %.c, $(BIN_DIR)/%, $(TEST_SRCS))

# Default: run all tests
all: run-tests

# Build all tests
build: $(TEST_EXES)

# Run all tests
run-tests: build
	@echo "=========================================="
	@echo "Running tests..."
	@echo "=========================================="
	@for test in $(TEST_EXES); do \
		echo "\n▶ Running $$test"; \
		if $$test; then \
			echo "  ✓ PASSED"; \
		else \
			echo "  ✗ FAILED"; \
			exit 1; \
		fi; \
	done
	@echo "\n=========================================="
	@echo "✓ All tests passed!"
	@echo "=========================================="

# Create directories
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

# Compile library objects
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Compile Unity
$(UNITY_OBJ): $(UNITY_SRC) | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Compile and link test executables
$(BIN_DIR)/test_%: test_%.c $(LIB_OBJS) $(UNITY_OBJ) | $(BIN_DIR)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

# Run with Valgrind
valgrind: build
	@echo "Running tests with Valgrind..."
	@for test in $(TEST_EXES); do \
		echo "\n▶ Valgrind: $$test"; \
		valgrind --leak-check=full --show-leak-kinds=all $$test; \
	done

# Run with AddressSanitizer
asan: CFLAGS += -fsanitize=address
asan: LDFLAGS += -fsanitize=address
asan: clean build
	@echo "Running tests with AddressSanitizer..."
	@for test in $(TEST_EXES); do \
		echo "\n▶ ASan: $$test"; \
		$$test; \
	done

# Clean
clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)

.PHONY: all build run-tests valgrind asan clean