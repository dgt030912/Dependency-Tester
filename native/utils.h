#ifndef UTILS_H
#define UTILS_H

#include <stddef.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

// ============ Mathematical Utilities ============

/**
 * Calculate factorial (int version)
 */
int factorial(int n);

/**
 * Calculate factorial (long long version for larger numbers)
 */
long long factorial_long(int n);

/**
 * Calculate Fibonacci number (optimized iterative)
 */
int fibonacci(int n);

/**
 * Calculate Fibonacci (long long version)
 */
long long fibonacci_long(int n);

/**
 * Check if number is prime
 */
bool is_prime(int n);

/**
 * Calculate greatest common divisor
 */
int gcd(int a, int b);

/**
 * Calculate least common multiple
 */
int lcm(int a, int b);

/**
 * Calculate power (base^exponent)
 */
double power(double base, int exponent);

// ============ String Utilities ============

/**
 * Reverse a string in place
 */
void reverse_string(char* str);

/**
 * Get string length
 */
int string_length(const char* str);

/**
 * Concatenate two strings (caller must free result)
 */
char* string_concat(const char* str1, const char* str2);

/**
 * Check if two strings are equal
 */
bool string_equals(const char* str1, const char* str2);

/**
 * Convert string to uppercase (in place)
 */
char* string_to_upper(char* str);

/**
 * Convert string to lowercase (in place)
 */
char* string_to_lower(char* str);

/**
 * Count vowels in a string
 */
int count_vowels(const char* str);

/**
 * Count words in a string
 */
int count_words(const char* str);

// ============ Array Utilities ============

/**
 * Sum all elements in array
 */
int sum_array(const int* arr, size_t size);

/**
 * Calculate average of array
 */
double average_array(const int* arr, size_t size);

/**
 * Find maximum value in array
 */
int find_max(const int* arr, size_t size);

/**
 * Find minimum value in array
 */
int find_min(const int* arr, size_t size);

/**
 * Sort array using bubble sort (in place)
 */
void sort_array(int* arr, size_t size);

/**
 * Binary search (assumes sorted array)
 */
int binary_search(const int* arr, size_t size, int target);

/**
 * Reverse array in place
 */
void reverse_array(int* arr, size_t size);

// ============ Memory Utilities ============

/**
 * Safe malloc with error checking
 */
void* safe_malloc(size_t size);

/**
 * Safe calloc with error checking
 */
void* safe_calloc(size_t num, size_t size);

/**
 * Safe free that nullifies pointer
 */
void safe_free(void** ptr);

#ifdef __cplusplus
}
#endif

#endif // UTILS_H
