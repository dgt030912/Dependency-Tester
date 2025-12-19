# Makefile for building C and C++ utilities

CC = gcc
CXX = g++
CFLAGS = -Wall -Wextra -std=c11 -O2
CXXFLAGS = -Wall -Wextra -std=c++17 -O2
LDFLAGS = 

# Directories
SRC_DIR = .
BUILD_DIR = build

# C targets
C_UTILS = $(BUILD_DIR)/libutils.so
C_TEST = $(BUILD_DIR)/test_utils

# C++ targets
CPP_PROCESSOR = $(BUILD_DIR)/task_processor
CPP_MAIN = $(BUILD_DIR)/main

.PHONY: all clean c cpp test

all: c cpp

# Create build directory
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# C targets
c: $(BUILD_DIR) $(C_UTILS) $(C_TEST)

$(C_UTILS): utils.c utils.h | $(BUILD_DIR)
	$(CC) $(CFLAGS) -shared -fPIC -o $@ utils.c $(LDFLAGS)

$(C_TEST): test_utils.c utils.c utils.h | $(BUILD_DIR)
	$(CC) $(CFLAGS) -o $@ test_utils.c utils.c $(LDFLAGS) -lm

# C++ targets
cpp: $(BUILD_DIR) $(CPP_PROCESSOR) $(CPP_MAIN)

$(CPP_PROCESSOR): task_processor.cpp task_processor.h | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -o $@ task_processor.cpp $(LDFLAGS)

$(CPP_MAIN): main.cpp task_processor.cpp task_processor.h | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -o $@ main.cpp task_processor.cpp $(LDFLAGS)

# Run tests
test: $(C_TEST)
	./$(C_TEST)

# Run C++ demo
demo: $(CPP_MAIN)
	./$(CPP_MAIN)

# Clean build artifacts
clean:
	rm -rf $(BUILD_DIR)

# Help
help:
	@echo "Available targets:"
	@echo "  all      - Build all C and C++ targets"
	@echo "  c        - Build C utilities and tests"
	@echo "  cpp      - Build C++ programs"
	@echo "  test     - Run C utility tests"
	@echo "  demo     - Run C++ demo program"
	@echo "  clean    - Remove build artifacts"
	@echo "  help     - Show this help message"

