package com.taskmanager.util;

/**
 * NativeUtils - Wrapper for native C/C++ functions
 * References: native/utils.h (C header file)
 *            native/utils.c (C implementation)
 *            native/task_processor.cpp (C++ implementation)
 * 
 * This class provides Java bindings to native code
 */
public class NativeUtils {
    
    static {
        try {
            // Load native library
            // In production, this would load the compiled .so/.dll from native/build/
            System.loadLibrary("utils");
        } catch (UnsatisfiedLinkError e) {
            System.err.println("Warning: Native library 'utils' not found. Using fallback implementations.");
        }
    }

    // Native method declarations
    // These would be implemented via JNI (Java Native Interface)
    private native long factorialNative(int n);
    private native long fibonacciNative(int n);
    private native boolean isPrimeNative(int n);
    private native String reverseStringNative(String str);
    private native long arraySumNative(int[] arr);

    /**
     * Calculate factorial using native C function
     * References: native/utils.h factorial()
     */
    public long factorial(int n) {
        try {
            return factorialNative(n);
        } catch (UnsatisfiedLinkError e) {
            // Fallback implementation
            return factorialFallback(n);
        }
    }

    /**
     * Calculate Fibonacci number using native C function
     * References: native/utils.h fibonacci()
     */
    public long fibonacci(int n) {
        try {
            return fibonacciNative(n);
        } catch (UnsatisfiedLinkError e) {
            return fibonacciFallback(n);
        }
    }

    /**
     * Check if number is prime using native C function
     * References: native/utils.h is_prime()
     */
    public boolean isPrime(int n) {
        try {
            return isPrimeNative(n);
        } catch (UnsatisfiedLinkError e) {
            return isPrimeFallback(n);
        }
    }

    /**
     * Reverse string using native C function
     * References: native/utils.h reverse_string()
     */
    public String reverseString(String str) {
        try {
            return reverseStringNative(str);
        } catch (UnsatisfiedLinkError e) {
            return reverseStringFallback(str);
        }
    }

    /**
     * Calculate array sum using native C function
     * References: native/utils.h array_sum()
     */
    public long arraySum(int[] arr) {
        try {
            return arraySumNative(arr);
        } catch (UnsatisfiedLinkError e) {
            return arraySumFallback(arr);
        }
    }

    /**
     * Calculate priority score for task
     * Uses native utilities for calculations
     */
    public int calculatePriorityScore(String title, String description) {
        int score = 0;
        
        // Use native factorial for scoring
        int titleLength = title != null ? title.length() : 0;
        score += factorial(titleLength % 10) % 50; // Limit to 50
        
        // Check for keywords
        String combined = (title + " " + (description != null ? description : "")).toLowerCase();
        if (combined.contains("urgent")) score += 30;
        if (combined.contains("important")) score += 20;
        if (combined.contains("high")) score += 15;
        
        return score;
    }

    // Fallback implementations
    private long factorialFallback(int n) {
        if (n < 0) return -1;
        if (n == 0 || n == 1) return 1;
        long result = 1;
        for (int i = 2; i <= n; i++) {
            result *= i;
        }
        return result;
    }

    private long fibonacciFallback(int n) {
        if (n <= 0) return 0;
        if (n == 1 || n == 2) return 1;
        long a = 1, b = 1;
        for (int i = 3; i <= n; i++) {
            long temp = a + b;
            a = b;
            b = temp;
        }
        return b;
    }

    private boolean isPrimeFallback(int n) {
        if (n < 2) return false;
        if (n == 2) return true;
        if (n % 2 == 0) return false;
        for (int i = 3; i * i <= n; i += 2) {
            if (n % i == 0) return false;
        }
        return true;
    }

    private String reverseStringFallback(String str) {
        return new StringBuilder(str).reverse().toString();
    }

    private long arraySumFallback(int[] arr) {
        long sum = 0;
        for (int value : arr) {
            sum += value;
        }
        return sum;
    }
}

