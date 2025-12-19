# Native C/C++ Utilities

This directory contains C and C++ utility code for the Dependency-Tester project.

## Structure

- **utils.c / utils.h** - C utility functions (factorial, fibonacci, prime checking, string manipulation)
- **task_processor.cpp / task_processor.h** - C++ TaskProcessor class for task management
- **main.cpp** - Example C++ program demonstrating TaskProcessor
- **test_utils.c** - Test program for C utilities
- **Makefile** - Build configuration

## Building

### Prerequisites
- GCC compiler (for C)
- G++ compiler (for C++)
- Make

### Build Commands

Build everything:
```bash
make all
```

Build only C utilities:
```bash
make c
```

Build only C++ programs:
```bash
make cpp
```

Run C tests:
```bash
make test
```

Run C++ demo:
```bash
make demo
```

Clean build artifacts:
```bash
make clean
```

## C Utilities

The `utils.c` file provides:
- `factorial(int n)` - Calculate factorial
- `fibonacci(int n)` - Calculate Fibonacci number
- `is_prime(int n)` - Check if number is prime
- `reverse_string(char* str)` - Reverse a string
- `array_sum(int* arr, int size)` - Sum array elements

## C++ TaskProcessor

The `TaskProcessor` class provides:
- Add/remove tasks
- Sort tasks alphabetically
- Search tasks
- Calculate priority scores
- Format timestamps

## Integration with Python

These native modules can be integrated with Python using:
- **ctypes** (for C functions)
- **pybind11** (for C++ classes)
- **Cython** (for wrapping C/C++ code)

## Example Usage

### C Example
```c
#include "utils.h"

int main() {
    long long fact = factorial(5);  // 120
    long long fib = fibonacci(10);  // 55
    int prime = is_prime(17);       // 1 (true)
    return 0;
}
```

### C++ Example
```cpp
#include "task_processor.h"

int main() {
    TaskProcessor processor;
    processor.addTask("Complete project");
    processor.sortTasks();
    std::cout << processor.toString();
    return 0;
}
```

