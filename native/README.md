# Native C/C++ Code - Enhanced v2.0

This directory contains enhanced native C and C++ utility code that can be used standalone or integrated with the Python backend through bindings.

## 📁 Files

### C Utilities
- **`utils.h` / `utils.c`** - Comprehensive C utility library
  - **Mathematical operations**: factorial, fibonacci, prime checking, GCD, LCM, power
  - **String manipulation**: reverse, concatenate, case conversion, vowel/word counting
  - **Array operations**: sum, average, min/max, sort, binary search, reverse
  - **Memory utilities**: safe allocation and deallocation

### C++ Components
- **`task_processor.h` / `task_processor.cpp`** - Advanced task processing system
  - Task management with priorities (LOW, MEDIUM, HIGH, CRITICAL)
  - Task status tracking (PENDING, IN_PROGRESS, COMPLETED, FAILED)
  - Batch processing with priority-based ordering
  - Comprehensive statistics and reporting
  - Smart pointers for memory safety

### Test Programs
- **`test_utils.c`** - Comprehensive test suite for C utilities
- **`main.cpp`** - Integrated demonstration of C and C++ functionality

### Build System
- **`Makefile`** - Enhanced build system with platform detection
  - Cross-platform support (Linux, macOS, Windows)
  - Colored output for better readability
  - Multiple build targets (debug, release, install)

## 🔨 Building

### Quick Start
```bash
# Build everything
make all

# Run C utility tests
make test

# Run main C++ program
make run

# Run both
make run-all
```

### Advanced Build Options
```bash
# Clean all build artifacts
make clean

# Full rebuild
make rebuild

# Debug build (with symbols, no optimization)
make debug

# Install shared library (requires sudo)
make install

# Show all available targets
make help
```

## 🧪 C Utilities API

### Mathematical Functions
```c
int factorial(int n);                    // Factorial (int)
long long factorial_long(int n);         // Factorial (long long)
int fibonacci(int n);                    // Fibonacci (int)
long long fibonacci_long(int n);         // Fibonacci (long long)
bool is_prime(int n);                    // Prime number check
int gcd(int a, int b);                   // Greatest common divisor
int lcm(int a, int b);                   // Least common multiple
double power(double base, int exponent); // Power calculation
```

### String Functions
```c
void reverse_string(char* str);                      // Reverse in place
int string_length(const char* str);                  // Get length
char* string_concat(const char* s1, const char* s2); // Concatenate (allocates)
bool string_equals(const char* s1, const char* s2);  // Compare equality
char* string_to_upper(char* str);                    // Convert to uppercase
char* string_to_lower(char* str);                    // Convert to lowercase
int count_vowels(const char* str);                   // Count vowels
int count_words(const char* str);                    // Count words
```

### Array Functions
```c
int sum_array(const int* arr, size_t size);        // Sum elements
double average_array(const int* arr, size_t size); // Calculate average
int find_max(const int* arr, size_t size);         // Find maximum
int find_min(const int* arr, size_t size);         // Find minimum
void sort_array(int* arr, size_t size);            // Sort (bubble sort)
int binary_search(const int* arr, size_t size, int target); // Binary search
void reverse_array(int* arr, size_t size);         // Reverse in place
```

### Memory Functions
```c
void* safe_malloc(size_t size);           // Malloc with error checking
void* safe_calloc(size_t num, size_t sz); // Calloc with error checking
void safe_free(void** ptr);               // Free and nullify pointer
```

## 🔧 C++ TaskProcessor API

### Task Management
```cpp
// Create processor
TaskProcessor processor;

// Add tasks
int id = processor.addTask("Task title", "Description", TaskPriority::HIGH);

// Manage tasks
processor.removeTask(id);
processor.updateTaskStatus(id, TaskStatus::COMPLETED);
processor.updateTaskPriority(id, TaskPriority::CRITICAL);
```

### Processing
```cpp
// Process specific task
processor.processTask(id);

// Process by priority
processor.processByPriority(TaskPriority::CRITICAL);

// Process all tasks (priority-ordered)
processor.processAll();
```

### Queries
```cpp
// Get tasks
auto task = processor.getTask(id);
auto all = processor.getAllTasks();
auto pending = processor.getTasksByStatus(TaskStatus::PENDING);
auto high = processor.getTasksByPriority(TaskPriority::HIGH);

// Statistics
int total = processor.getTotalCount();
int processed = processor.getProcessedCount();
auto stats = processor.getPriorityStats();
std::string summary = processor.getTaskSummary();
```

## 🐍 Python Integration

The C utilities can be integrated into Python using `ctypes`. See `backend/native_bindings.py` for examples.

```python
from native_bindings import (
    factorial, fibonacci, is_prime,
    reverse_string, string_length
)

# Use C functions from Python
print(factorial(5))           # 120
print(fibonacci(10))          # 55
print(is_prime(17))          # True

text = "Hello"
reverse_string(text)
print(text)                   # "olleH"
```

## 🖥️ Platform Support

| Platform | Compiler | Status |
|----------|----------|--------|
| **Linux** | gcc/g++ 7+ | ✅ Fully supported |
| **macOS** | clang/clang++ (Xcode CLT) | ✅ Fully supported |
| **Windows** | MinGW/MSYS2 gcc/g++ | ✅ Fully supported |

## 📋 Requirements

- **C Compiler**: gcc/clang with C11 support
- **C++ Compiler**: g++/clang++ with C++17 support
- **Build Tool**: GNU Make 3.8+
- **Optional**: ctypes (for Python integration)

## 🎯 Features

### C Utilities
- ✅ Comprehensive mathematical functions
- ✅ Advanced string manipulation
- ✅ Efficient array operations
- ✅ Safe memory management
- ✅ Full test coverage

### C++ Task Processor
- ✅ Priority-based task scheduling
- ✅ Status tracking and reporting
- ✅ Smart pointer memory management
- ✅ Detailed statistics and summaries
- ✅ Exception-safe design

### Build System
- ✅ Cross-platform Makefile
- ✅ Automatic OS detection
- ✅ Colored terminal output
- ✅ Debug and release builds
- ✅ System-wide installation support

## 📚 Examples

### C Example
```c
#include "utils.h"

int main() {
    // Math
    int fact = factorial(5);                    // 120
    bool prime = is_prime(17);                  // true
    int g = gcd(48, 18);                       // 6
    
    // Strings
    char str[] = "Hello";
    string_to_upper(str);                      // "HELLO"
    int vowels = count_vowels(str);            // 2
    
    // Arrays
    int arr[] = {5, 2, 8, 1, 9};
    sort_array(arr, 5);                        // {1, 2, 5, 8, 9}
    int idx = binary_search(arr, 5, 8);        // 3
    
    return 0;
}
```

### C++ Example
```cpp
#include "task_processor.h"

int main() {
    TaskProcessor proc;
    
    // Add tasks
    proc.addTask("Fix bug", "Critical bug", TaskPriority::CRITICAL);
    proc.addTask("Add feature", "New feature", TaskPriority::HIGH);
    
    // Process all (critical first)
    proc.processAll();
    
    // Get statistics
    std::cout << proc.getTaskSummary() << std::endl;
    
    return 0;
}
```

## 🤝 Contributing

Feel free to extend the utilities with additional functions. Follow the existing code style and add tests for new functionality.

## 📄 License

Part of the Dependency-Tester project.
