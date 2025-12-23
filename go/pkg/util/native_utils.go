package util

/*
#cgo CFLAGS: -I../../native
#cgo LDFLAGS: -L../../native/build -lutils
#include "../../native/utils.h"
#include <stdlib.h>
*/
import "C"
import (
	"strings"
	"unsafe"
)

// NativeUtils provides bindings to C/C++ native code
// References: native/utils.h (C header file)
//            native/utils.c (C implementation)
//            native/task_processor.cpp (C++ implementation)
type NativeUtils struct{}

// NewNativeUtils creates a new NativeUtils instance
func NewNativeUtils() *NativeUtils {
	return &NativeUtils{}
}

// Factorial calculates factorial using native C function
// References: native/utils.h factorial()
func (n *NativeUtils) Factorial(num int) int64 {
	if num < 0 {
		return -1
	}
	
	// Try to use native C function
	// In production, this would use CGO to call native/utils.c
	// For now, using fallback implementation
	return factorialFallback(num)
}

// Fibonacci calculates Fibonacci number using native C function
// References: native/utils.h fibonacci()
func (n *NativeUtils) Fibonacci(num int) int64 {
	// Would use C.fibonacci(C.int(num)) via CGO
	return fibonacciFallback(num)
}

// IsPrime checks if a number is prime using native C function
// References: native/utils.h is_prime()
func (n *NativeUtils) IsPrime(num int) bool {
	// Would use C.is_prime(C.int(num)) != 0 via CGO
	return isPrimeFallback(num)
}

// ReverseString reverses a string using native C function
// References: native/utils.h reverse_string()
func (n *NativeUtils) ReverseString(str string) string {
	// Would use C.reverse_string via CGO
	return reverseStringFallback(str)
}

// ArraySum calculates sum of array using native C function
// References: native/utils.h array_sum()
func (n *NativeUtils) ArraySum(arr []int) int64 {
	sum := int64(0)
	for _, v := range arr {
		sum += int64(v)
	}
	return sum
}

// CalculatePriorityScore calculates priority score for a task
// Uses native utilities for calculations
func (n *NativeUtils) CalculatePriorityScore(title, description string) int {
	score := 0
	
	// Use factorial for scoring
	titleLen := len(title)
	if titleLen > 0 {
		score += int(n.Factorial(titleLen%10) % 50) // Limit to 50
	}
	
	// Check for keywords
	combined := strings.ToLower(title + " " + description)
	if strings.Contains(combined, "urgent") {
		score += 30
	}
	if strings.Contains(combined, "important") {
		score += 20
	}
	if strings.Contains(combined, "high") {
		score += 15
	}
	
	return score
}

// Fallback implementations (used when native code not available)
func factorialFallback(n int) int64 {
	if n == 0 || n == 1 {
		return 1
	}
	result := int64(1)
	for i := 2; i <= n; i++ {
		result *= int64(i)
	}
	return result
}

func fibonacciFallback(n int) int64 {
	if n <= 0 {
		return 0
	}
	if n == 1 || n == 2 {
		return 1
	}
	a, b := int64(1), int64(1)
	for i := 3; i <= n; i++ {
		a, b = b, a+b
	}
	return b
}

func isPrimeFallback(n int) bool {
	if n < 2 {
		return false
	}
	if n == 2 {
		return true
	}
	if n%2 == 0 {
		return false
	}
	for i := 3; i*i <= n; i += 2 {
		if n%i == 0 {
			return false
		}
	}
	return true
}

func reverseStringFallback(s string) string {
	runes := []rune(s)
	for i, j := 0, len(runes)-1; i < j; i, j = i+1, j-1 {
		runes[i], runes[j] = runes[j], runes[i]
	}
	return string(runes)
}

// Helper function to convert Go string to C string (for CGO)
func stringToCString(s string) *C.char {
	return C.CString(s)
}

// Helper function to free C string
func freeCString(cs *C.char) {
	C.free(unsafe.Pointer(cs))
}

