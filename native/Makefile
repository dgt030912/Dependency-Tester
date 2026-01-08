# Makefile for Native C/C++ Code - Enhanced v2.0
# Supports: Linux, macOS, Windows (MinGW/MSYS2)

# Compilers
CC = gcc
CXX = g++

# Compiler flags
CFLAGS = -Wall -Wextra -O2 -fPIC -std=c11
CXXFLAGS = -Wall -Wextra -O2 -fPIC -std=c++17
LDFLAGS =

# Detect operating system
UNAME_S := $(shell uname -s 2>/dev/null || echo Windows)

ifeq ($(UNAME_S),Darwin)
    # macOS
    SHARED_EXT = dylib
    SHARED_FLAGS = -dynamiclib
    PLATFORM = macOS
else ifeq ($(UNAME_S),Linux)
    # Linux
    SHARED_EXT = so
    SHARED_FLAGS = -shared
    PLATFORM = Linux
else
    # Windows (assumes MinGW/MSYS2)
    SHARED_EXT = dll
    SHARED_FLAGS = -shared
    PLATFORM = Windows
    # Add .exe extension for Windows executables
    EXE_EXT = .exe
endif

# Source files
C_SOURCES = utils.c
C_HEADERS = utils.h
CPP_SOURCES = task_processor.cpp
CPP_HEADERS = task_processor.h

# Object files
C_OBJECTS = $(C_SOURCES:.c=.o)
CPP_OBJECTS = $(CPP_SOURCES:.cpp=.o)

# Output files
SHARED_LIB = libutils.$(SHARED_EXT)
TEST_BINARY = test_utils$(EXE_EXT)
MAIN_BINARY = main$(EXE_EXT)

# Colors for output (if terminal supports)
COLOR_RESET = \033[0m
COLOR_BOLD = \033[1m
COLOR_GREEN = \033[32m
COLOR_BLUE = \033[34m
COLOR_YELLOW = \033[33m

# Default target
all: banner $(SHARED_LIB) $(TEST_BINARY) $(MAIN_BINARY)
	@echo "$(COLOR_GREEN)$(COLOR_BOLD)✓ Build complete!$(COLOR_RESET)"
	@echo "$(COLOR_BLUE)Platform: $(PLATFORM)$(COLOR_RESET)"
	@echo "$(COLOR_BLUE)Shared library: $(SHARED_LIB)$(COLOR_RESET)"
	@echo "$(COLOR_BLUE)Executables: $(TEST_BINARY), $(MAIN_BINARY)$(COLOR_RESET)"

banner:
	@echo "$(COLOR_BOLD)======================================$(COLOR_RESET)"
	@echo "$(COLOR_BOLD)  Building Native C/C++ Code v2.0    $(COLOR_RESET)"
	@echo "$(COLOR_BOLD)======================================$(COLOR_RESET)"

# Compile C source files to object files
%.o: %.c $(C_HEADERS)
	@echo "$(COLOR_YELLOW)Compiling C: $<$(COLOR_RESET)"
	$(CC) $(CFLAGS) -c $< -o $@

# Compile C++ source files to object files
%.o: %.cpp $(CPP_HEADERS)
	@echo "$(COLOR_YELLOW)Compiling C++: $<$(COLOR_RESET)"
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Build shared library from C utilities
$(SHARED_LIB): $(C_OBJECTS)
	@echo "$(COLOR_YELLOW)Building shared library: $@$(COLOR_RESET)"
	$(CC) $(CFLAGS) $(SHARED_FLAGS) -o $@ $(C_OBJECTS) $(LDFLAGS)

# Build test binary (C only)
$(TEST_BINARY): test_utils.c $(C_SOURCES) $(C_HEADERS)
	@echo "$(COLOR_YELLOW)Building test binary: $@$(COLOR_RESET)"
	$(CC) $(CFLAGS) -o $@ test_utils.c $(C_SOURCES) $(LDFLAGS)

# Build main binary (C++ with C dependencies)
$(MAIN_BINARY): main.cpp $(CPP_SOURCES) $(CPP_HEADERS) $(C_SOURCES) $(C_HEADERS)
	@echo "$(COLOR_YELLOW)Building main binary: $@$(COLOR_RESET)"
	$(CXX) $(CXXFLAGS) -o $@ main.cpp $(CPP_SOURCES) $(C_SOURCES) $(LDFLAGS)

# Run C utility tests
test: $(TEST_BINARY)
	@echo "$(COLOR_BOLD)Running C utility tests...$(COLOR_RESET)"
	./$(TEST_BINARY)

# Run main C++ program
run: $(MAIN_BINARY)
	@echo "$(COLOR_BOLD)Running main program...$(COLOR_RESET)"
	./$(MAIN_BINARY)

# Run both tests and main program
run-all: test run

# Install shared library (optional - requires sudo on Linux/macOS)
install: $(SHARED_LIB)
	@echo "$(COLOR_YELLOW)Installing $(SHARED_LIB)...$(COLOR_RESET)"
ifeq ($(PLATFORM),macOS)
	cp $(SHARED_LIB) /usr/local/lib/
	@echo "$(COLOR_GREEN)Installed to /usr/local/lib/$(COLOR_RESET)"
else ifeq ($(PLATFORM),Linux)
	cp $(SHARED_LIB) /usr/local/lib/
	ldconfig
	@echo "$(COLOR_GREEN)Installed to /usr/local/lib/$(COLOR_RESET)"
else
	@echo "$(COLOR_YELLOW)Manual installation required on Windows$(COLOR_RESET)"
	@echo "Copy $(SHARED_LIB) to a directory in your PATH"
endif

# Clean build artifacts
clean:
	@echo "$(COLOR_YELLOW)Cleaning build artifacts...$(COLOR_RESET)"
	rm -f $(C_OBJECTS) $(CPP_OBJECTS)
	rm -f $(SHARED_LIB)
	rm -f $(TEST_BINARY) $(MAIN_BINARY)
	rm -f *.so *.dylib *.dll *.exe
	@echo "$(COLOR_GREEN)Clean complete!$(COLOR_RESET)"

# Full rebuild
rebuild: clean all

# Help target
help:
	@echo "$(COLOR_BOLD)Available targets:$(COLOR_RESET)"
	@echo "  $(COLOR_GREEN)all$(COLOR_RESET)        - Build everything (default)"
	@echo "  $(COLOR_GREEN)test$(COLOR_RESET)       - Build and run C utility tests"
	@echo "  $(COLOR_GREEN)run$(COLOR_RESET)        - Build and run main C++ program"
	@echo "  $(COLOR_GREEN)run-all$(COLOR_RESET)    - Run both tests and main program"
	@echo "  $(COLOR_GREEN)clean$(COLOR_RESET)      - Remove all build artifacts"
	@echo "  $(COLOR_GREEN)rebuild$(COLOR_RESET)    - Clean and rebuild everything"
	@echo "  $(COLOR_GREEN)install$(COLOR_RESET)    - Install shared library (requires sudo)"
	@echo "  $(COLOR_GREEN)help$(COLOR_RESET)       - Show this help message"

# Debug build with symbols
debug: CFLAGS += -g -O0 -DDEBUG
debug: CXXFLAGS += -g -O0 -DDEBUG
debug: clean all
	@echo "$(COLOR_GREEN)Debug build complete!$(COLOR_RESET)"

# Phony targets
.PHONY: all banner test run run-all clean rebuild install help debug
