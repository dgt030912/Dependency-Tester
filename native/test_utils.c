#include <stdio.h>
#include <assert.h>
#include "utils.h"

/**
 * Test program for C utility functions
 */
int main() {
    printf("=== Testing C Utility Functions ===\n\n");
    
    // Test factorial
    printf("Testing factorial:\n");
    assert(factorial(0) == 1);
    assert(factorial(1) == 1);
    assert(factorial(5) == 120);
    printf("  factorial(5) = %lld ✓\n", factorial(5));
    
    // Test fibonacci
    printf("\nTesting fibonacci:\n");
    assert(fibonacci(0) == 0);
    assert(fibonacci(1) == 1);
    assert(fibonacci(10) == 55);
    printf("  fibonacci(10) = %lld ✓\n", fibonacci(10));
    
    // Test is_prime
    printf("\nTesting is_prime:\n");
    assert(is_prime(2) == 1);
    assert(is_prime(3) == 1);
    assert(is_prime(4) == 0);
    assert(is_prime(17) == 1);
    printf("  is_prime(17) = %d ✓\n", is_prime(17));
    
    // Test reverse_string
    printf("\nTesting reverse_string:\n");
    char str[] = "Hello World";
    reverse_string(str);
    printf("  Reversed: %s ✓\n", str);
    assert(strcmp(str, "dlroW olleH") == 0);
    
    // Test array_sum
    printf("\nTesting array_sum:\n");
    int arr[] = {1, 2, 3, 4, 5};
    long long sum = array_sum(arr, 5);
    assert(sum == 15);
    printf("  array_sum([1,2,3,4,5]) = %lld ✓\n", sum);
    
    printf("\n=== All tests passed! ===\n");
    return 0;
}

