#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

/**
 * Calculate factorial of a number
 * @param n: The number to calculate factorial for
 * @return: Factorial of n, or -1 if n < 0
 */
long long factorial(int n) {
    if (n < 0) {
        return -1;
    }
    if (n == 0 || n == 1) {
        return 1;
    }
    
    long long result = 1;
    for (int i = 2; i <= n; i++) {
        result *= i;
    }
    return result;
}

/**
 * Calculate Fibonacci number at position n
 * @param n: Position in Fibonacci sequence
 * @return: Fibonacci number at position n
 */
long long fibonacci(int n) {
    if (n < 0) {
        return -1;
    }
    if (n == 0) {
        return 0;
    }
    if (n == 1 || n == 2) {
        return 1;
    }
    
    long long a = 1, b = 1, temp;
    for (int i = 3; i <= n; i++) {
        temp = a + b;
        a = b;
        b = temp;
    }
    return b;
}

/**
 * Check if a number is prime
 * @param n: Number to check
 * @return: 1 if prime, 0 if not prime
 */
int is_prime(int n) {
    if (n < 2) {
        return 0;
    }
    if (n == 2) {
        return 1;
    }
    if (n % 2 == 0) {
        return 0;
    }
    
    int sqrt_n = (int)sqrt(n);
    for (int i = 3; i <= sqrt_n; i += 2) {
        if (n % i == 0) {
            return 0;
        }
    }
    return 1;
}

/**
 * Reverse a string in place
 * @param str: String to reverse
 * @return: Pointer to reversed string
 */
char* reverse_string(char* str) {
    if (str == NULL) {
        return NULL;
    }
    
    int len = strlen(str);
    for (int i = 0; i < len / 2; i++) {
        char temp = str[i];
        str[i] = str[len - 1 - i];
        str[len - 1 - i] = temp;
    }
    return str;
}

/**
 * Calculate sum of array elements
 * @param arr: Array of integers
 * @param size: Size of the array
 * @return: Sum of all elements
 */
long long array_sum(int* arr, int size) {
    if (arr == NULL || size <= 0) {
        return 0;
    }
    
    long long sum = 0;
    for (int i = 0; i < size; i++) {
        sum += arr[i];
    }
    return sum;
}

