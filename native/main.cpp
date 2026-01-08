#include "task_processor.h"
#include "utils.h"
#include <iostream>
#include <iomanip>

void print_separator() {
    std::cout << std::string(60, '=') << std::endl;
}

void test_task_processor() {
    print_separator();
    std::cout << "Testing C++ TaskProcessor (Enhanced)" << std::endl;
    print_separator();
    
    TaskProcessor processor;
    
    // Add tasks with different priorities
    processor.addTask("Implement user authentication", "Add OAuth2 support", TaskPriority::HIGH);
    processor.addTask("Fix memory leak in parser", "Valgrind reports leak", TaskPriority::CRITICAL);
    processor.addTask("Update documentation", "Add API examples", TaskPriority::LOW);
    processor.addTask("Optimize database queries", "Reduce query time by 50%", TaskPriority::MEDIUM);
    processor.addTask("Add unit tests", "Cover edge cases", TaskPriority::HIGH);
    processor.addTask("Deploy to production", "Schedule maintenance window", TaskPriority::CRITICAL);
    
    std::cout << "\n" << processor.getTaskSummary() << std::endl;
    
    // Process critical tasks first
    std::cout << "\n--- Processing CRITICAL priority tasks ---" << std::endl;
    processor.processByPriority(TaskPriority::CRITICAL);
    
    // Process specific task
    std::cout << "\n--- Processing specific task #1 ---" << std::endl;
    processor.processTask(1);
    
    // Update task priority
    std::cout << "\n--- Updating task #3 priority ---" << std::endl;
    processor.updateTaskPriority(3, TaskPriority::HIGH);
    
    // Process all remaining tasks
    std::cout << "\n--- Processing all remaining tasks ---" << std::endl;
    processor.processAll();
    
    // Print final summary
    std::cout << "\n" << processor.getTaskSummary() << std::endl;
    
    // Query tasks by status
    auto completed = processor.getTasksByStatus(TaskStatus::COMPLETED);
    std::cout << "\nCompleted tasks (" << completed.size() << "):" << std::endl;
    for (const auto& task : completed) {
        std::cout << "  #" << task->id << ": " << task->title 
                  << " [" << priorityToString(task->priority) << "]" << std::endl;
    }
    
    // Clear completed tasks
    std::cout << "\n--- Clearing completed tasks ---" << std::endl;
    processor.clearCompleted();
    
    std::cout << "\n" << processor.getTaskSummary() << std::endl;
}

void test_c_utilities() {
    print_separator();
    std::cout << "Testing C Utilities (Enhanced)" << std::endl;
    print_separator();
    
    std::cout << "\n--- Mathematical Functions ---" << std::endl;
    std::cout << "factorial(7) = " << factorial(7) << std::endl;
    std::cout << "factorial_long(15) = " << factorial_long(15) << std::endl;
    std::cout << "fibonacci(12) = " << fibonacci(12) << std::endl;
    std::cout << "fibonacci_long(25) = " << fibonacci_long(25) << std::endl;
    std::cout << "is_prime(29) = " << (is_prime(29) ? "true" : "false") << std::endl;
    std::cout << "is_prime(30) = " << (is_prime(30) ? "true" : "false") << std::endl;
    std::cout << "gcd(56, 98) = " << gcd(56, 98) << std::endl;
    std::cout << "lcm(15, 25) = " << lcm(15, 25) << std::endl;
    std::cout << "power(2.5, 3) = " << std::fixed << std::setprecision(2) 
              << power(2.5, 3) << std::endl;
    
    std::cout << "\n--- String Functions ---" << std::endl;
    char test_str[] = "Hello C++ World";
    std::cout << "Original: " << test_str << std::endl;
    std::cout << "Length: " << string_length(test_str) << std::endl;
    std::cout << "Vowels: " << count_vowels(test_str) << std::endl;
    std::cout << "Words: " << count_words(test_str) << std::endl;
    
    char* concat = string_concat("C++ ", "Native Code");
    std::cout << "Concatenated: " << concat << std::endl;
    free(concat);
    
    string_to_upper(test_str);
    std::cout << "Uppercase: " << test_str << std::endl;
    string_to_lower(test_str);
    std::cout << "Lowercase: " << test_str << std::endl;
    reverse_string(test_str);
    std::cout << "Reversed: " << test_str << std::endl;
    
    std::cout << "\n--- Array Functions ---" << std::endl;
    int arr[] = {15, 3, 9, 21, 7, 12, 6, 18, 4};
    size_t size = sizeof(arr) / sizeof(arr[0]);
    
    std::cout << "Array: {";
    for (size_t i = 0; i < size; i++) {
        std::cout << arr[i] << (i < size - 1 ? ", " : "");
    }
    std::cout << "}" << std::endl;
    
    std::cout << "Sum: " << sum_array(arr, size) << std::endl;
    std::cout << "Average: " << std::fixed << std::setprecision(2) 
              << average_array(arr, size) << std::endl;
    std::cout << "Max: " << find_max(arr, size) << std::endl;
    std::cout << "Min: " << find_min(arr, size) << std::endl;
    
    sort_array(arr, size);
    std::cout << "Sorted: {";
    for (size_t i = 0; i < size; i++) {
        std::cout << arr[i] << (i < size - 1 ? ", " : "");
    }
    std::cout << "}" << std::endl;
    
    int search_val = 12;
    int index = binary_search(arr, size, search_val);
    std::cout << "Index of " << search_val << ": " << index << std::endl;
    
    reverse_array(arr, size);
    std::cout << "Reversed: {";
    for (size_t i = 0; i < size; i++) {
        std::cout << arr[i] << (i < size - 1 ? ", " : "");
    }
    std::cout << "}" << std::endl;
}

int main() {
    std::cout << "\n";
    std::cout << "╔══════════════════════════════════════════════════════════╗\n";
    std::cout << "║         Native C/C++ Test Suite - Enhanced v2.0         ║\n";
    std::cout << "╚══════════════════════════════════════════════════════════╝\n";
    std::cout << std::endl;
    
    try {
        test_task_processor();
        std::cout << std::endl;
        test_c_utilities();
        
        std::cout << std::endl;
        print_separator();
        std::cout << "✓ All tests completed successfully!" << std::endl;
        print_separator();
        std::cout << std::endl;
        
        return 0;
    }
    catch (const std::exception& e) {
        std::cerr << "\n✗ Error: " << e.what() << std::endl;
        return 1;
    }
}
