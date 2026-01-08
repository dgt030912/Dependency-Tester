#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

void test_math_functions() {
    printf("\n=== Testing Math Functions ===\n");
    
    // Factorial tests
    printf("factorial(5) = %d (expected: 120)\n", factorial(5));
    printf("factorial_long(10) = %lld (expected: 3628800)\n", factorial_long(10));
    assert(factorial(5) == 120);
    assert(factorial_long(10) == 3628800);
    
    // Fibonacci tests
    printf("fibonacci(10) = %d (expected: 55)\n", fibonacci(10));
    printf("fibonacci_long(20) = %lld (expected: 6765)\n", fibonacci_long(20));
    assert(fibonacci(10) == 55);
    assert(fibonacci_long(20) == 6765);
    
    // Prime tests
    printf("is_prime(17) = %s (expected: true)\n", is_prime(17) ? "true" : "false");
    printf("is_prime(18) = %s (expected: false)\n", is_prime(18) ? "true" : "false");
    assert(is_prime(17) == true);
    assert(is_prime(18) == false);
    
    // GCD/LCM tests
    printf("gcd(48, 18) = %d (expected: 6)\n", gcd(48, 18));
    printf("lcm(12, 18) = %d (expected: 36)\n", lcm(12, 18));
    assert(gcd(48, 18) == 6);
    assert(lcm(12, 18) == 36);
    
    // Power test
    printf("power(2.0, 10) = %.0f (expected: 1024)\n", power(2.0, 10));
    assert(power(2.0, 10) == 1024.0);
    
    printf("✓ All math tests passed!\n");
}

void test_string_functions() {
    printf("\n=== Testing String Functions ===\n");
    
    // String reversal
    char str1[] = "Hello World";
    printf("Original: %s\n", str1);
    reverse_string(str1);
    printf("Reversed: %s\n", str1);
    assert(strcmp(str1, "dlroW olleH") == 0);
    
    // String length
    printf("Length of 'Hello World': %d (expected: 11)\n", string_length("Hello World"));
    assert(string_length("Hello World") == 11);
    
    // String concatenation
    char* concat = string_concat("Hello ", "World");
    printf("Concatenated: %s (expected: Hello World)\n", concat);
    assert(strcmp(concat, "Hello World") == 0);
    free(concat);
    
    // String equality
    printf("'test' equals 'test': %s (expected: true)\n", 
           string_equals("test", "test") ? "true" : "false");
    assert(string_equals("test", "test") == true);
    assert(string_equals("test", "Test") == false);
    
    // Upper/lower case
    char str2[] = "Hello";
    string_to_upper(str2);
    printf("Uppercase: %s (expected: HELLO)\n", str2);
    assert(strcmp(str2, "HELLO") == 0);
    
    string_to_lower(str2);
    printf("Lowercase: %s (expected: hello)\n", str2);
    assert(strcmp(str2, "hello") == 0);
    
    // Vowel count
    int vowels = count_vowels("Hello World");
    printf("Vowels in 'Hello World': %d (expected: 3)\n", vowels);
    assert(vowels == 3);
    
    // Word count
    int words = count_words("Hello World This Is Test");
    printf("Words in 'Hello World This Is Test': %d (expected: 5)\n", words);
    assert(words == 5);
    
    printf("✓ All string tests passed!\n");
}

void test_array_functions() {
    printf("\n=== Testing Array Functions ===\n");
    
    int arr[] = {5, 2, 8, 1, 9, 3, 7, 4, 6};
    size_t size = sizeof(arr) / sizeof(arr[0]);
    
    // Sum and average
    int sum = sum_array(arr, size);
    printf("Sum: %d (expected: 45)\n", sum);
    assert(sum == 45);
    
    double avg = average_array(arr, size);
    printf("Average: %.2f (expected: 5.00)\n", avg);
    assert(avg == 5.0);
    
    // Min and max
    int max = find_max(arr, size);
    int min = find_min(arr, size);
    printf("Max: %d (expected: 9)\n", max);
    printf("Min: %d (expected: 1)\n", min);
    assert(max == 9);
    assert(min == 1);
    
    // Sort
    sort_array(arr, size);
    printf("Sorted: {");
    for (size_t i = 0; i < size; i++) {
        printf("%d%s", arr[i], i < size - 1 ? ", " : "");
    }
    printf("}\n");
    assert(arr[0] == 1 && arr[size-1] == 9);
    
    // Binary search
    int index = binary_search(arr, size, 7);
    printf("Index of 7: %d (expected: 6)\n", index);
    assert(index == 6);
    
    index = binary_search(arr, size, 10);
    printf("Index of 10: %d (expected: -1)\n", index);
    assert(index == -1);
    
    // Reverse
    reverse_array(arr, size);
    printf("Reversed: {");
    for (size_t i = 0; i < size; i++) {
        printf("%d%s", arr[i], i < size - 1 ? ", " : "");
    }
    printf("}\n");
    assert(arr[0] == 9 && arr[size-1] == 1);
    
    printf("✓ All array tests passed!\n");
}

void test_memory_functions() {
    printf("\n=== Testing Memory Functions ===\n");
    
    // Safe malloc
    int* ptr1 = (int*)safe_malloc(10 * sizeof(int));
    printf("safe_malloc: allocated 10 integers\n");
    ptr1[0] = 42;
    assert(ptr1[0] == 42);
    
    // Safe calloc
    int* ptr2 = (int*)safe_calloc(10, sizeof(int));
    printf("safe_calloc: allocated 10 integers (initialized to 0)\n");
    assert(ptr2[0] == 0);
    
    // Safe free
    safe_free((void**)&ptr1);
    safe_free((void**)&ptr2);
    printf("safe_free: freed both pointers\n");
    assert(ptr1 == NULL);
    assert(ptr2 == NULL);
    
    printf("✓ All memory tests passed!\n");
}

int main() {
    printf("\n╔════════════════════════════════════╗\n");
    printf("║   C Utilities Test Suite v2.0      ║\n");
    printf("╚════════════════════════════════════╝\n");
    
    test_math_functions();
    test_string_functions();
    test_array_functions();
    test_memory_functions();
    
    printf("\n╔════════════════════════════════════╗\n");
    printf("║   ✓ ALL TESTS PASSED!              ║\n");
    printf("╚════════════════════════════════════╝\n\n");
    
    return 0;
}
