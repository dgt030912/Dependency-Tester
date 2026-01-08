#include "utils.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

// ============ Mathematical Utilities ============

int factorial(int n) {
    if (n < 0) return -1;
    if (n <= 1) return 1;
    return n * factorial(n - 1);
}

long long factorial_long(int n) {
    if (n < 0) return -1;
    if (n <= 1) return 1;
    long long result = 1;
    for (int i = 2; i <= n; i++) {
        result *= i;
    }
    return result;
}

int fibonacci(int n) {
    if (n < 0) return -1;
    if (n <= 1) return n;
    
    int a = 0, b = 1, temp;
    for (int i = 2; i <= n; i++) {
        temp = a + b;
        a = b;
        b = temp;
    }
    return b;
}

long long fibonacci_long(int n) {
    if (n < 0) return -1;
    if (n <= 1) return n;
    
    long long a = 0, b = 1, temp;
    for (int i = 2; i <= n; i++) {
        temp = a + b;
        a = b;
        b = temp;
    }
    return b;
}

bool is_prime(int n) {
    if (n <= 1) return false;
    if (n <= 3) return true;
    if (n % 2 == 0 || n % 3 == 0) return false;
    
    for (int i = 5; i * i <= n; i += 6) {
        if (n % i == 0 || n % (i + 2) == 0)
            return false;
    }
    return true;
}

int gcd(int a, int b) {
    a = abs(a);
    b = abs(b);
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

int lcm(int a, int b) {
    if (a == 0 || b == 0) return 0;
    return abs(a * b) / gcd(a, b);
}

double power(double base, int exponent) {
    if (exponent == 0) return 1.0;
    if (exponent < 0) {
        base = 1.0 / base;
        exponent = -exponent;
    }
    
    double result = 1.0;
    for (int i = 0; i < exponent; i++) {
        result *= base;
    }
    return result;
}

// ============ String Utilities ============

void reverse_string(char* str) {
    if (str == NULL) return;
    
    int len = strlen(str);
    for (int i = 0; i < len / 2; i++) {
        char temp = str[i];
        str[i] = str[len - i - 1];
        str[len - i - 1] = temp;
    }
}

int string_length(const char* str) {
    return str ? strlen(str) : 0;
}

char* string_concat(const char* str1, const char* str2) {
    if (!str1 && !str2) return NULL;
    if (!str1) return strdup(str2);
    if (!str2) return strdup(str1);
    
    size_t len1 = strlen(str1);
    size_t len2 = strlen(str2);
    char* result = (char*)safe_malloc(len1 + len2 + 1);
    
    strcpy(result, str1);
    strcat(result, str2);
    return result;
}

bool string_equals(const char* str1, const char* str2) {
    if (str1 == str2) return true;
    if (!str1 || !str2) return false;
    return strcmp(str1, str2) == 0;
}

char* string_to_upper(char* str) {
    if (!str) return NULL;
    for (int i = 0; str[i]; i++) {
        str[i] = toupper((unsigned char)str[i]);
    }
    return str;
}

char* string_to_lower(char* str) {
    if (!str) return NULL;
    for (int i = 0; str[i]; i++) {
        str[i] = tolower((unsigned char)str[i]);
    }
    return str;
}

int count_vowels(const char* str) {
    if (!str) return 0;
    int count = 0;
    for (int i = 0; str[i]; i++) {
        char c = tolower((unsigned char)str[i]);
        if (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u') {
            count++;
        }
    }
    return count;
}

int count_words(const char* str) {
    if (!str) return 0;
    int count = 0;
    bool in_word = false;
    
    for (int i = 0; str[i]; i++) {
        if (isspace((unsigned char)str[i])) {
            in_word = false;
        } else if (!in_word) {
            in_word = true;
            count++;
        }
    }
    return count;
}

// ============ Array Utilities ============

int sum_array(const int* arr, size_t size) {
    if (!arr) return 0;
    int sum = 0;
    for (size_t i = 0; i < size; i++) {
        sum += arr[i];
    }
    return sum;
}

double average_array(const int* arr, size_t size) {
    if (!arr || size == 0) return 0.0;
    return (double)sum_array(arr, size) / size;
}

int find_max(const int* arr, size_t size) {
    if (!arr || size == 0) return 0;
    int max = arr[0];
    for (size_t i = 1; i < size; i++) {
        if (arr[i] > max) max = arr[i];
    }
    return max;
}

int find_min(const int* arr, size_t size) {
    if (!arr || size == 0) return 0;
    int min = arr[0];
    for (size_t i = 1; i < size; i++) {
        if (arr[i] < min) min = arr[i];
    }
    return min;
}

void sort_array(int* arr, size_t size) {
    if (!arr || size <= 1) return;
    
    for (size_t i = 0; i < size - 1; i++) {
        for (size_t j = 0; j < size - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

int binary_search(const int* arr, size_t size, int target) {
    if (!arr) return -1;
    
    int left = 0;
    int right = size - 1;
    
    while (left <= right) {
        int mid = left + (right - left) / 2;
        
        if (arr[mid] == target) return mid;
        if (arr[mid] < target) left = mid + 1;
        else right = mid - 1;
    }
    return -1;
}

void reverse_array(int* arr, size_t size) {
    if (!arr || size <= 1) return;
    
    for (size_t i = 0; i < size / 2; i++) {
        int temp = arr[i];
        arr[i] = arr[size - i - 1];
        arr[size - i - 1] = temp;
    }
}

// ============ Memory Utilities ============

void* safe_malloc(size_t size) {
    void* ptr = malloc(size);
    if (!ptr && size > 0) {
        fprintf(stderr, "Memory allocation failed for %zu bytes\n", size);
        exit(EXIT_FAILURE);
    }
    return ptr;
}

void* safe_calloc(size_t num, size_t size) {
    void* ptr = calloc(num, size);
    if (!ptr && num > 0 && size > 0) {
        fprintf(stderr, "Memory allocation failed for %zu elements of %zu bytes\n", num, size);
        exit(EXIT_FAILURE);
    }
    return ptr;
}

void safe_free(void** ptr) {
    if (ptr && *ptr) {
        free(*ptr);
        *ptr = NULL;
    }
}
